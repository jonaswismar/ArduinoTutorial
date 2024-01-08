#include <Arduino.h>

#include <time.h>
#include <sunset.h>

#include "location\location.h"
#include "time\ntptimeclient.h"

SunSet sun;

const char moonPhaseNames[8][21] = {"Neumond", "erstes Viertel", "zunehmender Halbmond", "zweites Viertel", "Vollmond", "drittes Viertel", "abnehmender Halbmond", "letztes Viertel"};

int getMoonPhase()
{
    sun.setPosition(getLat(), getLng(), 1.0);
    sun.setCurrentDate(getNTPTimeYear(), getNTPTimeMonth(), getNTPTimeDay());
    int moonphase = sun.moonPhase(std::time(nullptr));
    return moonphase;
}
String getMoonPhaseString()
{
    int mappedPhase = map(getMoonPhase(), 1, 30, 0, 15);
    if (mappedPhase == 0 || mappedPhase == 15)
    {
        return moonPhaseNames[0];
    }
    else if (mappedPhase == 1 || mappedPhase == 2)
    {
        return moonPhaseNames[1];
    }
    else if (mappedPhase == 3 || mappedPhase == 4)
    {
        return moonPhaseNames[2];
    }
    else if (mappedPhase == 5 || mappedPhase == 6)
    {
        return moonPhaseNames[3];
    }
    else if (mappedPhase == 7 || mappedPhase == 8)
    {
        return moonPhaseNames[4];
    }
    else if (mappedPhase == 9 || mappedPhase == 10)
    {
        return moonPhaseNames[5];
    }
    else if (mappedPhase == 11 || mappedPhase == 12)
    {
        return moonPhaseNames[6];
    }
    else
    {
        return moonPhaseNames[7];
    }
}
