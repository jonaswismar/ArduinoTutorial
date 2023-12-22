#include <Arduino.h>
#include <Joystick.h>
#include <AxisJoystick.h>

#define SW_PIN D0
#define VRX_PIN A0
// #define VRY_PIN A1
#define VRY_PIN A0
#define ADC_MIN 0
#define ADC_MAX 1023
#define AXES_DEVIATION 100

Joystick *joystick;

String moveTitle(const Joystick::Move move)
{
  switch (move)
  {
  case Joystick::Move::NOT:
    return "NOT";
  case Joystick::Move::PRESS:
    return "PRESS";
  case Joystick::Move::UP:
    return "UP";
  case Joystick::Move::DOWN:
    return "DOWN";
  case Joystick::Move::RIGHT:
    return "RIGHT";
  case Joystick::Move::LEFT:
    return "LEFT";
  default:
    return "???";
  }
}

void setup()
{
  Serial.begin(9600);

  joystick = new AxisJoystick(SW_PIN, VRX_PIN, VRY_PIN);
  joystick->calibrate(ADC_MIN, ADC_MAX, AXES_DEVIATION);
}

void loop()
{
  Serial.print("SingleRead: " + moveTitle(joystick->singleRead()));
  Serial.println(" | MultipleRead: " + moveTitle(joystick->multipleRead()));

  delay(500);
}