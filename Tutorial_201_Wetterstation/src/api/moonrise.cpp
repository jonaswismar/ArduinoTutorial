#include <Arduino.h>

#include <MoonRise.h>

#include "location\location.h"
#include "time\ntptimeclient.h"

MoonRise mr;

String getMoonRise()
{
    mr.calculate(getLat(), getLng(), getNTPTimeEpochTime());
    time_t moonRiseTime = mr.riseTime;
    char buff[20];
    strftime(buff, 20, "%Y.%m.%d %H:%M:%S", localtime(&moonRiseTime));
    return String(buff);
}

String getMoonSet()
{
    mr.calculate(getLat(), getLng(), getNTPTimeEpochTime());
    time_t moonSetTime = mr.setTime;
    char buff[20];
    strftime(buff, 20, "%Y.%m.%d %H:%M:%S", localtime(&moonSetTime));
    return String(buff);
}