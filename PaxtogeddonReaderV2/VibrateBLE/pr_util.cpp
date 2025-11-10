#include "pr_util.h"

namespace prUtil {

uint32_t systemRebootDelay = 5000;
bool systemReboot = false;
Preferences preferences;

void SettingsInit(void) {
  preferences.begin("prSettings", false);
  if (preferences.getBool("prs_ok", false)) {
    prSettings::bleMAC = preferences.getString("BLE_MAC", "");
  }
  preferences.end();

  if (prSettings::bleMAC == "") {
    prSettings::bleScanMode = true;
  }
}

void GPIOInit(void) {
  pinMode(prSettings::TRIGGER_PIN, INPUT_PULLUP);
  pinMode(prSettings::STATUS_LED_PIN, OUTPUT);
  digitalWrite(prSettings::STATUS_LED_PIN, prSettings::STATUS_LED_PIN_INVERTED ? 1 : 0);
  while (digitalRead(prSettings::TRIGGER_PIN) == 0) {
    StatusLED("flash", 50);
  }
}

void SaveSettings() {
  preferences.begin("prSettings", false);
  preferences.putString("BLE_MAC", prSettings::bleMAC);
  preferences.putBool("prs_ok", true);
  preferences.end();
}

void ClearSettings(void) {
  preferences.begin("prSettings", false);
  preferences.clear();
  preferences.end();
}

void StatusLED(String state, uint32_t flashRate) {
  if (state == "flash" && flashRate < 50) {
    flashRate = 50;
  }

  if (state == "on" || state == "flash") {
    digitalWrite(prSettings::STATUS_LED_PIN, prSettings::STATUS_LED_PIN_INVERTED ? 0 : 1);
    if (flashRate > 0) { delay(flashRate); }
  }

  if (state == "off" || state == "flash") {
    digitalWrite(prSettings::STATUS_LED_PIN, prSettings::STATUS_LED_PIN_INVERTED ? 1 : 0);
    if (flashRate > 0) { delay(flashRate); }
  }
}

}  //namespace prUtil
