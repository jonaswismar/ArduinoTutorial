#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <ESP8266WiFi.h>

#include "credentials.h"

#define BMP_SCK (D1)
#define BMP_MISO (D3)
#define BMP_MOSI (D2)
#define BMP_CS (D4)

Adafruit_BMP280 bmp; // I2C
// Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
// Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

WiFiClient client;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  unsigned status;
  // status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status)
  {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x");
    Serial.println(bmp.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1)
      delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {

    // Blink LED when connecting to wifi
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
  }
  Serial.println("WiFi connected");
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  Serial.print(F("Temperature = "));
  float temperature = bmp.readTemperature();
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  float pressure = bmp.readPressure();
  Serial.print(pressure);
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  float altitude = bmp.readAltitude(1013.25);
  Serial.print(altitude);
  Serial.println(" m");

  Serial.println();
  delay(2000);

  if (client.connect(server, 80))
  {
    Serial.println("Connect to ThingSpeak - OK");

    String dataToThingSpeak = "";
    dataToThingSpeak += "GET /update?api_key=";
    dataToThingSpeak += api_key;

    dataToThingSpeak += "&field1=";
    dataToThingSpeak += String(temperature);

    dataToThingSpeak += "&field2=";
    dataToThingSpeak += String(pressure);

    dataToThingSpeak += "&field3=";
    dataToThingSpeak += String(altitude);

    dataToThingSpeak += " HTTP/1.1\r\nHost: a.c.d\r\nConnection: close\r\n\r\n";
    dataToThingSpeak += "";
    client.print(dataToThingSpeak);

    int timeout = millis() + 5000;
    while (client.available() == 0)
    {
      if (timeout - millis() < 0)
      {
        Serial.println("Error: Client Timeout!");
        client.stop();
        return;
      }
    }
  }
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}
