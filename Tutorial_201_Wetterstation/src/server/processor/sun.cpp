#include <Arduino.h>

#include "web\sunrise.h"
#include "sensor\tsl2561.h"
#include "sensor\veml6070.h"
#include "time\parser.h"
#include "const.h"

String processorSun(const String &var)
{
    if (var == "SUNRISE")
    {
        return formattedSunDate(getSunrise());
    }
    else if (var == "SUNSET")
    {
        return formattedSunDate(getSunset());
    }
    else if (var == "SUNNOON")
    {
        return formattedSunDate(getSolarNoon());
    }
    else if (var == "SUNLENGTH")
    {
        return getDayLength();
    }
    else if (var == "SUNUV")
    {
        return String(getVemlUV());
    }
    else if (var == "SUNIR")
    {
        return String(getTsl1Ir());
    }
    else if (var == "SUNBB")
    {
        return String(getTsl1Broadband());
    }
    else if (var == "SUNHELL")
    {
        return String(getTsl1Light());
    }
    else if (var == "H_SUNUV")
    {
        if(getVemlStatus())
        {
            return "";
        }
        else
        {
            return htmlHiddenFlag;
        }
    }
    else if (var == "H_SUNIR"||var == "H_SUNBB"||var == "H_SUNHELL")
    {
        if(getTsl1Status())
        {
            return "";
        }
        else
        {
            return htmlHiddenFlag;
        }
    }
    return String();
}