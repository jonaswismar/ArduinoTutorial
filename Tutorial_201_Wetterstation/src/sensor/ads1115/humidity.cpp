#include <Arduino.h>

#include "sensor\ads1115.h"

float adsHumidity = 0;

void readAdsHumidity()
{
    adsHumidity = getAds1Volts2() / getAds1Volts1();
}

float getAdsHumidity()
{
    return adsHumidity;
}