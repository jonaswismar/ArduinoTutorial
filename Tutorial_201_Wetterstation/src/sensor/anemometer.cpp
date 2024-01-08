#include <Arduino.h>

boolean statusAnemo = false;

float m_anemoSpeed = 0;

void initAnemo()
{
    statusAnemo = true;
}

void readAnemo()
{
    m_anemoSpeed = random(0,360);
}

float getAnemoSpeed()
{
    return m_anemoSpeed;
}

boolean getAnemoStatus()
{
    return statusAnemo;
}