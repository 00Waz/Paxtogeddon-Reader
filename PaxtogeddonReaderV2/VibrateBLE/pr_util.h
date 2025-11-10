#ifndef PR_UTIL_H
#define PR_UTIL_H

#include <Arduino.h>
#include <Preferences.h>
#include "pr_settings.h"

namespace prUtil {

void SettingsInit(void);
void GPIOInit(void);
void SaveSettings(void);
void ClearSettings(void);
void StatusLED(String state, uint32_t flashRate);

}  //namespace prUtil

#endif
