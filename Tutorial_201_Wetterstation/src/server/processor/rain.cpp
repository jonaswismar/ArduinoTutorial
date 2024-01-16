#include <Arduino.h>

#include "sensor\as3935.h"
#include "sensor\raingauge.h"
#include "const.h"

String processorRain(const String &var)
{
    if (var == "RAINCHANCE")
    {
        return "";
    }
    else if (var == "RAINVOLUME")
    {
        return String(getRainVolume());
    }
    else if (var == "H_LIGHTNINGDISTANCE")
    {
        if(getAsStatus())
        {
            return "";
        }
        else
        {
            return htmlHiddenFlag;
        }
    }
    else if (var == "LIGHTNINGDISTANCE")
    {
        return String(getLightningDistance());
    }
    return String();
}