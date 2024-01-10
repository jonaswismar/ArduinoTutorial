#include <Arduino.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "server\processor\air.h"
#include "server\processor\humidity.h"
#include "server\processor\index.h"
#include "server\processor\moon.h"
#include "server\processor\rain.h"
#include "server\processor\sun.h"
#include "server\processor\temperature.h"
#include "server\processor\time.h"

AsyncWebServer server(80);

const char *http_username = "admin";
const char *http_password = "admin";

static const char TEXT_CSS[] PROGMEM = "text/css";
static const char TEXT_PLAIN[] PROGMEM = "text/plain";
static const char TEXT_HTML[] PROGMEM = "text/html";
static const char IMAGE_PNG[] PROGMEM = "image/png";

void initWebserver()
{
    if (!SPIFFS.begin())
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    Serial.println("SPIFFS running");

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.htm", String(), false, processorIndex); });
    server.on("/index.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.htm", String(), false, processorIndex); });
    server.on("/humi.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/humi.htm", String(), false, processorHumi); });
    server.on("/loc.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/loc.htm", FPSTR(TEXT_HTML)); });
    server.on("/moon.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/moon.htm", String(), false, processorMoon); });
    server.on("/prog.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/prog.htm", FPSTR(TEXT_HTML)); });
    server.on("/rain.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/rain.htm", String(), false, processorRain); });
    server.on("/start.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/start.htm", FPSTR(TEXT_HTML)); });
    server.on("/sun.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/sun.htm", String(), false, processorSun); });
    server.on("/temp.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/temp.htm", String(), false, processorTemp); });
    server.on("/time.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/time.htm", String(), false, processorTime); });
    server.on("/air.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/air.htm", String(), false, processorAir); });

    server.on("/tools.htm", HTTP_GET, [](AsyncWebServerRequest *request)
              {  if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
      request->send(SPIFFS, "/tools.htm", FPSTR(TEXT_HTML)); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", FPSTR(TEXT_CSS)); });

    server.begin();
}