#include <Arduino.h>

#include <math.h>

const String unitCelsius = "°C";
const String unitFahrenheit = "°F";
const String unitKelvin = "K";
const String unitRankine = "°Ra";
const String unitReaumur = "°Re";

int unitTemperature = 0;

void setUnitTemperature(int unit)
{
    unitTemperature = unit;
}
int getUnitTemperature()
{
    return unitTemperature;
}

/*
Die Formel zur Berechnung ist:
Temperatur über 0 ° C: k2=17.62, k3=243.12
Temperatur 0 ° C oder darunter: k2=22.46, k3=272.62
Temperatur t, Luftfeuchtigkeit l
Taupunkt = k3*((k2*t)/(k3+t)+ln(l/100))/((k2*k3)/(k3+t)-ln(l/100))
*/
float calculateDewPoint(float temperature, float humidity)
{
    float k2 = 17.62;
    float k3 = 243.12;
    if (temperature <= 0)
    {
        k2 = 22.46;
        k3 = 272.62;
    }
    return k3 * ((k2 * temperature) / (k3 + temperature) + log(humidity / 100)) / ((k2 * k3) / (k3 + temperature) - log(humidity / 100));
}

/*
{\displaystyle \vartheta _{\mathrm {WCT} }=13{,}12+0{,}6215\cdot \vartheta _{\mathrm {a} }+(0{,}3965\cdot \vartheta _{\mathrm {a} }-11{,}37)\cdot v^{0{,}16}\!}
ϑWCT – Windchill-Temperatur in Grad Celsius
ϑa – Lufttemperatur in Grad Celsius
v – Windgeschwindigkeit in Kilometern pro Stunde
*/
float calculateWindChill(float temperature, float windspeed)
{
    return 13.12 + (0.6215 * temperature) + (((0.3965 * temperature) - 11.37) * pow(windspeed, 0.16));
}

float convertCelsiusToFahrenheit(float celsius)
{
    return (celsius * 9.0 / 5.0) + 32.0;
}

float convertCelsiusToReaumur(float celsius)
{
    return celsius * 0.8;
}

float convertReaumurToCelsius(float reaumur)
{
    return reaumur * 1.25;
}

float convertCelsiusToRankine(float celsius)
{
    return celsius * (9 / 5) + 491.67;
}

float convertRankineToCelsius(float rankine)
{
    return rankine * (5 / 9) - 273.15;
}

float convertCelsiusToKelvin(float celsius)
{
    return celsius + 273.15;
}

float convertKelvinToCelsius(float kelvin)
{
    return kelvin - 273.15;
}

float convertFahrenheitToCelsius(float fahrenheit)
{
    return (fahrenheit - 32.0) * (5.0 / 9.0);
}