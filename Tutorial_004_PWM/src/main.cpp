#include <Arduino.h>

int timer = 50;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  for (int luminance = 0; luminance <= 255; luminance++)
  {
    analogWrite(LED_BUILTIN, luminance);
    delay(timer);
  }

  for (int luminance = 255; luminance >= 0; luminance--)
  {
    analogWrite(LED_BUILTIN, luminance);
    delay(timer);
  }
}