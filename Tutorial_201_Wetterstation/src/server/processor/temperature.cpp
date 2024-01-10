#include <Arduino.h>

#include "math\temperature.h"
#include "sensor\ads1115\thermistor.h"
#include "sensor\anemometer.h"
#include "sensor\bmp280.h"
#include "sensor\dht22.h"
#include "const.h"

String processorTemp(const String &var)
{
    if (var == "TEMPAIR")
    {
        return String(getBmp1Temperature());
    }
    else if (var == "TEMPSOIL")
    {
        return String(getAdsTemperature());
    }
    else if (var == "DEWPOINT")
    {
        return String(calculateDewPoint(getBmp1Temperature(), getDht1Humidity()));
    }
    else if (var == "WINDCHILL")
    {
        return String(calculateWindChill(getBmp1Temperature(), getAnemoSpeed()));
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