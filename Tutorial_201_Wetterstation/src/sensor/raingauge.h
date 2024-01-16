#include <Arduino.h>

void ICACHE_RAM_ATTR ISRRainGauge();
void initRainGauge();
void readRainGauge();
float getRainVolume();
boolean getRainGaugeStatus();