#include <Arduino.h>

#include "math\winddirection.h"
#include "math\windpower.h"
#include "sensor\anemometer.h"
#include "sensor\bmp280.h"
#include "sensor\vane.h"
#include "const.h"

String processorAir(const String &var)
{
    if (var == "AIRPRESSURE")
    {
        return String(getBmp1Pressure());
    }
    else if (var == "AIRSPEED")
    {
        return String(getAnemoSpeed());
    }
    else if (var == "AIRPOWER")
    {
        return String(calculateBeaufort(getAnemoSpeed()));
    }
    else if (var == "AIRDIRECTIONIMAGE")
    {
        return getWindDirectionShortString(getVaneDirection());
    }
    else if (var == "AIRDIRECTION")
    {
        return getWindDirectionString(getVaneDirection());
    }
    else if (var == "AIRDIRECTIONDEGREE")
    {
        return String(getVaneDirection());
    }
    else if (var == "H_AIRPRESSURE")
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
    else if (var == "H_AIRSPEED")
    {
        if(getAnemoStatus())
        {
            return "";
        }
        else
        {
            return htmlHiddenFlag;
        }
    }
    else if (var == "H_AIRPOWER")
    {
        if(getAnemoStatus())
        {
            return "";
        }
        else
        {
            return htmlHiddenFlag;
        }
    }
    else if (var == "H_AIRDIRECTION")
    {
        if(getVaneStatus())
        {
            return "";
        }
        else
        {
            return htmlHiddenFlag;
        }
    }
    else if (var == "H_AIRDIRECTIONDEGREE")
    {
        if(getVaneStatus())
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