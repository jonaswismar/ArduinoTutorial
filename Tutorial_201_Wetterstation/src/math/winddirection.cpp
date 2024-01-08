#include <Arduino.h>

#include <math.h>

float offsetDegrees = 0;

const char directionNames[16][16] = {"Nord", "Nord-Nord-Ost", "Nord-Ost", "Ost-Nord-Ost", "Ost", "Ost-Süd-Ost", "Süd-Ost", "Süd-Süd-Ost", "Süd", "Süd-Süd-West", "Süd-West", "West-Süd-West", "West", "West-Nord-West", "Nord-West", "Nord-Nord-West"};
const char directionShortNames[16][4] = {"N", "NNO", "NO", "ONO", "O", "OSO", "SO", "SSO", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};

int getWindDirectionNumber(float direction)
{
    direction = direction - 12.5;
    if (direction < 22.5)
    {
        return 0;
    }
    else if (direction >= 22.5 && direction < 45)
    {
        return 1;
    }
    else if (direction >= 45 && direction < 67.5)
    {
        return 2;
    }
    else if (direction >= 67.5 && direction < 90)
    {
        return 3;
    }
    else if (direction >= 90 && direction < 112.5)
    {
        return 4;
    }
    else if (direction >= 112.5 && direction < 135)
    {
        return 5;
    }
    else if (direction >= 135 && direction < 157.5)
    {
        return 6;
    }
    else if (direction >= 157.5 && direction < 180)
    {
        return 7;
    }
    else if (direction >= 180 && direction < 202.5)
    {
        return 8;
    }
    else if (direction >= 202.5 && direction < 225)
    {
        return 9;
    }
    else if (direction >= 225 && direction < 247.5)
    {
        return 10;
    }
    else if (direction >= 247.5 && direction < 270)
    {
        return 11;
    }
    else if (direction >= 270 && direction < 292.5)
    {
        return 12;
    }
    else if (direction >= 292.5 && direction < 315)
    {
        return 13;
    }
    else if (direction >= 315 && direction < 337.5)
    {
        return 14;
    }
    else
    {
        return 15;
    }
}

String getWindDirectionString(float direction)
{
    float realDirection = direction - offsetDegrees;
    return directionNames[getWindDirectionNumber(realDirection)];
}

String getWindDirectionShortString(float direction)
{
    float realDirection = direction - offsetDegrees;
    return directionShortNames[getWindDirectionNumber(realDirection)];
}