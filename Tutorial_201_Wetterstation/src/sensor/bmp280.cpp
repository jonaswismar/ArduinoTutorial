#include <Arduino.h>

#include <Adafruit_BMP280.h>

#include "const.h"

boolean statusBmp1 = false;

float m_bmp1Temperature = 0;
float m_bmp1Pressure = 0;
float m_bmp1Altitude = 0;

Adafruit_BMP280 bmp1;

void initBmp1()
{
    statusBmp1 = bmp1.begin(0x76);
    if (statusBmp1 == true)
    {
        bmp1.setSampling(Adafruit_BMP280::MODE_NORMAL, Adafruit_BMP280::SAMPLING_X2, Adafruit_BMP280::SAMPLING_X16, Adafruit_BMP280::FILTER_X16, Adafruit_BMP280::STANDBY_MS_500);
    }
}

void readBmp1()
{
    m_bmp1Temperature = bmp1.readTemperature();
    m_bmp1Pressure = bmp1.readPressure();
    m_bmp1Altitude = bmp1.readAltitude(seaLevelPressure);
}

float getBmp1Temperature()
{
    return m_bmp1Temperature;
}

float getBmp1Pressure()
{
    return m_bmp1Pressure;
}

float getBmp1Altitude()
{
    return m_bmp1Altitude;
}

boolean getBmp1Status()
{
    return statusBmp1;
}