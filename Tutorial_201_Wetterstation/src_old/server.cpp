#include <Arduino.h>

#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <FS.h>

#include <NTPClient.h>

#include "const.h"
#include "credentials.h"

#ifndef DBG_OUTPUT_PORT
#define DBG_OUTPUT_PORT Serial
#endif

String unsupportedFiles = String();
FS *fileSystem = &SPIFFS;
SPIFFSConfig fileSystemConfig = SPIFFSConfig();
static bool fsOK;
File uploadFile;

ESP8266WebServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds, 60000);

/*
Replys
*/
void replyOK()
{
    server.send(200, FPSTR(TEXT_PLAIN), "");
}

void replyOKWithMsg(String msg)
{
    server.send(200, FPSTR(TEXT_PLAIN), msg);
}

void replyNotFound(String msg)
{
    server.send(404, FPSTR(TEXT_PLAIN), msg);
}

void replyBadRequest(String msg)
{
    DBG_OUTPUT_PORT.println(msg);
    server.send(400, FPSTR(TEXT_PLAIN), msg + "\r\n");
}

void replyServerError(String msg)
{
    DBG_OUTPUT_PORT.println(msg);
    server.send(500, FPSTR(TEXT_PLAIN), msg + "\r\n");
}

/*
Handles
*/
void handleNotFound()
{
    if (!fsOK)
    {
        return replyServerError(FPSTR(FS_INIT_ERROR));
    }

    String uri = ESP8266WebServer::urlDecode(server.uri());

    if (handleFileRead(uri))
    {
        return;
    }

    String message;
    message.reserve(100);
    message = F("Error: File not found\n\nURI: ");
    message += uri;
    message += F("\nMethod: ");
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += F("\nArguments: ");
    message += server.args();
    message += '\n';
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += F(" NAME:");
        message += server.argName(i);
        message += F("\n VALUE:");
        message += server.arg(i);
        message += '\n';
    }
    message += "path=";
    message += server.arg("path");
    message += '\n';
    DBG_OUTPUT_PORT.print(message);

    return replyNotFound(message);
}

void handleGetEdit()
{
    if (handleFileRead(F("/edit/index.htm")))
    {
        return;
    }
    replyNotFound(FPSTR(FILE_NOT_FOUND));
}

String checkForUnsupportedPath(String filename)
{
    String error = String();
    if (!filename.startsWith("/"))
    {
        error += F("!NO_LEADING_SLASH! ");
    }
    if (filename.indexOf("//") != -1)
    {
        error += F("!DOUBLE_SLASH! ");
    }
    if (filename.endsWith("/"))
    {
        error += F("!TRAILING_SLASH! ");
    }
    return error;
}

void handleStatus()
{
    DBG_OUTPUT_PORT.println("handleStatus");
    FSInfo fs_info;
    String json;
    json.reserve(128);

    json = "{\"type\":\"";
    json += fsName;
    json += "\", \"isOk\":";
    if (fsOK)
    {
        fileSystem->info(fs_info);
        json += F("\"true\", \"totalBytes\":\"");
        json += fs_info.totalBytes;
        json += F("\", \"usedBytes\":\"");
        json += fs_info.usedBytes;
        json += "\"";
    }
    else
    {
        json += "\"false\"";
    }
    json += F(",\"unsupportedFiles\":\"");
    json += unsupportedFiles;
    json += "\"}";

    server.send(200, "application/json", json);
}

void handleFileList()
{
    if (!fsOK)
    {
        return replyServerError(FPSTR(FS_INIT_ERROR));
    }

    if (!server.hasArg("dir"))
    {
        return replyBadRequest(F("DIR ARG MISSING"));
    }

    String path = server.arg("dir");
    if (path != "/" && !fileSystem->exists(path))
    {
        return replyBadRequest("BAD PATH");
    }

    DBG_OUTPUT_PORT.println(String("handleFileList: ") + path);
    Dir dir = fileSystem->openDir(path);
    path.clear();

    if (!server.chunkedResponseModeStart(200, "text/json"))
    {
        server.send(505, F("text/html"), F("HTTP1.1 required"));
        return;
    }

    String output;
    output.reserve(64);
    while (dir.next())
    {
        String error = checkForUnsupportedPath(dir.fileName());
        if (error.length() > 0)
        {
            DBG_OUTPUT_PORT.println(String("Ignoring ") + error + dir.fileName());
            continue;
        }
        if (output.length())
        {
            server.sendContent(output);
            output = ',';
        }
        else
        {
            output = '[';
        }

        output += "{\"type\":\"";
        if (dir.isDirectory())
        {
            output += "dir";
        }
        else
        {
            output += F("file\",\"size\":\"");
            output += dir.fileSize();
        }

        output += F("\",\"name\":\"");
        if (dir.fileName()[0] == '/')
        {
            output += &(dir.fileName()[1]);
        }
        else
        {
            output += dir.fileName();
        }

        output += "\"}";
    }

    output += "]";
    server.sendContent(output);
    server.chunkedResponseFinalize();
}

bool handleFileRead(String path)
{
    DBG_OUTPUT_PORT.println(String("handleFileRead: ") + path);
    if (!fsOK)
    {
        replyServerError(FPSTR(FS_INIT_ERROR));
        return true;
    }

    if (path.endsWith("/"))
    {
        path += "index.htm";
    }

    String contentType;
    if (server.hasArg("download"))
    {
        contentType = F("application/octet-stream");
    }
    else
    {
        contentType = mime::getContentType(path);
    }

    if (!fileSystem->exists(path))
    {
        path = path + ".gz";
    }
    if (fileSystem->exists(path))
    {
        File file = fileSystem->open(path, "r");
        if (server.streamFile(file, contentType) != file.size())
        {
            DBG_OUTPUT_PORT.println("Sent less data than expected!");
        }
        file.close();
        return true;
    }

    return false;
}

String lastExistingParent(String path)
{
    while (!path.isEmpty() && !fileSystem->exists(path))
    {
        if (path.lastIndexOf('/') > 0)
        {
            path = path.substring(0, path.lastIndexOf('/'));
        }
        else
        {
            path = String();
        }
    }
    DBG_OUTPUT_PORT.println(String("Last existing parent: ") + path);
    return path;
}

void handleFileCreate()
{
    if (!fsOK)
    {
        return replyServerError(FPSTR(FS_INIT_ERROR));
    }

    String path = server.arg("path");
    if (path.isEmpty())
    {
        return replyBadRequest(F("PATH ARG MISSING"));
    }

    if (checkForUnsupportedPath(path).length() > 0)
    {
        return replyServerError(F("INVALID FILENAME"));
    }

    if (path == "/")
    {
        return replyBadRequest("BAD PATH");
    }
    if (fileSystem->exists(path))
    {
        return replyBadRequest(F("PATH FILE EXISTS"));
    }

    String src = server.arg("src");
    if (src.isEmpty())
    {
        DBG_OUTPUT_PORT.println(String("handleFileCreate: ") + path);
        if (path.endsWith("/"))
        {
            path.remove(path.length() - 1);
            if (!fileSystem->mkdir(path))
            {
                return replyServerError(F("MKDIR FAILED"));
            }
        }
        else
        {
            File file = fileSystem->open(path, "w");
            if (file)
            {
                file.write((const char *)0);
                file.close();
            }
            else
            {
                return replyServerError(F("CREATE FAILED"));
            }
        }
        if (path.lastIndexOf('/') > -1)
        {
            path = path.substring(0, path.lastIndexOf('/'));
        }
        replyOKWithMsg(path);
    }
    else
    {
        if (src == "/")
        {
            return replyBadRequest("BAD SRC");
        }
        if (!fileSystem->exists(src))
        {
            return replyBadRequest(F("SRC FILE NOT FOUND"));
        }

        DBG_OUTPUT_PORT.println(String("handleFileCreate: ") + path + " from " + src);

        if (path.endsWith("/"))
        {
            path.remove(path.length() - 1);
        }
        if (src.endsWith("/"))
        {
            src.remove(src.length() - 1);
        }
        if (!fileSystem->rename(src, path))
        {
            return replyServerError(F("RENAME FAILED"));
        }
        replyOKWithMsg(lastExistingParent(src));
    }
}

void deleteRecursive(String path)
{
    File file = fileSystem->open(path, "r");
    bool isDir = file.isDirectory();
    file.close();

    if (!isDir)
    {
        fileSystem->remove(path);
        return;
    }

    Dir dir = fileSystem->openDir(path);

    while (dir.next())
    {
        deleteRecursive(path + '/' + dir.fileName());
    }

    fileSystem->rmdir(path);
}

void handleFileDelete()
{
    if (!fsOK)
    {
        return replyServerError(FPSTR(FS_INIT_ERROR));
    }

    String path = server.arg(0);
    if (path.isEmpty() || path == "/")
    {
        return replyBadRequest("BAD PATH");
    }

    DBG_OUTPUT_PORT.println(String("handleFileDelete: ") + path);
    if (!fileSystem->exists(path))
    {
        return replyNotFound(FPSTR(FILE_NOT_FOUND));
    }
    deleteRecursive(path);

    replyOKWithMsg(lastExistingParent(path));
}

void handleFileUpload()
{
    if (!fsOK)
    {
        return replyServerError(FPSTR(FS_INIT_ERROR));
    }
    if (server.uri() != "/edit")
    {
        return;
    }
    HTTPUpload &upload = server.upload();
    if (upload.status == UPLOAD_FILE_START)
    {
        String filename = upload.filename;
        if (!filename.startsWith("/"))
        {
            filename = "/" + filename;
        }
        DBG_OUTPUT_PORT.println(String("handleFileUpload Name: ") + filename);
        uploadFile = fileSystem->open(filename, "w");
        if (!uploadFile)
        {
            return replyServerError(F("CREATE FAILED"));
        }
        DBG_OUTPUT_PORT.println(String("Upload: START, filename: ") + filename);
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
        if (uploadFile)
        {
            size_t bytesWritten = uploadFile.write(upload.buf, upload.currentSize);
            if (bytesWritten != upload.currentSize)
            {
                return replyServerError(F("WRITE FAILED"));
            }
        }
        DBG_OUTPUT_PORT.println(String("Upload: WRITE, Bytes: ") + upload.currentSize);
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
        if (uploadFile)
        {
            uploadFile.close();
        }
        DBG_OUTPUT_PORT.println(String("Upload: END, Size: ") + upload.totalSize);
    }
}

void serverInit()
{
    DBG_OUTPUT_PORT.begin(115200);
    DBG_OUTPUT_PORT.setDebugOutput(true);
    DBG_OUTPUT_PORT.print('\n');

    fileSystemConfig.setAutoFormat(false);
    fileSystem->setConfig(fileSystemConfig);
    fsOK = fileSystem->begin();
    DBG_OUTPUT_PORT.println(fsOK ? F("Filesystem initialized.") : F("Filesystem init failed!"));

    Dir dir = fileSystem->openDir("");
    DBG_OUTPUT_PORT.println(F("List of files at root of filesystem:"));
    while (dir.next())
    {
        String error = checkForUnsupportedPath(dir.fileName());
        String fileInfo = dir.fileName() + (dir.isDirectory() ? " [DIR]" : String(" (") + dir.fileSize() + "b)");
        DBG_OUTPUT_PORT.println(error + fileInfo);
        if (error.length() > 0)
        {
            unsupportedFiles += error + fileInfo + '\n';
        }
    }
    DBG_OUTPUT_PORT.println();

    unsupportedFiles.replace("\n", "<br/>");
    unsupportedFiles = unsupportedFiles.substring(0, unsupportedFiles.length() - 5);

    DBG_OUTPUT_PORT.printf("Connecting to %s\n", ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        DBG_OUTPUT_PORT.print(".");
    }
    DBG_OUTPUT_PORT.println("");
    DBG_OUTPUT_PORT.print(F("Connected! IP address: "));
    DBG_OUTPUT_PORT.println(WiFi.localIP());

    if (MDNS.begin(host))
    {
        MDNS.addService("http", "tcp", 80);
        DBG_OUTPUT_PORT.print(F("Open http://"));
        DBG_OUTPUT_PORT.print(host);
        DBG_OUTPUT_PORT.println(F(".local/edit to open the FileSystem Browser"));
    }

    server.on("/status", HTTP_GET, handleStatus);

    server.on("/list", HTTP_GET, handleFileList);

    server.on("/edit", HTTP_GET, handleGetEdit);

    server.on("/edit", HTTP_PUT, handleFileCreate);

    server.on("/edit", HTTP_DELETE, handleFileDelete);

    server.on("/edit", HTTP_POST, replyOK, handleFileUpload);

    server.onNotFound(handleNotFound);

    server.begin();
    DBG_OUTPUT_PORT.println("HTTP server started");
    timeClient.begin();
}

void handleClient()
{
    server.handleClient();
    timeClient.update();
    MDNS.update();
}