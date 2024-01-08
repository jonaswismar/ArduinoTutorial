#include <Arduino.h>

#include <math.h>

void setUnitTemperature(int);
int getUnitTemperature();
float calculateDewPoint(float, float);
float calculateWindChill(float, float);
float convertCelsiusToFahrenheit(float);
float convertCelsiusToReaumur(float);
float convertReaumurToCelsius(float);
float convertCelsiusToRankine(float);
float convertRankineToCelsius(float);
float convertCelsiusToKelvin(float);
float convertKelvinToCelsius(float);
float convertFahrenheitToCelsius(float);