#include <Arduino.h>

#include <math.h>

const String unitPercent = "%";
const String unitAbsolute = "g/m3";

float calculateAbsoluteHumidity(float temperature, float humidity)
{
    return (6.112 * pow(EULER, ((17.67 * temperature) / (temperature + 243.5))) * humidity * 18.02) / ((273.15 + temperature) * 100 * 0.08314);
}