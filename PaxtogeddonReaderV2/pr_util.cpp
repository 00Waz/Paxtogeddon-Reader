#include "pr_util.h"

namespace prUtil {

uint32_t systemRebootDelay = 5000;
bool systemReboot = false;
Preferences preferences;
Adafruit_SSD1306 display(prSettings::SCREEN_WIDTH, prSettings::SCREEN_HEIGHT, &Wire, prSettings::OLED_RESET);

//Inits
void SettingsInit(void) {
  preferences.begin("prOneShot", false);
  if (preferences.getBool("CONNECT_AP", false)) {
    preferences.putBool("CONNECT_AP", false);
    prSettings::oneShotConnectToAP = true;
  }
  preferences.end();

  preferences.begin("prSettings", false);
  if (preferences.getBool("prs_ok", false)) {
    prSettings::apSSID = preferences.getString("AP_SSID", prSettings::apSSID);
    prSettings::apPassword = preferences.getString("AP_PW", prSettings::apPassword);
    String ipAddr = preferences.getString("AP_IP", prSettings::apIP.toString());
    prSettings::apIP.fromString(ipAddr);
    prSettings::wifiSSID = preferences.getString("WIFI_SSID", prSettings::wifiSSID);
    prSettings::wifiPassword = preferences.getString("WIFI_PW", prSettings::wifiPassword);
    prSettings::allowCaptivePortal = preferences.getBool("ALLOW_CP", prSettings::allowCaptivePortal);
    prSettings::webPollSeconds = preferences.getString("WEB_POLL", prSettings::webPollSeconds);
    prSettings::oledConnected = preferences.getBool("OLED_CON", prSettings::oledConnected);
  }
  preferences.end();
}

void GPIOInit(void) {
  pinMode(prSettings::CLOCK_PIN, INPUT);
  pinMode(prSettings::DATA_PIN, INPUT);
  pinMode(prSettings::NOT_USED_PIN_A, OUTPUT);
  pinMode(prSettings::NOT_USED_PIN_B, OUTPUT);
  pinMode(prSettings::GREEN_LED_PIN, OUTPUT);
  pinMode(prSettings::YELLOW_LED_PIN, OUTPUT);
  pinMode(prSettings::RED_LED_PIN, OUTPUT);
  pinMode(prSettings::HEARTBEAT_LED_PIN, OUTPUT);

  digitalWrite(prSettings::NOT_USED_PIN_A, 0);
  digitalWrite(prSettings::NOT_USED_PIN_B, 0);
  digitalWrite(prSettings::GREEN_LED_PIN, 0);
  digitalWrite(prSettings::YELLOW_LED_PIN, 0);
  digitalWrite(prSettings::RED_LED_PIN, 0);
  digitalWrite(prSettings::HEARTBEAT_LED_PIN, 1);

  if (prSettings::EXT_PIN < 255) {
    pinMode(prSettings::EXT_PIN, OUTPUT);
    digitalWrite(prSettings::EXT_PIN, 0);
  }

  delay(500);
  prUtil::LedControl(true, true, true, false);
}

void OLEDInit(void) {
  if (prSettings::OLED_SDA_PIN == 255) { prSettings::oledConnected = false; }
  if (prSettings::OLED_SCL_PIN == 255) { prSettings::oledConnected = false; }

  if (prSettings::oledConnected) {
    Wire.setPins(prSettings::OLED_SDA_PIN, prSettings::OLED_SCL_PIN);
    display.begin(SSD1306_SWITCHCAPVCC, prSettings::SCREEN_ADDRESS);
    OLEDShowLogo();
    delay(2000);
    OLEDShowMessage("Paxtogeddon Reader", "", ":Version:", prSettings::VERSION_NUMBER, ":Build Date:", prSettings::BUILD_DATE);
  }
}

void SPIFFSInit(void) {
  if (SPIFFS.begin(true)) {
    return;
  }

  if (SPIFFS.format()) {
    if (SPIFFS.begin(true)) {
      return;
    }
  }

  if (prSettings::oledConnected) {
    delay(2000);
    OLEDShowMessage("SPIFFS init failed", "", "", "", "", "");
  }

  while (true) {
    LedControl(false, false, true, false);
  }
}

//Utils
void HeartBeat(void) {
  digitalWrite(prSettings::HEARTBEAT_LED_PIN, 0);
  delay(100);
  digitalWrite(prSettings::HEARTBEAT_LED_PIN, 1);
  delay(100);
}

void SaveSettings(void) {
  preferences.begin("prSettings", false);
  preferences.putString("AP_SSID", prSettings::apSSID);
  preferences.putString("AP_PW", prSettings::apPassword);
  preferences.putString("AP_IP", prSettings::apIP.toString());
  preferences.putString("WIFI_SSID", prSettings::wifiSSID);
  preferences.putString("WIFI_PW", prSettings::wifiPassword);
  preferences.putBool("ALLOW_CP", prSettings::allowCaptivePortal);
  preferences.putString("WEB_POLL", prSettings::webPollSeconds);
  preferences.putBool("OLED_CON", prSettings::oledConnected);
  preferences.putBool("prs_ok", true);
  preferences.end();
}

void ClearSettings(void) {
  preferences.begin("prSettings", false);
  preferences.clear();
  preferences.end();
  preferences.begin("prOneShot", false);
  preferences.putBool("CONNECT_AP", false);
  preferences.end();
}

void OLEDShowLogo(void) {
  if (prSettings::oledConnected) {
    display.clearDisplay();
    display.drawBitmap(0, 0, prSettings::LOGO_OLED, prSettings::SCREEN_WIDTH, prSettings::SCREEN_HEIGHT, WHITE);
    display.display();
  }
}

void OLEDShowAPInfo(void) {
  if (prSettings::oledConnected) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    if (prSettings::oneShotConnectToAP) {
      display.setCursor(0, 0);
      display.println("Connected to WiFi");
      display.setCursor(0, 20);
      display.println(":SSID:");
      display.setCursor(0, 30);
      display.println(prSettings::wifiSSID);
      display.setCursor(0, 40);
      display.println(":IP:");
      display.setCursor(0, 50);
      display.println(prSettings::wifiIP);
    } else {
      display.setCursor(0, 0);
      display.println(":SSID:");
      display.setCursor(0, 10);
      display.println(prSettings::apSSID);
      display.setCursor(0, 20);
      display.println(":PASS:");
      display.setCursor(0, 30);
      display.println(prSettings::apPassword);
      display.setCursor(0, 40);
      display.println(":IP:");
      display.setCursor(0, 50);
      display.println(prSettings::apIP);
    }

    display.display();
  }
}

void OLEDShowMessage(String L1, String L2, String L3, String L4, String L5, String L6) {
  if (prSettings::oledConnected) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(L1);
    display.setCursor(0, 10);
    display.println(L2);
    display.setCursor(0, 20);
    display.println(L3);
    display.setCursor(0, 30);
    display.println(L4);
    display.setCursor(0, 40);
    display.println(L5);
    display.setCursor(0, 50);
    display.println(L6);
    display.display();
  }
}

void RequestRebootAndConnectToAP(uint32_t rebootDelay) {
  preferences.begin("prOneShot", false);
  preferences.putBool("CONNECT_AP", true);
  preferences.end();
  systemRebootDelay = rebootDelay;
  systemReboot = true;
}

void RequestReboot(uint32_t rebootDelay) {
  systemRebootDelay = rebootDelay;
  systemReboot = true;
}

void CheckReboot(void) {
  if (systemReboot) {
    systemReboot = false;
    digitalWrite(prSettings::HEARTBEAT_LED_PIN, 1);
    delay(systemRebootDelay);
    ESP.restart();
  }
}

void LedControl(bool greenLed, bool yellowLed, bool redLed, bool extOut) {
  //Controls the EXT PIN if extOut is true and the pin has been assigned
  if (extOut && prSettings::EXT_PIN < 255) {
    digitalWrite(prSettings::EXT_PIN, 1);
  }

  //Controls the Green, Yellow, and Red LED's on the P50/P200 reader
  //Using 2N3904 NPN transistors with BASE connected to GPIO via 1K resistor
  //P50/P200 LED wire connected to COLLECTOR
  //0v/GND connected to EMITTER
  for (int i = 0; i < 2; i++) {
    digitalWrite(prSettings::GREEN_LED_PIN, 0);
    digitalWrite(prSettings::YELLOW_LED_PIN, 0);
    digitalWrite(prSettings::RED_LED_PIN, 0);

    delay(100);

    if (greenLed) {
      digitalWrite(prSettings::GREEN_LED_PIN, 1);
    }

    if (yellowLed) {
      digitalWrite(prSettings::YELLOW_LED_PIN, 1);
    }

    if (redLed) {
      digitalWrite(prSettings::RED_LED_PIN, 1);
    }

    delay(100);
  }

  digitalWrite(prSettings::GREEN_LED_PIN, 1);
  digitalWrite(prSettings::YELLOW_LED_PIN, 1);
  digitalWrite(prSettings::RED_LED_PIN, 1);

  if (extOut && prSettings::EXT_PIN < 255) {
    digitalWrite(prSettings::EXT_PIN, 0);
  }
}

void SendClockData(String binaryData) {
  pinMode(prSettings::CLOCK_PIN, OUTPUT);
  pinMode(prSettings::DATA_PIN, OUTPUT);
  delay(500);

  for (int i = 0; i < binaryData.length(); i++) {
    int b = binaryData[i] == '0' ? 1 : 0;
    digitalWrite(prSettings::DATA_PIN, b);
    digitalWrite(prSettings::CLOCK_PIN, 0);
    delay(2);
    digitalWrite(prSettings::CLOCK_PIN, 1);
  }

  digitalWrite(prSettings::DATA_PIN, 1);

  pinMode(prSettings::CLOCK_PIN, INPUT);
  pinMode(prSettings::DATA_PIN, INPUT);
}

String CalculateBinary(String cardNo) {
  String token = "";

  if (cardNo.length() < 8) {
    int padLen = 8 - cardNo.length();
    for (int i = 0; i < padLen; i++) {
      token += "0";
    }
  }

  token += cardNo;
  int LRC[4] = { 2, 2, 1, 2 };
  String binaryOut = "000000000011010";

  for (int i = 0; i < 8; i++) {
    int d = token[i];
    int b0 = d >> 0 & 1;
    int b1 = d >> 1 & 1;
    int b2 = d >> 2 & 1;
    int b3 = d >> 3 & 1;
    int b4 = (b0 + b1 + b2 + b3) % 2 == 0 ? 1 : 0;
    binaryOut += b0;
    binaryOut += b1;
    binaryOut += b2;
    binaryOut += b3;
    binaryOut += b4;
    LRC[0] += b0;
    LRC[1] += b1;
    LRC[2] += b2;
    LRC[3] += b3;
  }

  binaryOut += "11111";
  int c0 = LRC[0] % 2 == 0 ? 0 : 1;
  int c1 = LRC[1] % 2 == 0 ? 0 : 1;
  int c2 = LRC[2] % 2 == 0 ? 0 : 1;
  int c3 = LRC[3] % 2 == 0 ? 0 : 1;
  int c4 = (c0 + c1 + c2 + c3) % 2 == 0 ? 1 : 0;
  binaryOut += c0;
  binaryOut += c1;
  binaryOut += c2;
  binaryOut += c3;
  binaryOut += c4;
  binaryOut += "0000000000";
  return binaryOut;
}

String SplitString(String s, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = s.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (s.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? s.substring(strIndex[0], strIndex[1]) : "";
}

bool IsNumeric(String s) {
  if (s.length() == 0) { return false; }
  for (int i = 0; i < s.length(); i++) {
    if (!isDigit(s.charAt(i))) {
      return false;
    }
  }
  return true;
}

bool IsIpAddress(String s) {
  if (s.length() == 0) { return false; }
  if (s.charAt(s.length() - 1) == '.') { return false; }
  String octet1 = SplitString(s, '.', 0);
  if (!IsNumeric(octet1)) { return false; }
  int o1 = octet1.toInt();
  if (o1 < 1 || o1 > 254) { return false; }
  String octet2 = SplitString(s, '.', 1);
  if (!IsNumeric(octet2)) { return false; }
  int o2 = octet2.toInt();
  if (o2 > 255) { return false; }
  String octet3 = SplitString(s, '.', 2);
  if (!IsNumeric(octet3)) { return false; }
  int o3 = octet3.toInt();
  if (o3 > 255) { return false; }
  String octet4 = SplitString(s, '.', 3);
  if (!IsNumeric(octet4)) { return false; }
  int o4 = octet4.toInt();
  if (o4 < 1 || o4 > 254) { return false; }
  String trailing = SplitString(s, '.', 4);
  if (trailing != "") { return false; }
  return true;
}

}  //namespace prUtil
