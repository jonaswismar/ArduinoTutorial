#include <Arduino.h>

#include <Adafruit_ADS1X15.h>

boolean statusAds1 = false;
boolean statusAds2 = false;
boolean statusAds3 = false;
boolean statusAds4 = false;

float ads1volts1 = 0;
float ads1volts2 = 0;
float ads1volts3 = 0;
float ads1volts4 = 0;
float ads2volts1 = 0;
float ads2volts2 = 0;
float ads2volts3 = 0;
float ads2volts4 = 0;
float ads3volts1 = 0;
float ads3volts2 = 0;
float ads3volts3 = 0;
float ads3volts4 = 0;
float ads4volts1 = 0;
float ads4volts2 = 0;
float ads4volts3 = 0;
float ads4volts4 = 0;

Adafruit_ADS1115 ads1;
Adafruit_ADS1115 ads2;
Adafruit_ADS1115 ads3;
Adafruit_ADS1115 ads4;

void initAds1()
{
    statusAds1 = ads1.begin();
    if (statusAds1 == true)
    {
        ads1.setGain(GAIN_ONE);
    }
}

void initAds2()
{
    statusAds2 = ads2.begin();
    if (statusAds2 == true)
    {
        ads2.setGain(GAIN_ONE);
    }
}

void initAds3()
{
    statusAds3 = ads3.begin();
    if (statusAds3 == true)
    {
        ads3.setGain(GAIN_ONE);
    }
}

void initAds4()
{
    statusAds4 = ads4.begin();
    if (statusAds4 == true)
    {
        ads4.setGain(GAIN_ONE);
    }
}

void readAds1()
{
    if (statusAds1 == true)
    {
        int16_t adc1, adc2, adc3, adc4;
        adc1 = ads1.readADC_SingleEnded(0);
        adc2 = ads1.readADC_SingleEnded(1);
        adc3 = ads1.readADC_SingleEnded(2);
        adc4 = ads1.readADC_SingleEnded(3);

        ads1volts1 = ads1.computeVolts(adc1);
        ads1volts2 = ads1.computeVolts(adc2);
        ads1volts3 = ads1.computeVolts(adc3);
        ads1volts4 = ads1.computeVolts(adc4);
    }
}

void readAds2()
{
    if (statusAds2 == true)
    {
        int16_t adc1, adc2, adc3, adc4;
        adc1 = ads2.readADC_SingleEnded(0);
        adc2 = ads2.readADC_SingleEnded(1);
        adc3 = ads2.readADC_SingleEnded(2);
        adc4 = ads2.readADC_SingleEnded(3);

        ads2volts1 = ads2.computeVolts(adc1);
        ads2volts2 = ads2.computeVolts(adc2);
        ads2volts3 = ads2.computeVolts(adc3);
        ads2volts4 = ads2.computeVolts(adc4);
    }
}

void readAds3()
{
    if (statusAds3 == true)
    {
        int16_t adc1, adc2, adc3, adc4;
        adc1 = ads3.readADC_SingleEnded(0);
        adc2 = ads3.readADC_SingleEnded(1);
        adc3 = ads3.readADC_SingleEnded(2);
        adc4 = ads3.readADC_SingleEnded(3);

        ads3volts1 = ads3.computeVolts(adc1);
        ads3volts2 = ads3.computeVolts(adc2);
        ads3volts3 = ads3.computeVolts(adc3);
        ads3volts4 = ads3.computeVolts(adc4);
    }
}

void readAds4()
{
    if (statusAds4 == true)
    {
        int16_t adc1, adc2, adc3, adc4;
        adc1 = ads4.readADC_SingleEnded(0);
        adc2 = ads4.readADC_SingleEnded(1);
        adc3 = ads4.readADC_SingleEnded(2);
        adc4 = ads4.readADC_SingleEnded(3);

        ads4volts1 = ads4.computeVolts(adc1);
        ads4volts2 = ads4.computeVolts(adc2);
        ads4volts3 = ads4.computeVolts(adc3);
        ads4volts4 = ads4.computeVolts(adc4);
    }
}

float getAds1Volts1()
{
    return ads1volts1;
}

float getAds1Volts2()
{
    return ads1volts2;
}

float getAds1Volts3()
{
    return ads1volts3;
}

float getAds1Volts4()
{
    return ads1volts4;
}

float getAds2Volts1()
{
    return ads2volts1;
}

float getAds2Volts2()
{
    return ads2volts2;
}

float getAds2Volts3()
{
    return ads2volts3;
}

float getAds2Volts4()
{
    return ads2volts4;
}

float getAds3Volts1()
{
    return ads3volts1;
}

float getAds3Volts2()
{
    return ads3volts2;
}

float getAds3Volts3()
{
    return ads3volts3;
}

float getAds3Volts4()
{
    return ads3volts4;
}

float getAds4Volts1()
{
    return ads4volts1;
}

float getAds4Volts2()
{
    return ads4volts2;
}

float getAds4Volts3()
{
    return ads4volts3;
}

float getAds4Volts4()
{
    return ads4volts4;
}

boolean getAds1Status()
{
    return statusAds1;
}

boolean getAds2Status()
{
    return statusAds2;
}

boolean getAds3Status()
{
    return statusAds3;
}

boolean getAds4Status()
{
    return statusAds4;
}