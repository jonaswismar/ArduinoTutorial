#include <Arduino.h>

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include "location\location.h"
#include "time\ntptimeclient.h"

WiFiClient client;
HTTPClient http;

String ws_sunrise = "";
String ws_sunset = "";
String ws_solar_noon = "";
String ws_day_length = "";
String ws_civil_twilight_begin = "";
String ws_civil_twilight_end = "";
String ws_nautical_twilight_begin = "";
String ws_nautical_twilight_end = "";
String ws_astronomical_twilight_begin = "";
String ws_astronomical_twilight_end = "";

const long intervalSunrise = 60000;
unsigned long previousMillisSunrise = 0;

String getSunriseJSON(String lat, String lng)
{
    http.begin(client, "http://api.sunrise-sunset.org/json?lat=50.598143071770046&lng=8.746039867401123&date=today");
    http.GET();
    String json = http.getString();
    http.end();
    return json;
}

void parseSunriseJSON(String json)
{
    StaticJsonDocument<768> doc;
    DeserializationError error = deserializeJson(doc, json);

    if (error)
    {
        return;
    }

    JsonObject results = doc["results"];
    ws_sunrise = String(results["sunrise"]);                                         // "7:27:02 AM"
    ws_sunset = String(results["sunset"]);                                           // "5:05:55 PM"
    ws_solar_noon = String(results["solar_noon"]);                                   // "12:16:28 PM"
    ws_day_length = String(results["day_length"]);                                   // "9:38:53"
    ws_civil_twilight_begin = String(results["civil_twilight_begin"]);               // "6:58:14 AM"
    ws_civil_twilight_end = String(results["civil_twilight_end"]);                   // "5:34:43 PM"
    ws_nautical_twilight_begin = String(results["nautical_twilight_begin"]);         // "6:25:47 AM"
    ws_nautical_twilight_end = String(results["nautical_twilight_end"]);             // "6:07:10 PM"
    ws_astronomical_twilight_begin = String(results["astronomical_twilight_begin"]); // "5:54:14 ...
    ws_astronomical_twilight_end = String(results["astronomical_twilight_end"]);     // "6:38:43 PM"
}
String getSunrise()
{
    return ws_sunrise;
}
String getSunset()
{
    return ws_sunset;
}
String getSolarNoon()
{
    return ws_solar_noon;
}
String getDayLength()
{
    return ws_day_length;
}
String getCivilTwilightBegin()
{
    return ws_civil_twilight_begin;
}
String getCivilTwilightEnd()
{
    return ws_civil_twilight_end;
}
String getNauticalTwilightBegin()
{
    return ws_nautical_twilight_begin;
}
String getNauticalTwilightEnd()
{
    return ws_nautical_twilight_end;
}
String getAstronomicalTwilightBegin()
{
    return ws_astronomical_twilight_begin;
}
String getAstronomicalTwilightEnd()
{
    return ws_astronomical_twilight_end;
}

void updateSunrise()
{
    if (millis() - previousMillisSunrise >= intervalSunrise)
    {
        previousMillisSunrise = millis();
        parseSunriseJSON(getSunriseJSON(String(getLat()), String(getLng())));
    }
}
