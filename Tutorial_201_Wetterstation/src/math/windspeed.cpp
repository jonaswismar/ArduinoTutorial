#include <Arduino.h>

#include <math.h>

const String unitKmh = "km/h";
const String unitMs = "m/s";
const String unitKnots = "kn";

float calculateKmhToKnots(float kmh)
{
    return kmh / 1.852;
}

float calculateKnotsToKmh(float kn)
{
    return kn * 1.852;
}

float calculateKmhToMs(float kmh)
{
    return kmh / 3.6;
}

float calculateMsToKmh(float ms)
{
    return ms * 3.6;
}