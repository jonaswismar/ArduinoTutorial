#include <Arduino.h>

boolean statusRainGauge = false;
const int pinRainGauge = D6;
float m_rainVolume = 0;

volatile int m_rainInterruptCounter = 0;
unsigned long lastRainGaugeInterruptTime = 0;
unsigned long lastRainGaugeTime = 0;

void ICACHE_RAM_ATTR ISRRainGauge()
{
    if (millis() - lastRainGaugeInterruptTime >= 10)
    {
        lastRainGaugeInterruptTime = millis();
        m_rainInterruptCounter++;
    }
}

void initRainGauge()
{
    pinMode(pinRainGauge, INPUT_PULLUP);
    attachInterrupt(pinRainGauge, ISRRainGauge, FALLING);
    statusRainGauge = true;
}

void readRainGauge()
{
    if (millis() - lastRainGaugeTime >= 1000)
    {
        lastRainGaugeTime = millis();

        // Process anemometer data once per second
        // One contact closure (falling) = 1.492 MPH or 2.4 km/h of wind speed

        if (m_rainInterruptCounter > 0)
        {
            m_rainVolume = 2.4 * (float)m_rainInterruptCounter;
            m_rainInterruptCounter = 0;
        }
    }

    // Fake Values because i have no sensor
    m_rainVolume = random(0, 20);
}

float getRainVolume()
{
    return m_rainVolume;
}

boolean getRainGaugeStatus()
{
    return statusRainGauge;
}