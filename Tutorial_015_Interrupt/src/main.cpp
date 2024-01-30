#include <Arduino.h>

const int pushButton = D7;
const int ledPin = D5;

int ledState = LOW;
volatile int buttonFlag;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

IRAM_ATTR void ISR_button()
{
  buttonFlag = 1;
}

void setup()
{
  Serial.begin(9600);
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pushButton), ISR_button, CHANGE);
}

void loop()
{
  if (millis() - lastDebounceTime > debounceDelay && buttonFlag == 1)
  {
    lastDebounceTime = millis();
    if (digitalRead(pushButton) == 0 && lastButtonState == 1)
    {
      ledState = !ledState;
      Serial.println(ledState);
      digitalWrite(ledPin, ledState);
      lastButtonState = 0;
    }
    else if (digitalRead(pushButton) == 1 && lastButtonState == 0)
    {
      lastButtonState = 1;
    }
    buttonFlag = 0;
  }
}