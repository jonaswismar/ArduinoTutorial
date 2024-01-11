#include <Arduino.h>

void ICACHE_RAM_ATTR ISRRainGauge();
void initRainGauge();
void readAnemo();
float getRainVolume();
boolean getRainGaugeStatus();