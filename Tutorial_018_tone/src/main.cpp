#include <Arduino.h>

#include "pitches.h"

int LPin = 13;

void setup()
{
  pinMode(LPin, OUTPUT);
}

void loop()
{
  tone(LPin, NOTE_C4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_D4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_E4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_F4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_G4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_G4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_A4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_A4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_A4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_A4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_G4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_F4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_F4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_F4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_F4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_F4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_F4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_E4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_E4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_G4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_G4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_G4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_G4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_G4);
  delay(200);
  noTone(LPin);
  delay(20);
  tone(LPin, NOTE_C4);
  delay(200);
  noTone(LPin);
  delay(10000);
}