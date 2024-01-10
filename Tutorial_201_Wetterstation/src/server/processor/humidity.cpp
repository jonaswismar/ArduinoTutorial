#include <Arduino.h>

#include "math\humidity.h"
#include "sensor\ads1115\humidity.h"
#include "sensor\bmp280.h"
#include "sensor\dht22.h"
#include "const.h"

String processorHumi(const String &var)
{
    if (var == "HUMISOIL")
    {
        return String(getAdsHumidity());
    }
    else if (var == "HUMIAIR")
    {
        return String(getDht1Humidity());
    }
    else if (var == "HUMIABSOL")
    {
        return String(calculateAbsoluteHumidity(getBmp1Temperature(), getDht1Humidity()));
    }
    else if (var == "H_HUMIAIR")
    {
        if (getDht1Status())
        {
            return "";
        }
        else
        {
            return htmlHiddenFlag;
        }
    }
    else if (var == "H_HUMIABSOL")
    {
        if (getBmp1Status() && getDht1Status())
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