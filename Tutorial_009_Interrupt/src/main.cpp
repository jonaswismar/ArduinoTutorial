#include <Arduino.h>

void IntCallback()
{
  Serial.print("Zeit(ms): ");
  Serial.println(millis());
}

void setup()
{
  Serial.begin(9600);
  // D5, D6, D7
  attachInterrupt(digitalPinToInterrupt(D6), IntCallback, RISING);
}

void loop()
{
}