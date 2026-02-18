#ifndef PR_UTIL_H
#define PR_UTIL_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <Preferences.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pr_settings.h"

namespace prUtil {

void SettingsInit(void);
void GPIOInit(void);
void OLEDInit(void);
void SPIFFSInit(void);
void HeartBeat(void);
void SaveSettings(void);
void ClearSettings(void);
void OLEDShowLogo(void);
void OLEDShowAPInfo(void);
void OLEDShowMessage(String L1, String L2, String L3, String L4, String L5, String L6);
void RequestRebootAndConnectToAP(uint32_t rebootDelay);
void RequestReboot(uint32_t rebootDelay);
void CheckReboot(void);
void RequestTriggerBLEScan(void);
void CheckTriggerBLEScan(void);
void LedControl(bool greenLed, bool yellowLed, bool redLed, bool extOut);
void SendClockData(String binaryData);
String CalculateBinary(String cardNo);
String ConvertToHex(unsigned long n);
String SplitString(String s, char separator, int index);
bool IsNumeric(String s);
bool IsIpAddress(String s);

}  //namespace prUtil

#endif
