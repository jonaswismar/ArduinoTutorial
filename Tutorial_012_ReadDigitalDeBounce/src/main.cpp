#include <Arduino.h>

const int pushButton = D8;
const int ledPin = D5;

int ledState = LOW;
int buttonState;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup()
{
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop()
{
  int reading = digitalRead(pushButton);
  Serial.println(reading);

  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      Serial.println(buttonState);
      buttonState = reading;

      if (buttonState == HIGH)
      {
        ledState = !ledState;
      }
    }
  }

  digitalWrite(ledPin, ledState);

  lastButtonState = reading;
}