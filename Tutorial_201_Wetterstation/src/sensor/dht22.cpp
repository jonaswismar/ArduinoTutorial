#include <Arduino.h>

#include <DHT.h>
#include <DHT_U.h>

boolean statusDht1 = false;

float m_dht1Temperature = 0;
float m_dht1Humidity = 0;

DHT_Unified dht1(D3, DHT22);

void initDht1()
{
    dht1.begin();
    statusDht1 = true;
}

void readDht1()
{
    sensors_event_t eventDht;
    dht1.temperature().getEvent(&eventDht);
    if (isnan(eventDht.temperature))
    {
    }
    else
    {
        m_dht1Temperature = eventDht.temperature;
    }

    dht1.humidity().getEvent(&eventDht);
    if (isnan(eventDht.relative_humidity))
    {
    }
    else
    {
        m_dht1Humidity = eventDht.relative_humidity;
    }
}

float getDht1Temperature()
{
    return m_dht1Temperature;
}

float getDht1Humidity()
{
    return m_dht1Humidity;
}

boolean getDht1Status()
{
    return statusDht1;
}