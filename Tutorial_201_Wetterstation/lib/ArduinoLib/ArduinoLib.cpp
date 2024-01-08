#include <Arduino.h>

#include "ArduinoLib.h"

String getBuildOn()
{
	return F(__DATE__ " " __TIME__);
}
String getSRCFileName()
{
	return F(__FILE__);
}