/*
__________                  __                           .___  .___             
\______   \_____  ___  ____/  |_  ____   ____   ____   __| _/__| _/____   ____  
 |     ___/\__  \ \  \/  /\   __\/  _ \ / ___\_/ __ \ / __ |/ __ |/  _ \ /    \ 
 |    |     / __ \_>    <  |  | (  <_> ) /_/  >  ___// /_/ / /_/ (  <_> )   |  \
 |____|    (____  /__/\_ \ |__|  \____/\___  / \___  >____ \____ |\____/|___|  /
                \/      \/            /_____/      \/     \/    \/           \/ 

Product Name:  Paxtogeddon Reader
Version:       2.1
Build Date:    2025-11-02
Author:        Daniel Raines [ Dr0pR00t ]

Credit [ALL]: Moral support + just being an awesome dudes!
Credit [ALL]: The legends who know who they are, that are not listed below, at their request.

Credit: 00Waz (Original decode + code for SPIFFS + case) [ https://github.com/00Waz/Paxtogeddon-Reader ]
Credit: En4rab (Original port of doorsim into MicroPython + parity/LRC insights + captive portal + OLED) [ https://github.com/en4rab/Paxtogeddon-OLED-PCB ]
Credit: Cardinal_Black (Original BLE lib/commands for FitPro M4/M5/M6) > VibrateBLE.ino
Credit: Craigsblackie (ASCII art) [ https://github.com/craigsblackie ]

FireBeetle 2 ESP32-E -> Server Tasks > Core 0 | Ardunio/Events > Core 1
ESP32 C3 Super Mini -> Only has a single core

Net2 fobs > 10 bit leadin > b > 8 digit no. > f > lrc > 10 bit leadout (75 bits)
Switch2 fobs > 10 bit leadin > b > 8 digit no. > d > 15 digits > d > 12 zeros > f > lrc > 10 bit leadout (220 bits)
*/

#include <Arduino.h>
#include "pr_settings.h"
#include "pr_util.h"
#include "pr_server.h"
#include "pr_html.h"
#include "pr_cardreader.h"

void setup() {
  prUtil::SettingsInit();
  prUtil::GPIOInit();
  prUtil::OLEDInit();
  prUtil::SPIFFSInit();
  prCardReader::CardReaderInit();
  prServer::ServerInit();
}

void loop() {
  prUtil::HeartBeat();
  prUtil::CheckReboot();
  prUtil::CheckTriggerBLEScan();
  prCardReader::ParseCard();
}
