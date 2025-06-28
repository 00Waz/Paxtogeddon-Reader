#ifndef PR_SETTINGS_H
#define PR_SETTINGS_H

#include <Arduino.h>

namespace prSettings {

//Product
const extern String VERSION_NUMBER;
const extern String BUILD_DATE;

//OLED
const extern byte SCREEN_WIDTH;
const extern byte SCREEN_HEIGHT;
const extern byte OLED_RESET;
const extern byte SCREEN_ADDRESS;

//Test Card
const extern String TEST_CARD;

//Function Cards
const extern String FC_DEFAULT;
const extern String FC_CONNECT_TO_AP;
const extern String FC_SHOW_AP_INFO;

//PIN Assignments
const extern byte HEARTBEAT_LED_PIN;
const extern byte CLOCK_PIN;
const extern byte DATA_PIN;
const extern byte NOT_USED_PIN_A;
const extern byte NOT_USED_PIN_B;
const extern byte GREEN_LED_PIN;
const extern byte YELLOW_LED_PIN;
const extern byte RED_LED_PIN;
const extern byte EXT_PIN;
const extern byte OLED_SDA_PIN;
const extern byte OLED_SCL_PIN;

//User Config Defaults
extern String apSSID;
extern String apPassword;
extern IPAddress apIP;
extern String wifiSSID;
extern String wifiPassword;
extern IPAddress wifiIP;
extern bool allowCaptivePortal;
extern String webPollSeconds;
extern bool oledConnected;

//General
extern bool oneShotConnectToAP;
extern String lastCardData;
extern String replayBin;

//Paxtogeddon Logo
const extern unsigned char LOGO_OLED[];
const extern String LOGO_HTML;

} //namespace prSettings

#endif
