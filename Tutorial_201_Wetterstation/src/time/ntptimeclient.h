#include <Arduino.h>
time_t getNTPTimeEpochTime();
void initNTPTimeClient();
void updateNTPTimeClient();
boolean isNTPTimeSummertime();
String getNTPTimeFormattedTime();
String getNTPTimeFormattedDate();
int getNTPTimeYear();
int getNTPTimeMonth();
int getNTPTimeDay();
int getNTPTimeDayOfWeek();
String getNTPTimeDayOfWeekString();
int getNTPTimeHours();
int getNTPTimeMinutes();
int getNTPTimeSeconds();
int getNTPTimeSeason();
String getNTPTimeSeasonString();
int getNTPTimeDaytime();
String getNTPTimeDaytimeString();