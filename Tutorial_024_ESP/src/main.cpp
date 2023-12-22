#include <Arduino.h>

void setup()
{
  // Befehle
  Serial.begin(9600);
  Serial.println("ESP Befehle:");
  Serial.print("getBootMode: ");
  Serial.println(ESP.getBootMode());
  Serial.print("getBootVersion: ");
  Serial.println(ESP.getBootVersion());
  Serial.print("getChipId: ");
  Serial.println(ESP.getChipId());
  Serial.print("getCoreVersion: ");
  Serial.println(ESP.getCoreVersion());
  Serial.print("getCpuFreqMHz: ");
  Serial.println(ESP.getCpuFreqMHz());
  Serial.print("getCycleCount: ");
  Serial.println(ESP.getCycleCount());
  Serial.print("getFlashChipId: ");
  Serial.println(ESP.getFlashChipId());
  Serial.print("getFlashChipMode: ");
  Serial.println(ESP.getFlashChipMode());
  Serial.print("getFlashChipRealSize: ");
  Serial.println(ESP.getFlashChipRealSize());
  Serial.print("getFlashChipSize: ");
  Serial.println(ESP.getFlashChipSize());
  Serial.print("getFlashChipSizeByChipId: ");
  Serial.println(ESP.getFlashChipSizeByChipId());
  Serial.print("getFlashChipSpeed: ");
  Serial.println(ESP.getFlashChipSpeed());
  Serial.print("getFlashChipVendorId: ");
  Serial.println(ESP.getFlashChipVendorId());
  Serial.print("getFreeContStack: ");
  Serial.println(ESP.getFreeContStack());
  Serial.print("getFreeHeap: ");
  Serial.println(ESP.getFreeHeap());
  Serial.print("getFreeSketchSpace: ");
  Serial.println(ESP.getFreeSketchSpace());
  Serial.print("getFullVersion: ");
  Serial.println(ESP.getFullVersion());
  Serial.print("getHeapFragmentation: ");
  Serial.println(ESP.getHeapFragmentation());
  Serial.print("getMaxFreeBlockSize: ");
  Serial.println(ESP.getMaxFreeBlockSize());
  Serial.print("getResetInfo: ");
  Serial.println(ESP.getResetInfo());
  Serial.print("getResetReason: ");
  Serial.println(ESP.getResetReason());
  Serial.print("getSdkVersion: ");
  Serial.println(ESP.getSdkVersion());
  Serial.print("getSketchMD5: ");
  Serial.println(ESP.getSketchMD5());
  Serial.print("getSketchSize: ");
  Serial.println(ESP.getSketchSize());
  Serial.print("getVcc: ");
  Serial.println(ESP.getVcc());
  Serial.print("random: ");
  Serial.println(ESP.random());

  // Befehle zum Steuern
  Serial.println("ESP.rebootIntoUartDownloadMode()");
  // ESP.rebootIntoUartDownloadMode()
  Serial.println("ESP.reset()");
  // ESP.reset()
  Serial.println("ESP.restart()");
  // ESP.restart()
  Serial.println("ESP.rtcUserMemoryRead()");
  // ESP.rtcUserMemoryRead()
  Serial.println("ESP.rtcUserMemoryWrite()");
  // ESP.rtcUserMemoryWrite()
}
void loop()
{
}