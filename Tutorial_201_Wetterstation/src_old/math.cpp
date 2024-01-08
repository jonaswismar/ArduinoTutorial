#include <Arduino.h>

#include <math.h>

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

float convertFahrenheitToCelsius(float fahrenheit)
{
    return (fahrenheit - 32.0) * (5.0 / 9.0);
}

int calculateBeaufort(float windspeed)
{
    if (windspeed >= 118)
    {
        return 12;
    }
    else if (windspeed >= 103)
    {
        return 11;
    }
    else if (windspeed >= 89)
    {
        return 10;
    }
    else if (windspeed >= 75)
    {
        return 9;
    }
    else if (windspeed >= 62)
    {
        return 8;
    }
    else if (windspeed >= 50)
    {
        return 7;
    }
    else if (windspeed >= 39)
    {
        return 6;
    }
    else if (windspeed >= 29)
    {
        return 5;
    }
    else if (windspeed >= 20)
    {
        return 4;
    }
    else if (windspeed >= 12)
    {
        return 3;
    }
    else if (windspeed >= 6)
    {
        return 2;
    }
    else if (windspeed >= 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int calculateFujita(float windspeed)
{
    if (windspeed >= 1188)
    {
        return 12;
    }
    else if (windspeed >= 1063)
    {
        return 11;
    }
    else if (windspeed >= 943)
    {
        return 10;
    }
    else if (windspeed >= 827)
    {
        return 9;
    }
    else if (windspeed >= 717)
    {
        return 8;
    }
    else if (windspeed >= 612)
    {
        return 7;
    }
    else if (windspeed >= 513)
    {
        return 6;
    }
    else if (windspeed >= 419)
    {
        return 5;
    }
    else if (windspeed >= 333)
    {
        return 4;
    }
    else if (windspeed >= 254)
    {
        return 3;
    }
    else if (windspeed >= 181)
    {
        return 2;
    }
    else if (windspeed >= 118)
    {
        return 1;
    }
    else if (windspeed >= 63)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int calculateEFujita(float windspeed)
{
    if (windspeed >= 322)
    {
        return 5;
    }
    else if (windspeed >= 267)
    {
        return 4;
    }
    else if (windspeed >= 218)
    {
        return 3;
    }
    else if (windspeed >= 178)
    {
        return 2;
    }
    else if (windspeed >= 139)
    {
        return 1;
    }
    else if (windspeed >= 104)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int calculateSaffirSimpson(float windspeed)
{
    if (windspeed >= 252)
    {
        return 5;
    }
    else if (windspeed >= 209)
    {
        return 4;
    }
    else if (windspeed >= 178)
    {
        return 3;
    }
    else if (windspeed >= 154)
    {
        return 2;
    }
    else if (windspeed >= 119)
    {
        return 1;
    }
    else if (windspeed >= 63)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int calculateTorro(float windspeed)
{
    if (windspeed >= 433)
    {
        return 10;
    }
    else if (windspeed >= 386)
    {
        return 9;
    }
    else if (windspeed >= 343)
    {
        return 8;
    }
    else if (windspeed >= 300)
    {
        return 7;
    }
    else if (windspeed >= 261)
    {
        return 6;
    }
    else if (windspeed >= 221)
    {
        return 5;
    }
    else if (windspeed >= 185)
    {
        return 4;
    }
    else if (windspeed >= 149)
    {
        return 3;
    }
    else if (windspeed >= 117)
    {
        return 2;
    }
    else if (windspeed >= 88)
    {
        return 1;
    }
    else if (windspeed >= 61)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
float calculateHumidityAbsolut(float temperature, float humidity)
{
    float e = 2.71828;
    return (6.112 * pow(e, ((17.67 * temperature) / (temperature + 243.5))) * humidity * 18.02) / ((273.15 + temperature) * 100 * 0.08314);
}