#include <Arduino.h>

#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

boolean statusMlx1 = false;
float ambientTemp = 0;
float objectTemp = 0;
float emissivity = 0;

void initMlx1()
{
    statusMlx1 = mlx.begin();
    if (!statusMlx1)
    {
        Serial.println("Ooops, no MLX90614 detected ... Check your wiring!");
    }
}

void readMlx1()
{
    emissivity = mlx.readEmissivity();
    ambientTemp = mlx.readAmbientTempC();
    objectTemp = mlx.readObjectTempC();
}

float getAmbientTemp()
{
    return ambientTemp;
}

float getObjectTemp()
{
    return objectTemp;
}

float getEmissivity()
{
    return emissivity;
}

boolean getStatusMlx1()
{
    return statusMlx1;
}