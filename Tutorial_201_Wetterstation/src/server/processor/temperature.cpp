#include <Arduino.h>

#include "sensor\anemometer.h"
#include "sensor\bmp280.h"
#include "sensor\dht22.h"
#include "const.h"

String processorTemp(const String &var)
{
    if (var == "TEMPAIR")
    {
        return "";
    }
    else if (var == "TEMPSOIL")
    {
        return "";
    }
    else if (var == "DEWPOINT")
    {
        return "";
    }
    else if (var == "WINDCHILL")
    {
        return "";
    }
    else if (var == "H_TEMPAIR")
    {
        if(getBmp1Status())
        {
            return "";
        }
        else
        {
            return htmlHiddenFlag;
        }
    }
    else if (var == "H_DEWPOINT")
    {
        if(getBmp1Status()&&getDht1Status())
        {
            return "";
        }
        else
        {
            return htmlHiddenFlag;
        }
    }
    else if (var == "H_WINDCHILL")
    {
        if(getBmp1Status()&&getAnemoStatus())
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