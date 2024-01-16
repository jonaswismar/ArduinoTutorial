#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>

#include <SparkFun_AS3935.h>

#define AS3935_ADDR 0x03
#define INDOOR 0x12
#define OUTDOOR 0xE
#define LIGHTNING_INT 0x08
#define DISTURBER_INT 0x04
#define NOISE_INT 0x01

SparkFun_AS3935 lightning(AS3935_ADDR);

boolean statusAs = false;
const int lightningInt = D4;
int distance = 0;
// This variable holds the number representing the lightning or non-lightning
// event issued by the lightning detector.
int intVal = 0;
int noise = 2;     // Value between 1-7
int disturber = 2; // Value between 1-10

void initAs()
{
    pinMode(lightningInt, INPUT);
    Wire.begin();
    statusAs = lightning.begin();
    if (!lightning.begin())
    {
        Serial.println("Lightning Detector did not start up!");
    }
    lightning.setIndoorOutdoor(OUTDOOR);
}

void readAs()
{
    if (digitalRead(lightningInt) == HIGH)
    {
        intVal = lightning.readInterruptReg();
        if (intVal == NOISE_INT)
        {
            // Serial.println("Noise.");
            //  Too much noise? Uncomment the code below, a higher number means better
            //  noise rejection.
            // lightning.setNoiseLevel(setNoiseLevel);
            distance = 0;
        }
        else if (intVal == DISTURBER_INT)
        {
            // Serial.println("Disturber.");
            //  Too many disturbers? Uncomment the code below, a higher number means better
            //  disturber rejection.
            // lightning.watchdogThreshold(threshVal);
            distance = 0;
        }
        else if (intVal == LIGHTNING_INT)
        {
            // Serial.println("Lightning Strike Detected!");
            //  Lightning! Now how far away is it? Distance estimation takes into
            //  account any previously seen events in the last 15 seconds.
            distance = lightning.distanceToStorm();
            // Serial.print("Approximately: ");
            // Serial.print(distance);
            // Serial.println("km away!");
        }
    }
    else
    {
        distance = 0;
    }
}

int getLightningDistance()
{
    return distance;
}

boolean getAsStatus()
{
    return statusAs;
}