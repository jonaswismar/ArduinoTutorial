#include <Arduino.h>

#ifndef DBG_OUTPUT_PORT
#define DBG_OUTPUT_PORT Serial
#endif

const char *host = "wetterstation";

static const char TEXT_PLAIN[] PROGMEM = "text/plain";
static const char TEXT_HTML[] PROGMEM = "text/html";
static const char IMAGE_PNG[] PROGMEM = "image/png";
static const char IMAGE_ICO[] PROGMEM = "image/ico";

static const char FS_INIT_ERROR[] PROGMEM = "FS INIT ERROR";
static const char FILE_NOT_FOUND[] PROGMEM = "FileNotFound";

const char *fsName = "SPIFFS";

const long utcOffsetInSeconds = 3600;
char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
