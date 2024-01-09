#include <Arduino.h>

int redPin= D7;
int greenPin = D6;
int bluePin = D5;

int timer = 50;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  for (int luminance = 0; luminance <= 255; luminance++)
  {
    analogWrite(redPin, luminance);
    delay(timer);
  }

  for (int luminance = 0; luminance <= 255; luminance++)
  {
    analogWrite(greenPin, luminance);
    delay(greenPin);
  }

  for (int luminance = 0; luminance <= 255; luminance++)
  {
    analogWrite(bluePin, luminance);
    delay(bluePin);
  }

  
  for (int luminance = 255; luminance >= 0; luminance--)
  {
    analogWrite(redPin, luminance);
    delay(timer);
  }
  
  for (int luminance = 255; luminance >= 0; luminance--)
  {
    analogWrite(greenPin, luminance);
    delay(greenPin);
  }
  
  for (int luminance = 255; luminance >= 0; luminance--)
  {
    analogWrite(bluePin, luminance);
    delay(timer);
  }
}