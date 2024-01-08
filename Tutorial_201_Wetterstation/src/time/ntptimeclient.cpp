#include <Arduino.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

#include "text/string.h"

const char seasonNames[4][10] = {"Winter", "Frühling", "Sommer", "Herbst"};
const char monthNames[12][10] = {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};
const char dayOfTheWeekNames[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
const char timeOfDayNames[6][12] = {"Morgen", "Vormittag", "Mittag", "Nachmittag", "Abend", "Nacht"};

const long utcOffsetInSeconds = 3600;

const long intervalNTPClient = 60000;
unsigned long previousMillisNTPClient = 0;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds);

void initNTPTimeClient()
{
    timeClient.begin();
}

void updateNTPTimeClient()
{
    if (millis() - previousMillisNTPClient >= intervalNTPClient)
    {
        previousMillisNTPClient = millis();
        timeClient.update();
    }
}

String getNTPTimeFormattedTime()
{
    return timeClient.getFormattedTime();
}

time_t getNTPTimeEpochTime()
{
    return timeClient.getEpochTime();
}

String getNTPTimeFormattedDate()
{
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((time_t *)&epochTime);
    int currentYear = ptm->tm_year + 1900;
    int currentMonth = ptm->tm_mon + 1;
    int monthDay = ptm->tm_mday;
    return getLeftPaddingString(String(monthDay), '0', 2) + "." + getLeftPaddingString(String(currentMonth), '0', 2) + "." + String(currentYear);
}

int getNTPTimeYear()
{
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((time_t *)&epochTime);
    int currentYear = ptm->tm_year + 1900;
    return currentYear;
}

int getNTPTimeMonth()
{
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((time_t *)&epochTime);
    int currentMonth = ptm->tm_mon + 1;
    return currentMonth;
}

String getNTPTimeMonthString()
{
    return monthNames[getNTPTimeMonth()];
}

int getNTPTimeDay()
{
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((time_t *)&epochTime);
    int monthDay = ptm->tm_mday;
    return monthDay;
}

int getNTPTimeDayOfWeek()
{
    return timeClient.getDay();
}

String getNTPTimeDayOfWeekString()
{
    return dayOfTheWeekNames[getNTPTimeDayOfWeek()];
}

int getNTPTimeHours()
{
    return timeClient.getHours();
}

int getNTPTimeMinutes()
{
    return timeClient.getMinutes();
}

int getNTPTimeSeconds()
{
    return timeClient.getSeconds();
}

int getNTPTimeSeason()
{
    int day = getNTPTimeDay();
    int month = getNTPTimeMonth();
    int season = 0;
    if (month <= 3)
    {
        season = 0;
    }
    else if (month >= 4 && month <= 6)
    {
        season = 1;
    }
    else if (month >= 7 && month <= 9)
    {
        season = 2;
    }
    else if (month >= 10 && month <= 12)
    {
        season = 3;
    }
    // make correction for solstices/equinoxes
    if (month % 3 == 0 && day >= 21)
    {
        if (season == 0)
        {
            season = 1;
        }
        else if (season == 1)
        {
            season = 2;
        }
        else if (season == 2)
        {
            season = 3;
        }
        else
        {
            season = 0;
        }
    }
    return season;
}

String getNTPTimeSeasonString()
{
    return seasonNames[getNTPTimeSeason()];
}

boolean isNTPTimeSummertime()
{
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((time_t *)&epochTime);
    int currentYear = ptm->tm_year + 1900;
    int currentMonth = ptm->tm_mon + 1;
    int monthDay = ptm->tm_mday;
    int tzHours = 0;
    int hour = timeClient.getHours();
    if (currentMonth < 3 || currentMonth > 10)
    {
        return false; // keine Sommerzeit in Jan, Feb, Nov, Dez
    }
    else if (currentMonth > 3 && currentMonth < 10)
    {
        return true; // Sommerzeit in Apr, Mai, Jun, Jul, Aug, Sep
    }
    else if ((currentMonth == 3 && (hour + 24 * monthDay) >= (1 + tzHours + 24 * (31 - (5 * currentYear / 4 + 4) % 7))) || (currentMonth == 10 && (hour + 24 * monthDay) < (1 + tzHours + 24 * (31 - (5 * currentYear / 4 + 1) % 7))))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int getNTPTimeDaytime()
{
    boolean summertime = isNTPTimeSummertime();
    int hour = getNTPTimeHours();
    if (summertime == true)
    {
        if (hour >= 7 && hour < 11)
        {
            return 0;
        }
        else if (hour >= 11 && hour < 13)
        {
            return 1;
        }
        else if (hour >= 13 && hour < 15)
        {
            return 2;
        }
        else if (hour >= 15 && hour < 18)
        {
            return 3;
        }
        else if (hour >= 18 && hour < 22)
        {
            return 4;
        }
        else if (hour >= 22 || hour < 7)
        {
            return 5;
        }
        return 0;
    }
    else
    {
        if (hour >= 6 && hour < 10)
        {
            return 0;
        }
        else if (hour >= 10 && hour < 12)
        {
            return 1;
        }
        else if (hour >= 12 && hour < 14)
        {
            return 2;
        }
        else if (hour >= 14 && hour < 17)
        {
            return 3;
        }
        else if (hour >= 17 && hour < 21)
        {
            return 4;
        }
        else if (hour >= 21 || hour < 6)
        {
            return 5;
        }
        return 0;
    }
    return 0;
}
String getNTPTimeDaytimeString()
{
    return timeOfDayNames[getNTPTimeDaytime()];
}