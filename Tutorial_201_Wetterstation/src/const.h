#include <Arduino.h>

const long intervalSecond = 1000;
const long intervalMinute = intervalSecond * 60;
const long intervalHour = intervalMinute * 60;
const long intervalDay = intervalHour * 60;

const float seaLevelPressure = 1013.25;

const String htmlHiddenFlag = "style=\"display: none;\" ";