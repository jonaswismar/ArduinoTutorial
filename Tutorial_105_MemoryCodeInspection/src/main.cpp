#include <Arduino.h>

// Incorrect function declaration
void myFunction();

// Uninitialized global variable
int uninitializedVar;

void setup()
{
  Serial.begin(9600);

  // OutOfBounds
  int ledPins[] = {1, 2, 3, 4, 5};
  Serial.print(ledPins[10]);

  // Unused variable
  int unusedVar;

  // Unreachable code
  if (1 == 0)
  {
    Serial.println("This should never be printed");
  }

  // Division by zero
  int result = 10 / 0;

  // Incorrect format specifier
  Serial.println("String with %d placeholder");

  // Type mismatch
  int value = "This should be a string";

  // Buffer overflow
  char buffer[5];
  strcpy(buffer, "This is a long string that causes a buffer overflow");

  // Memory leak
  char *dynamicString = new char[10];

  // Missing return statement
  if (value > 5)
  {
    return;
  }
}

void loop()
{
  // Endless loop
  while (1)
  {
    Serial.println("Stuck in an endless loop");
  }
}

// Undefined function
void undefinedFunction()
{
  Serial.println("Undefined function");
}

// Function without return
int withoutReturnFunction()
{
}