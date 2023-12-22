#include <Arduino.h>

#include <SoftwareSerial.h>

SoftwareSerial mySerial(D5, D6);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  }
  Serial.println();
  Serial.println("ESP SoftwareSerial  test!");

  mySerial.begin(115200);

  Serial.print("Serial test - Serial 1 at  baudrate ");
  Serial.println(115200);
}

void loop()
{
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  while (Serial.available())
  {
    mySerial.write(Serial.read());
  }
}