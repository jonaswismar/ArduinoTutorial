#include <Arduino.h>

#include <Adafruit_HMC5883_U.h>

boolean statusHmc1 = false;
float headingDegrees = 0;
float heading = 0;

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(11001);

void initHmc1()
{
    statusHmc1 = mag.begin();
    if (!statusHmc1)
    {
        Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    }
}

void readHmc1()
{
    sensors_event_t event;
    mag.getEvent(&event);

    float newHeading = atan2(event.magnetic.y, event.magnetic.x);

    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
    float declinationAngle = 0.05235987756;
    newHeading += declinationAngle;

    // Correct for when signs are reversed.
    if (newHeading < 0)
    {
        newHeading += 2 * PI;
    }
    // Check for wrap due to addition of declination.
    if (newHeading > 2 * PI)
    {
        newHeading -= 2 * PI;
    }
    // Convert radians to degrees for readability.
    headingDegrees = newHeading * 180 / M_PI;
    heading = newHeading;
}

float getheading()
{
    return heading;
}

float getheadingDegrees()
{
    return headingDegrees;
}

boolean getStatusHmc1()
{
    return statusHmc1;
}