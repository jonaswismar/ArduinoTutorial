#include <Arduino.h>

#include <time.h>

#include "text/string.h"

String formattedSunDate(String original)
{
    struct tm tm = {0};
    const char *ts1 = original.c_str();
    strptime(ts1, "%I:%M:%S %P", &tm);
    if (original.endsWith("PM"))
    {
        return getLeftPaddingString(String(tm.tm_hour + 12), '0', 2) + ":" + getLeftPaddingString(String(tm.tm_min), '0', 2) + ":" + getLeftPaddingString(String(tm.tm_sec), '0', 2);
    }
    else
    {
        return getLeftPaddingString(String(tm.tm_hour), '0', 2) + ":" + getLeftPaddingString(String(tm.tm_min), '0', 2) + ":" + getLeftPaddingString(String(tm.tm_sec), '0', 2);
    }
}