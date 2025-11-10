#ifndef PR_SETTINGS_H
#define PR_SETTINGS_H

#include <Arduino.h>

namespace prSettings {

//Product
const extern String VERSION_NUMBER;
const extern String BUILD_DATE;

//PIN Assignments
const extern byte STATUS_LED_PIN;
const extern bool STATUS_LED_PIN_INVERTED;
const extern byte TRIGGER_PIN;

//General
const extern String bleManufacturerTarget;

//Internal
extern String bleMAC;
extern bool bleScanMode;

} //namespace prSettings

#endif
