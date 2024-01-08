#include <Arduino.h>

#include "time\ntptimeclient.h"
#include "const.h"

String processorTime(const String &var)
{
    if (var == "DAYNAMEIMAGE")
    {
        int dayOfWeek = getNTPTimeDayOfWeek();
        return F("day") + String(dayOfWeek);
    }
    else if (var == "DAYNAME")
    {
        return getNTPTimeDayOfWeekString();
    }
    else if (var == "DAYIMAGE")
    {
        int day = getNTPTimeDay();
        return String(day);
    }
    else if (var == "DAY")
    {
        return getNTPTimeFormattedDate();
    }
    else if (var == "TIME")
    {
        return getNTPTimeFormattedTime();
    }
    else if (var == "DAYTIMEIMAGE")
    {
        int daytime = getNTPTimeDaytime();
        switch (daytime)
        {
        case 0:
            return String("0");
            break;
        case 1:
            return String("0");
            break;
        case 2:
            return String("2");
        case 3:
            return String("2");
        case 4:
            return String("4");
        case 5:
            return String("5");
            break;
        default:
            return String("0");
            break;
        }
    }
    else if (var == "DAYTIME")
    {
        return getNTPTimeDaytimeString();
    }
    else if (var == "SEASONIMAGE")
    {
        int season = getNTPTimeSeason();
        return String(season);
    }
    else if (var == "SEASON")
    {
        return getNTPTimeSeasonString();
    }
    return String();
}