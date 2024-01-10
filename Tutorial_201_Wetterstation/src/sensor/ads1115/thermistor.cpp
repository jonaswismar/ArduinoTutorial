#include <Arduino.h>

#include "math\temperature.h"
#include "sensor\ads1115.h"

const float thermistor_resistance = 10000;
const float thermistor_nominal = 10000;
const float thermistor_bcoefficient = 3950;
const float temperature_nominal = 25;

float adsTemperature = 0;

void readAdsTemperature()
{
    float val = getAds1Volts1() / getAds1Volts3();
    float resistance = thermistor_resistance / val;

    adsTemperature = calculateSteinhartHart(resistance, thermistor_nominal, thermistor_bcoefficient, temperature_nominal);
}

float getAdsTemperature()
{
    return adsTemperature;
}