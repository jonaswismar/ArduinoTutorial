#include <Arduino.h>

boolean statusVane = false;

float m_vaneDirection = 0;

void initVane()
{
    statusVane = true;
}

void readVane()
{
    m_vaneDirection = random(0,360);
}

float getVaneDirection()
{
    return m_vaneDirection;
}

boolean getVaneStatus()
{
    return statusVane;
}