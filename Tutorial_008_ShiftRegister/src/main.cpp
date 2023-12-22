#include <Arduino.h>

int latchPin = D8;
int clockPin = D7;
int dataPin = D6;
long randNumber;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  randomSeed(analogRead(A0));
}

void loop()
{
  randNumber = random(1, 255);
  // take the latchPin low so
  // the LEDs don't change while you're sending in bits:
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, randNumber);
  // take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
  // pause before next value:
  delay(500);
}