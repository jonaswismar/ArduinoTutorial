#include <Arduino.h>

int pushButton = D6;
int ledPin = D5;

volatile int ledStatus = LOW;

void unserInterruptHandler()
{
  ledStatus = !ledStatus;
  digitalWrite(ledPin, ledStatus);
}

void setup()
{
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(ledPin, OUTPUT);
  // D5, D6, D7
  attachInterrupt(digitalPinToInterrupt(pushButton), unserInterruptHandler, RISING);
}

void loop()
{
  int buttonState = digitalRead(pushButton);
  if (buttonState == HIGH)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}