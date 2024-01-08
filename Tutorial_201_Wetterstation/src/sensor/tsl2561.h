#include <Arduino.h>

#include <Adafruit_TSL2561_U.h>

void initTsl1();
void initTsl2();
void initTsl3();
void readTsl1();
void readTsl2();
void readTsl3();
float getTsl1Light();
float getTsl2Light();
float getTsl3Light();
int getTsl1Broadband();
int getTsl2Broadband();
int getTsl3Broadband();
int getTsl1Ir();
int getTsl2Ir();
int getTsl3Ir();
boolean getTsl1Status();
boolean getTsl2Status();
boolean getTsl3Status();