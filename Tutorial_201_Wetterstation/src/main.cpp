#include <Arduino.h>

#include <FS.h>
#include <SPI.h>
#include <Wire.h>

#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>

#include "credentials.h"
#include "sensor\anemometer.h"
#include "sensor\ads1115.h"
#include "sensor\ads1115\humidity.h"
#include "sensor\ads1115\thermistor.h"
#include "sensor\bmp280.h"
#include "sensor\dht22.h"
#include "sensor\tsl2561.h"
#include "sensor\vane.h"
#include "sensor\veml6070.h"
#include "server\asyncwebserver.h"
#include "time\ntptimeclient.h"
#include "web\sunrise.h"

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
    Serial.println(getAds1Status());
    Serial.println(getBmp1Status());
    Serial.println(getDht1Status());
    Serial.println(getTsl1Status());
    Serial.println(getVemlStatus());
    Serial.println("-------");

    readAds1();
    readAdsHumidity();
    readAdsTemperature();
    readAnemo();
    readBmp1();
    readDht1();
    readTsl1();
    readVane();
    readVeml();
    
    delay(5000);
}