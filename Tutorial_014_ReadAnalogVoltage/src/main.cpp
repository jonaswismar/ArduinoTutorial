#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  float voltage = map(sensorValue, 0, 1024, 0, 3);
  Serial.println(voltage);
  delay(1000);
}