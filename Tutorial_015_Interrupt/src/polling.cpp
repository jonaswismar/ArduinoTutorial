/*
#include <Arduino.h>

int pushButton = D6;
int ledPin = D5;

int ledStatus = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
 int buttonState = digitalRead(pushButton);
 if(buttonState == HIGH)
 {
    ledStatus = !ledStatus;
  digitalWrite(ledPin, ledStatus);
 }
  else
  {
    ledStatus = !ledStatus;
    digitalWrite(ledPin, ledStatus);
    }

}
*/