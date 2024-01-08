#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_VEML6070.h>
#include <DHT.h>
#include <DHT_U.h>

#include "math.h"

#ifndef DBG_OUTPUT_PORT
#define DBG_OUTPUT_PORT Serial
#endif

// Sensor Objects
Adafruit_ADS1115 ads;
Adafruit_BMP280 bmp;
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
Adafruit_VEML6070 veml = Adafruit_VEML6070();
DHT_Unified dht(D3, DHT22);

// Sensor Status
boolean statusAds = false;
boolean statusAnemometer = false;
boolean statusBmp = false;
boolean statusTsl = false;
boolean statusVane = false;
boolean statusVeml = false;
boolean statusDht = false;
boolean statusMoist = false;

// Sensor Results
float m_temperatureBmp = 0; // °C
float m_pressureBmp = 0;    // hPa (mb)
float m_altitudeBmp = 0;    // m
float m_lightTsl = 0;       // lux
int m_uvVeml = 0;           // UV Index
float m_temperatureDht = 0; // °C
float m_humidityDht = 0;    // %
float m_humidityEarth = 0;  // %

// Calculated Results
float c_humidityAbsolut = 0;    // g/m³
float c_dewPoint = 0;      // °C
float c_windChill = 0;     // °C
float c_windDirection = 0; // 0-360 °
float c_windSpeed = 0;     // km/h
int c_windBeaufort = 0;    // Bft
int c_windFujita = 0;      // F
int c_windEFujita = 0;     // EF
int c_windSaffirSimpson = 0;
int c_windTorro = 0;  // T
float c_rainFall = 0; // mm
// c_ozon
// c_co2
// c_dayTime;
// c_Season;

// Polled Results
// p_sunRise;
// p_sunSet;
// p_moonRise;
// p_moonSet;
// p_sunHours;

// Helper for Anemometer
unsigned long t_anemometerLastCheck = 0;
volatile int irc_anemometer = 0;
void ICACHE_RAM_ATTR ISR()
{
    irc_anemometer++;
}

void initSensorADS()
{
    statusAds = ads.begin();
}
void initSensorAnemometer()
{
    statusAnemometer = true;
    t_anemometerLastCheck = 0;
    irc_anemometer = 0;
}

void initSensorBMP()
{
    statusBmp = bmp.begin(0x76);
    if (statusBmp == false)
    {
        DBG_OUTPUT_PORT.println(F("Could not find a valid BMP280 sensor, check wiring or try a different address!"));
    }
    else
    {
        bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                        Adafruit_BMP280::SAMPLING_X2,
                        Adafruit_BMP280::SAMPLING_X16,
                        Adafruit_BMP280::FILTER_X16,
                        Adafruit_BMP280::STANDBY_MS_500);
    }
}

void initSensorDHT()
{
    dht.begin();
    statusDht = true;
}

void initSensorMoist()
{
    if (statusAds == true)
    {
        statusMoist = true;
    }
    else
    {
        initSensorADS();
    }
}

void initSensorTSL()
{
    statusTsl = tsl.begin();
    if (statusTsl == false)
    {
        DBG_OUTPUT_PORT.println(F("Could not find a valid TSL2561 sensor, check wiring or try a different address!"));
    }
    else
    {
        tsl.enableAutoRange(true);
        tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);
    }
}

void initSensorVane()
{
    if (statusAds == true)
    {
        statusVane = true;
    }
    else
    {
        initSensorADS();
    }
}

void initSensorVEML()
{
    veml.begin(VEML6070_1_T);
    statusVeml = true;
}

void initSensors()
{
    initSensorADS();
    initSensorAnemometer();
    initSensorBMP();
    initSensorDHT();
    initSensorMoist();
    initSensorTSL();
    initSensorVEML();
}

float readSensorADS(int sensor, boolean compute)
{
    int16_t adc = ads.readADC_SingleEnded(0);
    if (compute == true)
    {
        return ads.computeVolts(adc);
    }
    else
    {
        return float(adc);
    }
}
void readSensorAnemometer()
{
    unsigned long currentMillis = millis();
    unsigned long irc_anemometerSec = (currentMillis - t_anemometerLastCheck) / 1000;
    // Calculation only realistic if measuring time greater than 10 seconds
    if (irc_anemometerSec >= 10)
    {
        // One tick per second times 2.4 is speed in km/h
        c_windSpeed = (irc_anemometer / irc_anemometerSec) * 2.4;

        c_windBeaufort = calculateBeaufort(c_windSpeed);
        c_windFujita = calculateFujita(c_windSpeed);
        c_windEFujita = calculateEFujita(c_windSpeed);
        c_windSaffirSimpson = calculateSaffirSimpson(c_windSpeed);
        c_windTorro = calculateTorro(c_windSpeed);

        t_anemometerLastCheck = 0;
        irc_anemometer = 0;
    }
}

void readSensorBMP()
{
    m_temperatureBmp = bmp.readTemperature();
    m_pressureBmp = bmp.readPressure();
    m_altitudeBmp = bmp.readAltitude(1013.25);
    if (m_temperatureBmp != 0 && m_humidityDht != 0)
    {
        c_dewPoint = calculateDewPoint(m_temperatureBmp, m_humidityDht);
    }
}

void readSensorDHT()
{
    sensors_event_t eventDht;
    dht.temperature().getEvent(&eventDht);
    if (isnan(eventDht.temperature))
    {
    }
    else
    {
        m_temperatureDht = eventDht.temperature;
    }
    dht.humidity().getEvent(&eventDht);
    if (isnan(eventDht.relative_humidity))
    {
    }
    else
    {
        m_humidityDht = eventDht.relative_humidity;
    }
    if (m_temperatureBmp != 0 && m_humidityDht != 0)
    {
        c_dewPoint = calculateDewPoint(m_temperatureBmp, m_humidityDht);
        c_humidityAbsolut = calculateHumidityAbsolut(m_temperatureBmp, m_humidityDht);
    }
}

void readSensorMoist()
{
    m_humidityEarth = map(readSensorADS(0, false), 0, 32767, 0, 100);
}

void readSensorTSL()
{
    sensors_event_t eventTsl;
    tsl.getEvent(&eventTsl);
    if (eventTsl.light)
    {
        m_lightTsl = eventTsl.light;
    }
}

void readSensorVane()
{
    // Without Sensor, there is no logic
    /*
        Direction
    (degrees)
    Resistance
    （ohms）
    0 33K
    22.5 6.57K
    45 8.2K
    67.5 891
    90 1K
    112.5 688
    135 2.2K
    157.5 1.41K
    180 3.9K
    202.5 3.14K
    225 16K
    247.5 14.12K
    270 120K
    292.5 42.12K
    315 64.9K
    337.5 21.88K
        */

    c_windDirection = 0;
}

void readSensorVEML()
{
    m_uvVeml = veml.readUV();
}

void readSensors()
{
    readSensorAnemometer();
    readSensorBMP();
    readSensorDHT();
    readSensorMoist();
    readSensorTSL();
    readSensorVEML();
}