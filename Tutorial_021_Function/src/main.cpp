#include <Arduino.h>

int summe(int x, int y)
{
  int sum = 0;
  sum = x + y;
  return sum;
}

void setup()
{
  Serial.begin(9600);

    int zahl1 = 5;
  int zahl2 = 6;
  int result = 0;
  result = summe(zahl1, zahl2);

  Serial.println("Summe von " + String(zahl1) + " und " + String(zahl2) + " ist " + String(result));
 
}

void loop()
{
  int zahl1 = 5;
  int zahl2 = 6;
  int result = 0;
  result = summe(zahl1, zahl2);

  Serial.println("Summe von " + String(zahl1) + " und " + String(zahl2) + " ist " + String(result));
  delay(2000);
}