#include <Arduino.h>

#include <math.h>

#include "const.h"

const String unitHectoPascal = "hPa";
const String unitPascal = "Pa";
const String unitAtmosphere = "atm";
const String unitTorr = "Torr";
const String unitMercury = "mmHg";

float convertHpaToPa(float hpa)
{
    return hpa * 100;
}

float convertPaToHpa(float pa)
{
    return pa / 100;
}

float convertHpaToAtm(float hpa)
{
    return hpa * seaLevelPressure;
}

float convertAtmToHpa(float atm)
{
    return atm / seaLevelPressure;
}

float convertHpaToTorr(float hpa)
{
    return hpa / 1.33322;
}

float convertTorrToHpa(float torr)
{
    return torr * 1.33322;
}

float convertHpaToHg(float hpa)
{
    return hpa / 1.33322;
}

float convertTorrToHg(float hg)
{
    return hg * 1.33322;
}