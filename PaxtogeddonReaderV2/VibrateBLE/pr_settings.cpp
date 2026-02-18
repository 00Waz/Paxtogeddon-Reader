#include "pr_settings.h"

namespace prSettings {

//Product
const String VERSION_NUMBER = "1.0";
const String BUILD_DATE = "2025-11-02";

//PIN Assignments
const byte STATUS_LED_PIN = 2;               //[ OUTPUT ] -> Built-in LED
const bool STATUS_LED_PIN_INVERTED = false;  //True indicates the built-in LED is inverted: 0 is ON
const byte TRIGGER_PIN = 17;                 //[ INPUT  ] -> BLE send data trigger pin

//General
const String bleManufacturerTarget = "716";

//Internal - DO NOT CHANGE THESE!
String bleMAC = "";
bool bleScanMode = false;

}  //namespace prSettings
