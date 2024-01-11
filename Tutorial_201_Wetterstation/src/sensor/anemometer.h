#include <Arduino.h>

void ICACHE_RAM_ATTR ISRAnemo();
void initAnemo();
void readAnemo();
float getAnemoSpeed();
boolean getAnemoStatus();