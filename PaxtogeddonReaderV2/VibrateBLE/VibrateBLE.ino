/*
__________                  __                           .___  .___             
\______   \_____  ___  ____/  |_  ____   ____   ____   __| _/__| _/____   ____  
 |     ___/\__  \ \  \/  /\   __\/  _ \ / ___\_/ __ \ / __ |/ __ |/  _ \ /    \ 
 |    |     / __ \_>    <  |  | (  <_> ) /_/  >  ___// /_/ / /_/ (  <_> )   |  \
 |____|    (____  /__/\_ \ |__|  \____/\___  / \___  >____ \____ |\____/|___|  /
                \/      \/            /_____/      \/     \/    \/           \/ 

Product Name:  Vibrate BLE for Paxtogeddon Reader
Version:       1.0
Build Date:    2025-11-02
Author:        Daniel Raines [ Dr0pR00t ]

Credit: Cardinal_Black (Original BLE lib/commands for FitPro M4/M5/M6)

Shopping links...
https://www.aliexpress.com/item/1005008971783153.html
https://www.aliexpress.com/item/1005009086572716.html

This code was tested using a FireBeetle 2 ESP32-E
Trigger pin and status LED pin can be adjusted in pr_settings.cpp
*/

#include <Arduino.h>
#include "pr_settings.h"
#include "pr_util.h"
#include "pr_ble.h"

void setup() {
  prUtil::SettingsInit();
  prUtil::GPIOInit();
  prBLE::FitProM4Init();
}

void loop() {
  if (prSettings::bleScanMode) {
    prBLE::ScanDevices();
  } else {
    prBLE::MaintainConnection();
  }
  prBLE::InputTriggerHandler();
}
