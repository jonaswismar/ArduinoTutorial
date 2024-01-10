#include <Arduino.h>

int latchPin = D8;
int clockPin = D7;
int dataPin = D6;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  randomSeed(analogRead(A0));
}

void loop()
{
  // for (int counter = 0; counter <= 16777215; counter++)
  // for (int counter = 0; counter <= 65535; counter++)
  for (int counter = 0; counter <= 255; counter++)
  {
    // take the latchPin low so
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    // shiftOut(dataPin, clockPin, MSBFIRST, counter >> 16); // send bits X-Q
    // shiftOut(dataPin, clockPin, MSBFIRST, counter >> 8);
    shiftOut(dataPin, clockPin, MSBFIRST, counter);
    // take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(1000);
  }
}