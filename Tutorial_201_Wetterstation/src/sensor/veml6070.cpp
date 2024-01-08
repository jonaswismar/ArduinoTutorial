#include <Arduino.h>

#include <Adafruit_VEML6070.h>

boolean statusVeml = false;

int m_vemlUv = 0;

Adafruit_VEML6070 veml = Adafruit_VEML6070();

void initVeml()
{
    veml.begin(VEML6070_1_T);
    statusVeml = true;
}

void readVeml()
{
    m_vemlUv = veml.readUV();
}

int getVemlUV()
{
    return m_vemlUv;
}

boolean getVemlStatus()
{
    return statusVeml;
}