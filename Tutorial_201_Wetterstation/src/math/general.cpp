#include <Arduino.h>

#include <math.h>

int nth_digit(int value, int position)
{
  /*char buffer [4] ;
  sprintf (buffer, "%i", val) ;
  return (int)buffer[0] == '-' ? buffer [n+1] : buffer [n] ;*/

  /*unsigned int pow[] = {1, 10, 100, 1000, 10000};
  return val / pow[n] % 10;*/

  // faster
  unsigned long Pow = 1;
  for (byte D = 0; D < (position - 1); D++)
  {
    Pow *= 10;
  }
  return (value / Pow) % 10;
}