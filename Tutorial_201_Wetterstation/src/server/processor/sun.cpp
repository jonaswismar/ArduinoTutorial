#include <Arduino.h>

#include "client\sunrise.h"
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
    return String();
}