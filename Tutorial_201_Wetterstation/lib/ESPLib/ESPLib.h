#include <Arduino.h>

uint32_t getChipId();
uint8_t getChipCores();
String getFullVersion();
uint8_t getFlashChipVendorId();
uint32_t getFlashChipRealSize();
String getResetInfo();
String getResetReason();
uint32_t getRandom();
void reset();
boolean setMAC(uint8_t);