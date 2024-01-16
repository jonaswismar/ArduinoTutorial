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
#include "sensor\as3935.h"
#include "sensor\bmp280.h"
#include "sensor\dht22.h"
#include "sensor\hmc5883l.h"
#include "sensor\mlx90614.h"
#include "sensor\raingauge.h"
#include "sensor\tsl2561.h"
#include "sensor\vane.h"
#include "sensor\veml6070.h"
#include "server\asyncwebserver.h"
#include "time\ntptimeclient.h"
#include "web\sunrise.h"
#include "web\thingspeak.h"

unsigned long previousMillisWiFi = 0;
const unsigned long intervalWiFi = 30000;

const unsigned long intervalSensors = 20000;
unsigned long previousMillisSensors = 0;

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
    initAs();
    initBmp1();
    initDht1();
    initHmc1();
    initMlx1();
    initRainGauge();
    initTsl1();
    initVane();
    initVeml();
}

void loop()
{
    unsigned long currentMillis = millis();
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillisWiFi >= intervalWiFi))
    {
        Serial.print(millis());
        Serial.println("Reconnecting to WiFi...");
        WiFi.disconnect();
        WiFi.reconnect();
        previousMillisWiFi = currentMillis;
    }
    updateNTPTimeClient();
    updateSunrise();
    /* Serial.println(getAds1Status());
      Serial.println(getBmp1Status());
      Serial.println(getDht1Status());
      Serial.println(getTsl1Status());
      Serial.println(getVemlStatus());
      Serial.println("-------");*/

    if (currentMillis - previousMillisSensors >= intervalSensors)
    {

        readAds1();
        readAdsHumidity();
        readAdsTemperature();
        readAs();
        readAnemo();
        readBmp1();
        readDht1();
        readTsl1();
        readVane();
        readVeml();

        previousMillisSensors = millis();

        transmitThinkspeak();
    }
}