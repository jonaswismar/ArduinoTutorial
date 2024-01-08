#include <Arduino.h>

#include <FS.h>
#include <SPI.h>
#include <Wire.h>

#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>

#include "server\asyncwebserver.h"
#include "time\ntptimeclient.h"
#include "client\sunrise.h"

#include "sensor\anemometer.h"
#include "sensor\ads1115.h"
#include "sensor\bmp280.h"
#include "sensor\dht22.h"
#include "sensor\tsl2561.h"
#include "sensor\vane.h"
#include "sensor\veml6070.h"

const char *ssid = "HighSecurity";
const char *password = "1337leet";

void setup()
{
    Serial.begin(115200);
    Serial.println("Booting");
    WiFi.begin(ssid, password);

    Serial.print("WiFi connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    initNTPTimeClient();
    updateNTPTimeClient();
    Serial.println("NTP running");
    initWebserver();
    Serial.println("Server running");

    initAds1();
    initAnemo();
    initBmp1();
    initDht1();
    initTsl1();
    initVane();
    initVeml();
}

void loop()
{
    updateNTPTimeClient();
    updateSunrise();
    delay(5000);
}