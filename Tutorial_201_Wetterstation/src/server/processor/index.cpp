#include <Arduino.h>

#include <Version.h>

#include <ArduinoLib.h>
#include <ESPLib.h>

#include "const.h"

String processorIndex(const String &var)
{
    if (var == "SYSESPCORE")
    {
        return getFullVersion();
    }
    else if (var == "SYSBUILDON")
    {
        return getBuildOn();
    }
    else if (var == "SYSVERSION")
    {
        return String(VERSION);
    }
    return String();
}