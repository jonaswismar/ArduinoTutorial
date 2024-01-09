#include <Arduino.h>

#include "api\moonphase.h"
#include "api\moonrise.h"
#include "location\location.h"
#include "const.h"

String processorMoon(const String &var)
{
    if (var == "MOONRISE")
    {
        return getMoonRise();
    }
    else if (var == "MOONSET")
    {
        return getMoonSet();
    }
    else if (var == "MOONPHASEIMAGE")
    {
        return String(map(getMoonPhase(), 1, 30, 0, 15));
    }
    else if (var == "MOONPHASE")
    {
        return getMoonPhaseString();
    }
    return String();
}