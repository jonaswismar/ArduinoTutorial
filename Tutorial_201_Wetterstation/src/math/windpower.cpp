#include <Arduino.h>

#include <math.h>

const String unitBeaufort = "Bft";
const String unitFujita = "F";
const String unitEFujita = "EF";
const String unitSaffirSimpson = "Kategorie";
const String unitTorro = "T";

int calculateBeaufort(float kmh)
{
    if (kmh >= 118)
    {
        return 12;
    }
    else if (kmh >= 103)
    {
        return 11;
    }
    else if (kmh >= 89)
    {
        return 10;
    }
    else if (kmh >= 75)
    {
        return 9;
    }
    else if (kmh >= 62)
    {
        return 8;
    }
    else if (kmh >= 50)
    {
        return 7;
    }
    else if (kmh >= 39)
    {
        return 6;
    }
    else if (kmh >= 29)
    {
        return 5;
    }
    else if (kmh >= 20)
    {
        return 4;
    }
    else if (kmh >= 12)
    {
        return 3;
    }
    else if (kmh >= 6)
    {
        return 2;
    }
    else if (kmh >= 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int calculateFujita(float kmh)
{
    if (kmh >= 1188)
    {
        return 12;
    }
    else if (kmh >= 1063)
    {
        return 11;
    }
    else if (kmh >= 943)
    {
        return 10;
    }
    else if (kmh >= 827)
    {
        return 9;
    }
    else if (kmh >= 717)
    {
        return 8;
    }
    else if (kmh >= 612)
    {
        return 7;
    }
    else if (kmh >= 513)
    {
        return 6;
    }
    else if (kmh >= 419)
    {
        return 5;
    }
    else if (kmh >= 333)
    {
        return 4;
    }
    else if (kmh >= 254)
    {
        return 3;
    }
    else if (kmh >= 181)
    {
        return 2;
    }
    else if (kmh >= 118)
    {
        return 1;
    }
    else if (kmh >= 63)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int calculateEFujita(float kmh)
{
    if (kmh >= 322)
    {
        return 5;
    }
    else if (kmh >= 267)
    {
        return 4;
    }
    else if (kmh >= 218)
    {
        return 3;
    }
    else if (kmh >= 178)
    {
        return 2;
    }
    else if (kmh >= 139)
    {
        return 1;
    }
    else if (kmh >= 104)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int calculateSaffirSimpson(float kmh)
{
    if (kmh >= 252)
    {
        return 5;
    }
    else if (kmh >= 209)
    {
        return 4;
    }
    else if (kmh >= 178)
    {
        return 3;
    }
    else if (kmh >= 154)
    {
        return 2;
    }
    else if (kmh >= 119)
    {
        return 1;
    }
    else if (kmh >= 63)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int calculateTorro(float kmh)
{
    if (kmh >= 433)
    {
        return 10;
    }
    else if (kmh >= 386)
    {
        return 9;
    }
    else if (kmh >= 343)
    {
        return 8;
    }
    else if (kmh >= 300)
    {
        return 7;
    }
    else if (kmh >= 261)
    {
        return 6;
    }
    else if (kmh >= 221)
    {
        return 5;
    }
    else if (kmh >= 185)
    {
        return 4;
    }
    else if (kmh >= 149)
    {
        return 3;
    }
    else if (kmh >= 117)
    {
        return 2;
    }
    else if (kmh >= 88)
    {
        return 1;
    }
    else if (kmh >= 61)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}