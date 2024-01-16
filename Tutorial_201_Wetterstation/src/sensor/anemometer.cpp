#include <Arduino.h>

boolean statusAnemo = false;
const int pinAnemo = D5;
float m_anemoSpeed = 0;
float m_anemoGust = 0;

volatile int m_anemoInterruptCounter = 0;
unsigned long lastAnemometerInterruptTime = 0;
unsigned long lastAnemometerTime = 0;

void ICACHE_RAM_ATTR ISRAnemo()
{
    if (millis() - lastAnemometerInterruptTime >= 10)
    {
        lastAnemometerInterruptTime = millis();
        m_anemoInterruptCounter++;
    }
}

void initAnemo()
{
    pinMode(pinAnemo, INPUT_PULLUP);
    attachInterrupt(pinAnemo, ISRAnemo, FALLING);
    statusAnemo = true;
}

void readAnemo()
{
    if (millis() - lastAnemometerTime >= 1000)
    {
        lastAnemometerTime = millis();

        // Process anemometer data once per second
        // One contact closure (falling) = 1.492 MPH or 2.4 km/h of wind speed

        if (m_anemoInterruptCounter > 0)
        {
            float speed = 2.4 * (float)m_anemoInterruptCounter;
            m_anemoInterruptCounter = 0;

            if (speed > m_anemoGust)
            {
                m_anemoGust = speed;
            }
            m_anemoSpeed += speed;
        }
    }

    // Fake Values because i have no sensor
    m_anemoSpeed = random(0, 360);
    m_anemoGust = random(0, 360);
}

float getAnemoSpeed()
{
    return m_anemoSpeed;
}

boolean getAnemoStatus()
{
    return statusAnemo;
}