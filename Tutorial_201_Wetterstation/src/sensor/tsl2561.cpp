#include <Arduino.h>

#include <Adafruit_TSL2561_U.h>

boolean statusTsl1 = false;
boolean statusTsl2 = false;
boolean statusTsl3 = false;

float m_tsl1Light = 0;
float m_tsl2Light = 0;
float m_tsl3Light = 0;

uint16_t m_tsl1Broadband = 0;
uint16_t m_tsl2Broadband = 0;
uint16_t m_tsl3Broadband = 0;

uint16_t m_tsl1Ir = 0;
uint16_t m_tsl2Ir = 0;
uint16_t m_tsl3Ir = 0;

Adafruit_TSL2561_Unified tsl1 = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 13001);
Adafruit_TSL2561_Unified tsl2 = Adafruit_TSL2561_Unified(TSL2561_ADDR_HIGH, 13002);
Adafruit_TSL2561_Unified tsl3 = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, 13003);

void initTsl1()
{
    statusTsl1 = tsl1.begin();
    if (statusTsl1 == true)
    {
        tsl1.enableAutoRange(true);
        tsl1.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);
    }
}

void initTsl2()
{
    statusTsl2 = tsl2.begin();
    if (statusTsl2 == true)
    {
        tsl2.enableAutoRange(true);
        tsl2.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);
    }
}

void initTsl3()
{
    statusTsl3 = tsl3.begin();
    if (statusTsl3 == true)
    {
        tsl3.enableAutoRange(true);
        tsl3.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);
    }
}

void readTsl1()
{
    sensors_event_t eventTsl1;
    tsl1.getEvent(&eventTsl1);
    if (eventTsl1.light)
    {
        m_tsl1Light = eventTsl1.light;
    }
    tsl1.getLuminosity(&m_tsl1Broadband, &m_tsl1Ir);
}

void readTsl2()
{
    sensors_event_t eventTsl2;
    tsl2.getEvent(&eventTsl2);
    if (eventTsl2.light)
    {
        m_tsl2Light = eventTsl2.light;
    }
    tsl2.getLuminosity(&m_tsl2Broadband, &m_tsl2Ir);
}

void readTsl3()
{
    sensors_event_t eventTsl3;
    tsl3.getEvent(&eventTsl3);
    if (eventTsl3.light)
    {
        m_tsl3Light = eventTsl3.light;
    }
    tsl3.getLuminosity(&m_tsl3Broadband, &m_tsl3Ir);
}

float getTsl1Light()
{
    return m_tsl1Light;
}

float getTsl2Light()
{
    return m_tsl2Light;
}

float getTsl3Light()
{
    return m_tsl3Light;
}

int getTsl1Broadband()
{
    return m_tsl1Broadband;
}

int getTsl2Broadband()
{
    return m_tsl2Broadband;
}

int getTsl3Broadband()
{
    return m_tsl3Broadband;
}

int getTsl1Ir()
{
    return m_tsl1Ir;
}

int getTsl2Ir()
{
    return m_tsl2Ir;
}

int getTsl3Ir()
{
    return m_tsl3Ir;
}

boolean getTsl1Status()
{
    return statusTsl1;
}

boolean getTsl2Status()
{
    return statusTsl2;
}

boolean getTsl3Status()
{
    return statusTsl3;
}