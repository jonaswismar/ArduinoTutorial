#include "Arduino.h"

#include "FS.h"
 
void setup()
{
    Serial.begin(112500);
 
    delay(500);
 
    Serial.println(F("Inizializing FS..."));
    if (SPIFFS.begin()){
        Serial.println(F("done."));
    }else{
        Serial.println(F("fail."));
    }
 
    FSInfo fs_info;
    SPIFFS.info(fs_info);
 
    Serial.println("File system info.");
 
    Serial.print("Total space:      ");
    Serial.print(fs_info.totalBytes);
    Serial.println("byte");
 
    Serial.print("Total space used: ");
    Serial.print(fs_info.usedBytes);
    Serial.println("byte");
 
    Serial.print("Block size:       ");
    Serial.print(fs_info.blockSize);
    Serial.println("byte");
 
    Serial.print("Page size:        ");
    Serial.print(fs_info.totalBytes);
    Serial.println("byte");
 
    Serial.print("Max open files:   ");
    Serial.println(fs_info.maxOpenFiles);
 
    Serial.print("Max path length:  ");
    Serial.println(fs_info.maxPathLength);
 
    Serial.println();
 
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
        Serial.print(dir.fileName());
        Serial.print(" - ");
        if(dir.fileSize()) {
            File f = dir.openFile("r");
            Serial.println(f.size());
            f.close();
        }else{
            Serial.println("0");
        }
    }
}
 
void loop()
{
 
}