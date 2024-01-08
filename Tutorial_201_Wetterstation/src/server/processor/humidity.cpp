#include <Arduino.h>

#include "sensor\bmp280.h"
#include "sensor\dht22.h"
#include "const.h"

String processorHumi(const String &var)
{
    if (var == "HUMISOIL")
    {
        return "";
    }
    else if (var == "HUMIAIR")
    {
        return "";
    }
    else if (var == "HUMIABSOL")
    {
        return "";
    }
    else if (var == "H_HUMIAIR")
    {
        if(getDht1Status())
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
        if(getBmp1Status()&&getDht1Status())
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