#include <Arduino.h>

#include <Ticker.h>
//#include <TimerOne.h>

int ledState = LOW;

void blinkLed(){
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Ticker timer1(blinkLed, 1000, 0, MILLIS);
  //Timer1.initialize(1000000); //Timer laufen mit Microsekunden
  //Timer1.attachInterrupt(blinkLed);
}

void loop()
{
  
}