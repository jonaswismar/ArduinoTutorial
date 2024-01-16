#include <Arduino.h>

#include <ESP8266WiFi.h>

#include "sensor\ads1115\humidity.h"
#include "sensor\ads1115\thermistor.h"
#include "sensor\anemometer.h"
#include "sensor\bmp280.h"
#include "sensor\dht22.h"
#include "sensor\hmc5883l.h"
#include "sensor\mlx90614.h"
#include "sensor\raingauge.h"
#include "sensor\tsl2561.h"
#include "sensor\vane.h"
#include "sensor\veml6070.h"

WiFiClient client1;
WiFiClient client2;
WiFiClient client3;

const char *server1 = "api.thingspeak.com";
const char *server2 = "api.thingspeak.com";
const char *server3 = "api.thingspeak.com";

const char *api_key1 = "5OA4K813NOZODS28";
const char *api_key2 = "3MIDI9LVX0WAA60E";
const char *api_key3 = "7VO5JZCW57VB8OJ8";

void transmitThinkspeak()
{
    if (client1.connect(server1, 80))
    {
        Serial.println("Connect to ThingSpeak - OK");

        String dataToThingSpeak = "";
        dataToThingSpeak += "GET /update?api_key=";
        dataToThingSpeak += api_key1;

        dataToThingSpeak += "&field1=";
        dataToThingSpeak += String(getBmp1Temperature());

        dataToThingSpeak += "&field2=";
        dataToThingSpeak += String(getBmp1Pressure());

        dataToThingSpeak += "&field3=";
        dataToThingSpeak += String(getBmp1Altitude());

        dataToThingSpeak += "&field4=";
        dataToThingSpeak += String(getDht1Temperature());

        dataToThingSpeak += "&field5=";
        dataToThingSpeak += String(getDht1Humidity());

        dataToThingSpeak += "&field6=";
        dataToThingSpeak += String(getAdsTemperature());

        dataToThingSpeak += "&field7=";
        dataToThingSpeak += String(getAdsHumidity());

        dataToThingSpeak += "&field8=";
        dataToThingSpeak += String(getAmbientTemp());

        dataToThingSpeak += " HTTP/1.1\r\nHost: a.c.d\r\nConnection: close\r\n\r\n";
        dataToThingSpeak += "";
        client1.print(dataToThingSpeak);

        int timeout = millis() + 5000;
        while (client1.available() == 0)
        {
            if (timeout - millis() < 0)
            {
                Serial.println("Error: Client Timeout!");
                client1.stop();
                return;
            }
        }
    }

    if (client2.connect(server2, 80))
    {
        Serial.println("Connect to ThingSpeak - OK");

        String dataToThingSpeak = "";
        dataToThingSpeak += "GET /update?api_key=";
        dataToThingSpeak += api_key2;

        dataToThingSpeak += "&field1=";
        dataToThingSpeak += String(getObjectTemp());

        dataToThingSpeak += "&field2=";
        dataToThingSpeak += String(getAnemoSpeed());

        dataToThingSpeak += "&field3=";
        dataToThingSpeak += String(getEmissivity());

        dataToThingSpeak += "&field4=";
        dataToThingSpeak += String(getTsl1Light());

        dataToThingSpeak += "&field5=";
        dataToThingSpeak += String(getTsl1Broadband());

        dataToThingSpeak += "&field6=";
        dataToThingSpeak += String(getTsl1Ir());

        dataToThingSpeak += "&field7=";
        dataToThingSpeak += String(getVemlUV());

        dataToThingSpeak += "&field8=";
        dataToThingSpeak += String(getVaneDirection());

        dataToThingSpeak += " HTTP/1.1\r\nHost: a.c.d\r\nConnection: close\r\n\r\n";
        dataToThingSpeak += "";
        client2.print(dataToThingSpeak);

        int timeout = millis() + 5000;
        while (client2.available() == 0)
        {
            if (timeout - millis() < 0)
            {
                Serial.println("Error: Client Timeout!");
                client2.stop();
                return;
            }
        }
    }

    if (client3.connect(server3, 80))
    {
        Serial.println("Connect to ThingSpeak - OK");

        String dataToThingSpeak = "";
        dataToThingSpeak += "GET /update?api_key=";
        dataToThingSpeak += api_key3;

        dataToThingSpeak += "&field1=";
        dataToThingSpeak += String(getheadingDegrees());

        dataToThingSpeak += "&field2=";
        dataToThingSpeak += String(getRainVolume());

        dataToThingSpeak += " HTTP/1.1\r\nHost: a.c.d\r\nConnection: close\r\n\r\n";
        dataToThingSpeak += "";
        client3.print(dataToThingSpeak);

        int timeout = millis() + 5000;
        while (client3.available() == 0)
        {
            if (timeout - millis() < 0)
            {
                Serial.println("Error: Client Timeout!");
                client3.stop();
                return;
            }
        }
    }
}