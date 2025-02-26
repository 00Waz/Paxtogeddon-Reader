/*-------------------------------------------------------------------------------------------------------------------
__________                  __                           .___  .___             
\______   \_____  ___  ____/  |_  ____   ____   ____   __| _/__| _/____   ____  
 |     ___/\__  \ \  \/  /\   __\/  _ \ / ___\_/ __ \ / __ |/ __ |/  _ \ /    \ 
 |    |     / __ \_>    <  |  | (  <_> ) /_/  >  ___// /_/ / /_/ (  <_> )   |  \
 |____|    (____  /__/\_ \ |__|  \____/\___  / \___  >____ \____ |\____/|___|  /
                \/      \/            /_____/      \/     \/    \/           \/ 

Paxtogeddon Reader v1.2.1
Author: Daniel "DropR00t" Raines

Credit: 00Waz (Original decode + code for SPIFFS + just being an awesome dude)
Credit: En4rab (Original port of doorism into MicroPython + parity/LRC insights + just being an awesome dude)
Credit: Craigsblackie (ASCII art + moral support + just being an awesome dude)

Credit: The legends who know who they are (Moral support + just being an awesome dudes)

Net2 fobs > 10 bit leadin > b > 8 digit no. > f > lrc > 10 bit leadout (75 bits)
Switch2 fobs > 10 bit leadin > b > 8 digit no. > d > 15 digits > d > 12 zeros > f > lrc > 10 bit leadout (220 bits)

My setup (Arduino IDE), as follows...
Web Server Task > Pinned to Core 0
By default "Ardunio" and "Events" are running on Core 1
-------------------------------------------------------------------------------------------------------------------*/


//----- Includes ----------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include <SPIFFS.h>

//----- Constants ---------------------------------------------------------------------------------------------------
const bool DEBUG_MODE = true;  //Will output data to the serial console if true

const long DEBOUNCE_TIME = 350;                 //Interrupt debounce time (sweet spot 300 to 400)
const unsigned long SERIAL_BAUD_RATE = 115200;  //Serial console baud rate
const int HTML_AUTO_REFRESH_SECONDS = 5;        //Adjust as required

const byte HEARTBEAT_LED_PIN = 2;  //Adjust as required (built-in LED to show main loop "extremely fast" heartbeat!)
const byte CLOCK_PIN = 18;         //Adjust as required
const byte DATA_PIN = 19;          //Adjust as required
const byte REPLAY_CLOCK_PIN = 4;   //Adjust as required
const byte REPLAY_DATA_PIN = 12;   //Adjust as required
const byte WIFI_MODE_PIN = 27;     //Adjust as required (built-in button on the FireBeetle)
const byte GREEN_LED_PIN = 25;     //Adjust as required
const byte RED_LED_PIN = 26;       //Adjust as required
const byte YELLOW_LED_PIN = 13;    //Adjust as required

const char* AP_SSID = "Paxtogeddon";          //Adjust as required
const char* AP_PASSWORD = "13371337";         //Adjust as required
const IPAddress AP_IP(192, 168, 2, 10);       //Adjust as required
const IPAddress AP_SUBNET(255, 255, 255, 0);  //Adjust as required
const char* HOSTNAME = "PaxtogeddonESP32";    //Adjust as required

const char* WIFI_SSID = "YOUR_WIFI_SSID";                      //Your Wifi access point SSID name
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";  //You Wifi access point password

//----- Volatiles (Interrupt) ---------------------------------------------------------------------------------------
volatile unsigned long lastMicros = 0;  //Last recorded micros, works in accordance with debounce time
volatile int bitCount = 0;              //Total recevied bits
volatile bool processingData = false;   //Ensures bit count and card data are not accessed whilst parsing data
volatile bool interruptFired = false;   //This is purely for debug purposes
volatile int cardData[256];             //Card data array for clocked-in bits

//----- General Config ----------------------------------------------------------------------------------------------
int net2Bits = 75;                 //Net2 expected bit count
int switch2Bits = 220;             //Switch2 expected bit count
bool autoRefreshCardData = false;  //HTML auto refresh - this is the default and can be toggled via the web page
bool connectedViaWifi = false;     //Toggles depending on AP or WiFi
bool systemReboot = false;         //Set to true via web server call, at which point the main loop reboots the ESP32
String lastCardData = "Ready.";    //Last card processed or error message
AsyncWebServer webServer(80);      //Default port for Web Server

//----- Configure WiFi ----------------------------------------------------------------------------------------------
void ConfigureWiFi() {
  if (digitalRead(WIFI_MODE_PIN) == 0) {
    if (DEBUG_MODE) {
      Serial.println("Connecting to WiFi...");
    }

    WiFi.mode(WIFI_STA);
    WiFi.softAP(HOSTNAME, "");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
      LedControl(false, true, false, 100);
    }

    connectedViaWifi = true;

    if (DEBUG_MODE) {
      Serial.print("Connected to: ");
      Serial.println(WIFI_SSID);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    }
  } else {
    if (DEBUG_MODE) {
      Serial.println("Starting access point...");
    }

    WiFi.mode(WIFI_AP);
    WiFi.softAP(HOSTNAME, "");
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    WiFi.softAPConfig(AP_IP, AP_IP, AP_SUBNET);
    delay(500);
    connectedViaWifi = false;

    if (DEBUG_MODE) {
      Serial.print("AP Name: ");
      Serial.println(AP_SSID);
      Serial.print("IP address: ");
      Serial.println(AP_IP);
    }
  }
}

//----- Load Card Data ----------------------------------------------------------------------------------------------
void LoadCardData() {
  File logFile = SPIFFS.open("/card_data.txt", "r");
  int totalCards = 0;

  if (logFile) {
    while (logFile.available()) {
      String line = logFile.readStringUntil('\n');
      line.trim();

      if (line.length() > 0) {
        totalCards++;

        if (DEBUG_MODE) {
          Serial.println(line);
        }
      }
    }

    logFile.close();
  }

  if (DEBUG_MODE) {
    Serial.print("Total cards in log: ");
    Serial.println(totalCards);
  }
}

//----- Save Card Data ----------------------------------------------------------------------------------------------
bool SaveCardData(String cardNumber, String bitCount, String binary, String cardType, String colour) {
  File logFile = SPIFFS.open("/card_data.txt", "a");

  if (logFile) {
    logFile.print(cardNumber);
    logFile.print(",");
    logFile.print(bitCount);
    logFile.print(",");
    logFile.print(binary);
    logFile.print(",");
    logFile.print(cardType);
    logFile.print(",");
    logFile.println(colour);
    logFile.close();
    return true;
  }

  if (DEBUG_MODE) {
    Serial.println("Failed to open log file");
  }

  return false;
}

//----- Delete Card Data --------------------------------------------------------------------------------------------
void DeleteCardData() {
  SPIFFS.remove("/card_data.txt");
}

//----- LED Control -------------------------------------------------------------------------------------------------
void LedControl(bool greenLed, bool yellowLed, bool redLed, int interval) {
  //Controls the Green, Yellow, and Red LED's on the P50 reader
  //Using 2N3904 NPN transistors with BASE connected to GPIO via 1K resistor
  //P50 LED wire connected to COLLECTOR
  //0v/GND connected to EMITTER
  for (int i = 0; i < 2; i++) {
    digitalWrite(GREEN_LED_PIN, 0);
    digitalWrite(YELLOW_LED_PIN, 0);
    digitalWrite(RED_LED_PIN, 0);

    delay(interval);

    if (greenLed) {
      digitalWrite(GREEN_LED_PIN, 1);
    }

    if (yellowLed) {
      digitalWrite(YELLOW_LED_PIN, 1);
    }

    if (redLed) {
      digitalWrite(RED_LED_PIN, 1);
    }

    delay(interval);
  }

  digitalWrite(GREEN_LED_PIN, 1);
  digitalWrite(YELLOW_LED_PIN, 1);
  digitalWrite(RED_LED_PIN, 1);
}

//----- Split String ------------------------------------------------------------------------------------------------
String SplitString(String s, char separator, int index) {
  //Split a string by separator char and return a string for a given index
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

//----- Get Base URL ------------------------------------------------------------------------------------------------
String GetBaseURL() {
  //Get IP Address and build "URL"

  if (connectedViaWifi) {
    return "http://" + WiFi.localIP().toString();
  }

  return "http://" + AP_IP.toString();
}

//-----Get Redirect HTML --------------------------------------------------------------------------------------------
String GetRedirectHTML() {
  String html = "<!doctype html><html><head>";
  html += "<meta charset=\"utf-8\">";
  html += "<title>Paxtogeddon Reader</title><meta charset=\"utf-8\">";
  html += "<meta http-equiv=\"refresh\" content=\"0; url=" + GetBaseURL() + "/\">";
  html += "</head><body></body></html>";
  return html;
}

//----- Check Bit Count ---------------------------------------------------------------------------------------------
bool CheckBitCount() {
  if (bitCount > 0) {
    int brk = 0;

    //Check if we have the Net2 bit count with break after 1 second if we don't
    while (bitCount < net2Bits) {
      delay(10);
      brk++;

      if (brk >= 100) {
        break;
      }
    }

    brk = 0;
    //delay(50);

    //We have more bits than Net2, so assume it's a Switch2 card
    //Check if we have the Switch2 bit count with break after 1 second if we don't
    if (bitCount > net2Bits) {
      while (bitCount < switch2Bits) {
        delay(10);
        brk++;

        if (brk >= 100) {
          break;
        }
      }
    }

    if (DEBUG_MODE) {
      Serial.print("Bit count: ");
      Serial.println(bitCount);
    }

    //If the bit count doesn't match Net2 or Switch2 then something went wrong!
    if (bitCount != net2Bits && bitCount != switch2Bits) {
      if (DEBUG_MODE) {
        Serial.println("Bit count error");
      }

      lastCardData = "Bit count error, received: " + String(bitCount);
      LedControl(false, false, true, 100);
    } else {
      return true;
    }
  }

  bitCount = 0;
  return false;
}

//----- Check Leadin ------------------------------------------------------------------------------------------------
bool CheckLeadin() {
  //Check first 10 bits are all zero
  for (int i = 0; i < 10; i++) {
    if (cardData[i] != 0) {
      if (DEBUG_MODE) {
        Serial.println("Leadin error");
      }

      lastCardData = "Leadin error";
      LedControl(false, false, true, 100);
      bitCount = 0;
      return false;
    }
  }

  return true;
}

//----- Check Leadout -----------------------------------------------------------------------------------------------
bool CheckLeadout() {
  //Check last 10 bits are all zero
  for (int i = bitCount - 10; i < bitCount; i++) {
    if (cardData[i] != 0) {
      if (DEBUG_MODE) {
        Serial.println("Leadout error");
      }

      lastCardData = "Leadout error";
      LedControl(false, false, true, 100);
      bitCount = 0;
      return false;
    }
  }

  return true;
}

//----- Parse Net2 ---------------------------------------------------------------------------------------------------
void ParseNet2() {
  String cardNumber = "";
  String binary = "";
  bool cardReadSuccess = false;
  int LRC[4] = { 0, 0, 0, 0 };

  //Iterates over all bits to store binary data as a string
  for (int i = 0; i < bitCount; i++) {
    binary += cardData[i];
  }

  //Iterates over all bits (excluding leadin / leadout)
  for (int i = 10; i < bitCount - 10; i += 5) {

    //Calculate each digit of the card number from the digit bits
    int dval = (0
                + 8 * cardData[i + 3]
                + 4 * cardData[i + 2]
                + 2 * cardData[i + 1]
                + 1 * cardData[i + 0]);

    //Check each rows parity (odd)
    int b0 = cardData[i + 0];
    int b1 = cardData[i + 1];
    int b2 = cardData[i + 2];
    int b3 = cardData[i + 3];
    int b4 = cardData[i + 4];
    int rowParity = (b0 + b1 + b2 + b3) % 2 == 0 ? 1 : 0;

    if (rowParity != b4) {
      lastCardData = "Row odd parity LRC error<br>";
      lastCardData += binary;

      if (DEBUG_MODE) {
        Serial.print("Row odd parity LRC error at index ");
        Serial.print(i);
        Serial.print(" - ");
        Serial.println(i + 5);
        Serial.println(binary);
        for (int p = 0; p < bitCount; p++) {
          if (p >= i && p < i + 5) {
            Serial.print("^");
          } else {
            Serial.print(" ");
          }
        }
        Serial.println("");
      }

      LedControl(false, false, true, 100);
      return;
    }

    //Index 10 from for loop iterator +=5
    //Checks the card start bits are equal to 11 (B in HEX)
    if (i == 10) {
      if (dval != 11) {
        if (DEBUG_MODE) {
          Serial.print("Start bits error - expected 11 but received ");
          Serial.println(dval);
        }

        lastCardData = "Start bits error - expected 11 but received " + String(dval);
        LedControl(false, false, true, 100);
        return;
      }
    }

    //Index 55 from for loop iterator +=5
    //Checks the card stop bits are equal to 15 (F in HEX)
    if (i == 55) {
      if (dval != 15) {
        if (DEBUG_MODE) {
          Serial.print("Stop bits error - expected 15 but received ");
          Serial.println(dval);
        }

        lastCardData = "Stop bits error - expected 15 but received " + String(dval);
        LedControl(false, false, true, 100);
        return;
      }
    }

    //Add the column bits to the LRC array
    //Skip if we are reading the actual LRC bits
    if (i < 60) {
      LRC[0] += b0;
      LRC[1] += b1;
      LRC[2] += b2;
      LRC[3] += b3;
    }

    //Index 60 from for loop iterator +=5 (LRC bits)
    //Check column parity (even) matches actual partiy bits
    if (i == 60) {
      int c0 = LRC[0] % 2 == 0 ? 0 : 1;
      int c1 = LRC[1] % 2 == 0 ? 0 : 1;
      int c2 = LRC[2] % 2 == 0 ? 0 : 1;
      int c3 = LRC[3] % 2 == 0 ? 0 : 1;

      if (c0 == b0 && c1 == b1
          && c2 == b2 && c3 == b3) {
        cardReadSuccess = true;
      } else {
        lastCardData = "Column even parity LRC error<br>";
        lastCardData += binary;

        if (DEBUG_MODE) {
          Serial.print("Column even parity LRC error at index ");
          Serial.print(i);
          Serial.print(" - ");
          Serial.println(i + 5);
          Serial.println(binary);
          for (int p = 0; p < bitCount; p++) {
            if (p >= i && p < i + 5) {
              Serial.print("^");
            } else {
              Serial.print(" ");
            }
          }

          Serial.println("");
          Serial.print("Calculated LRC: ");
          Serial.print(c0);
          Serial.print(c1);
          Serial.print(c2);
          Serial.print(c3);
          Serial.println(b4);
          Serial.print("Actual LRC: ");
          Serial.print(b0);
          Serial.print(b1);
          Serial.print(b2);
          Serial.print(b3);
          Serial.println(b4);
        }

        LedControl(false, false, true, 100);
        return;
      }
    }

    if (i > 10 && i < 55) {
      cardNumber += dval;
    }
  }

  if (!cardReadSuccess) {
    return;
  }

  if (DEBUG_MODE) {
    Serial.print("Binary: ");
    Serial.println(binary);
    Serial.print("Card number: ");
    Serial.println(cardNumber);
    Serial.println("Card type: Net2");
    Serial.println("Card colour: None");
  }

  lastCardData = "Card number: " + cardNumber + "<br>";
  lastCardData += "Card type: Net2<br>";
  lastCardData += "Card colour: None<br>";
  lastCardData += "Bit count: " + String(bitCount) + "<br>";
  lastCardData += "Binary: " + binary + "<br>";

  if (!SaveCardData(cardNumber, String(bitCount), binary, "Net2", "None")) {
    if (DEBUG_MODE) {
      Serial.println("Card save error");
    }

    lastCardData = "Card save error";
    LedControl(false, true, false, 100);
    return;
  }

  LedControl(true, false, false, 100);
}

//----- Parse Switch2 ---------------------------------------------------------------------------------------------------
void ParseSwitch2() {
  String cardNumber = "";
  String s2fcn1 = "";
  String s2fcn2 = "";
  String binary = "";
  String cardType = "Switch2 Knockout";
  String colour = "Unknown";
  bool cardReadSuccess = false;
  int LRC[4] = { 0, 0, 0, 0 };

  //Iterates over all bits to store binary data as a string
  for (int i = 0; i < bitCount; i++) {
    binary += cardData[i];
  }

  //Iterates over all bits (excluding leadin / leadout)
  for (int i = 10; i < bitCount - 10; i += 5) {

    //Calculate each digit of the card number from the digit bits
    int dval = (0
                + 8 * cardData[i + 3]
                + 4 * cardData[i + 2]
                + 2 * cardData[i + 1]
                + 1 * cardData[i + 0]);

    //Check each rows parity (odd)
    int b0 = cardData[i + 0];
    int b1 = cardData[i + 1];
    int b2 = cardData[i + 2];
    int b3 = cardData[i + 3];
    int b4 = cardData[i + 4];
    int rowParity = (b0 + b1 + b2 + b3) % 2 == 0 ? 1 : 0;

    if (rowParity != b4) {
      lastCardData = "Row odd parity LRC error<br>";
      lastCardData += binary;

      if (DEBUG_MODE) {
        Serial.print("Row odd parity LRC error at index ");
        Serial.print(i);
        Serial.print(" - ");
        Serial.println(i + 5);
        Serial.println(binary);
        for (int p = 0; p < bitCount; p++) {
          if (p >= i && p < i + 5) {
            Serial.print("^");
          } else {
            Serial.print(" ");
          }
        }
        Serial.println("");
      }

      LedControl(false, false, true, 100);
      return;
    }

    //Index 10 from for loop iterator +=5
    //Checks the card start bits are equal to 11 (B in HEX)
    if (i == 10) {
      if (dval != 11) {
        if (DEBUG_MODE) {
          Serial.print("Start bits error - expected 11 but received ");
          Serial.println(dval);
        }

        lastCardData = "Start bits error - expected 11 but received " + String(dval);
        LedControl(false, false, true, 100);
        return;
      }
    }

    //Index 55 from for loop iterator +=5
    //Checks the card digit bits are equal to 13 (D in HEX)
    if (i == 55) {
      if (dval != 13) {
        if (DEBUG_MODE) {
          Serial.print("Digit bits error - expected 13 but received ");
          Serial.println(dval);
        }

        lastCardData = "Digit bits error - expected 13 but received " + String(dval);
        LedControl(false, false, true, 100);
        return;
      }
    }

    //Index 125 from for loop iterator +=5
    //Gets the card type
    if (i == 125) {
      if (dval == 1) {
        cardType = "Switch2 Fob";
      }
    }

    //Index 130 from for loop iterator +=5
    //Gets the card colour
    if (i == 130) {
      if (dval == 1) {
        colour = "Green";
      } else if (dval == 2) {
        colour = "Yellow";
      } else if (dval == 4) {
        colour = "Red";
      }
    }

    //Index 135 from for loop iterator +=5
    //Checks the card digit bits are equal to 13 (D in HEX)
    if (i == 135) {
      if (dval != 13) {
        if (DEBUG_MODE) {
          Serial.print("Digit bits error - expected 13 but received ");
          Serial.println(dval);
        }

        lastCardData = "Digit bits error - expected 13 but received " + String(dval);
        LedControl(false, false, true, 100);
        return;
      }
    }

    //Index 200 from for loop iterator +=5
    //Checks the card stop bits are equal to 15 (F in HEX)
    if (i == 200) {
      if (dval != 15) {
        if (DEBUG_MODE) {
          Serial.print("Stop bits error - expected 15 but received ");
          Serial.println(dval);
        }

        lastCardData = "Stop bits error - expected 15 but received " + String(dval);
        LedControl(false, false, true, 100);
        return;
      }
    }

    //Add the column bits to the LRC array
    //Skip if we are reading the actual LRC bits
    if (i < 205) {
      LRC[0] += b0;
      LRC[1] += b1;
      LRC[2] += b2;
      LRC[3] += b3;
    }

    //Index 200 from for loop iterator +=5 (LRC bits)
    //Check column parity (even) matches actual partiy bits
    if (i == 205) {
      int c0 = LRC[0] % 2 == 0 ? 0 : 1;
      int c1 = LRC[1] % 2 == 0 ? 0 : 1;
      int c2 = LRC[2] % 2 == 0 ? 0 : 1;
      int c3 = LRC[3] % 2 == 0 ? 0 : 1;

      if (c0 == b0 && c1 == b1
          && c2 == b2 && c3 == b3) {
        cardReadSuccess = true;
      } else {
        lastCardData = "Column even parity LRC error<br>";
        lastCardData += binary;

        if (DEBUG_MODE) {
          Serial.print("Column even parity LRC error at index ");
          Serial.print(i);
          Serial.print(" - ");
          Serial.println(i + 5);
          Serial.println(binary);
          for (int p = 0; p < bitCount; p++) {
            if (p >= i && p < i + 5) {
              Serial.print("^");
            } else {
              Serial.print(" ");
            }
          }

          Serial.println("");
          Serial.print("Calculated LRC: ");
          Serial.print(c0);
          Serial.print(c1);
          Serial.print(c2);
          Serial.print(c3);
          Serial.println(b4);
          Serial.print("Actual LRC: ");
          Serial.print(b0);
          Serial.print(b1);
          Serial.print(b2);
          Serial.print(b3);
          Serial.println(b4);
        }

        LedControl(false, false, true, 100);
        return;
      }
    }

    //Get part 1 of the Switch2 Fob number
    if (i == 60 || i == 70 || i == 80 || i == 90) {
      s2fcn1 += dval;
    }

    //Get part 2 of the Switch2 Fob number
    if (i == 20 || i == 30 || i == 40 || i == 50) {
      s2fcn2 += dval;
    }

    if (i > 10 && i < 55) {
      cardNumber += dval;
    }
  }

  if (!cardReadSuccess) {
    return;
  }

  if (cardType == "Switch2 Fob") {
    cardNumber = s2fcn1 + s2fcn2;
  }

  if (DEBUG_MODE) {
    Serial.print("Binary: ");
    Serial.println(binary);
    Serial.print("Card number: ");
    Serial.println(cardNumber);
    Serial.print("Card type: ");
    Serial.println(cardType);
    Serial.print("Card colour: ");
    Serial.println(colour);
  }

  lastCardData = "Card number: " + cardNumber + "<br>";
  lastCardData += "Card type: " + cardType + "<br>";
  lastCardData += "Card colour: " + colour + "<br>";
  lastCardData += "Bit count: " + String(bitCount) + "<br>";
  lastCardData += "Binary: " + binary + "<br>";

  if (!SaveCardData(cardNumber, String(bitCount), binary, cardType, colour)) {
    if (DEBUG_MODE) {
      Serial.println("Card save error");
    }

    lastCardData = "Card save error";
    LedControl(false, true, false, 100);
    return;
  }

  LedControl(true, false, false, 100);
}

//----- Card Replay -------------------------------------------------------------------------------------------------
void CardReplayGPIO(int noOfBits, String binaryData, String cardNo) {
  //Iterates over all bits of binaryData and clocks these out via GPIO
  for (int i = 0; i < noOfBits; i++) {
    int b = binaryData[i] == '0' ? 1 : 0;
    digitalWrite(REPLAY_DATA_PIN, b);
    digitalWrite(REPLAY_CLOCK_PIN, 0);
    delay(2);
    digitalWrite(REPLAY_CLOCK_PIN, 1);
  }

  digitalWrite(REPLAY_DATA_PIN, 1);

  lastCardData = "Card Replay<br>";
  lastCardData += "Card number: " + cardNo + "<br>";
  lastCardData += "Bit count: " + String(noOfBits) + "<br>";
  lastCardData += "Binary: " + binaryData + "<br>";

  if (DEBUG_MODE) {
    Serial.println("Card Replay");
    Serial.print("Card number: ");
    Serial.println(cardNo);
    Serial.print("Bit count: ");
    Serial.println(noOfBits);
    Serial.print("Binary: ");
    Serial.println(binaryData);
  }
}

//----- Web Server Task ---------------------------------------------------------------------------------------------
void WebServerTask(void* parameter) {
  //Web Server Task is pinned to Core 0

  //Toggle auto refresh on/off
  webServer.on("/toggleRefresh", HTTP_GET, [](AsyncWebServerRequest* request) {
    autoRefreshCardData = !autoRefreshCardData;

    if (DEBUG_MODE) {
      Serial.print("Auto refresh: ");
      Serial.println(autoRefreshCardData);
    }

    request->send(200, "text/html", GetRedirectHTML());
  });

  //Downloads log if available
  webServer.on("/downloadLog", HTTP_GET, [](AsyncWebServerRequest* request) {
    bool logAvailable = false;
    File logFile = SPIFFS.open("/card_data.txt", "r");
    if (logFile) {
      if (logFile.available()) {
        logAvailable = true;
        if (DEBUG_MODE) {
          Serial.println("Log downloaded");
        }
      }

      logFile.close();
    }

    if (logAvailable) {
      request->send(SPIFFS, "/card_data.txt", String(), true);
      return;
    }

    if (DEBUG_MODE) {
      Serial.println("Logfile not available");
    }

    lastCardData = "Logfile not available";
    request->send(200, "text/html", GetRedirectHTML());
  });

  //Clears log
  webServer.on("/clearLog", HTTP_GET, [](AsyncWebServerRequest* request) {
    DeleteCardData();

    if (DEBUG_MODE) {
      Serial.println("Logfile cleared");
    }

    lastCardData = "Logfile cleared";
    request->send(200, "text/html", GetRedirectHTML());
  });

  //Reboot ESP32
  webServer.on("/rebootESP32", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (DEBUG_MODE) {
      Serial.println("Reboot command received");
    }

    lastCardData = "Reboot command sent";
    systemReboot = true;

    request->send(200, "text/html", GetRedirectHTML());
  });

  //Replays binary data via *replay* clock/data pins for a given card number
  webServer.on("/replayCard", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->params() == 2) {

      String binaryData = "";
      int numOfBits = 0;
      String cardNo = "";
      int numOfDigits = 0;

      AsyncWebParameter* param1 = request->getParam(0);
      if (param1->name() == "b") {
        binaryData = param1->value();
        numOfBits = binaryData.length();
      }

      AsyncWebParameter* param2 = request->getParam(1);
      if (param2->name() == "c") {
        cardNo = param2->value();
        numOfDigits = cardNo.length();
      }

      if (numOfBits > 0 && numOfDigits > 0) {
        CardReplayGPIO(numOfBits, binaryData, cardNo);
      }
    }

    request->send(200, "text/html", GetRedirectHTML());
  });

  //Renders page and shows all collected log data
  webServer.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = "<!doctype html><html><head>";
    if (autoRefreshCardData) {
      html += "<meta http-equiv=\"refresh\" content=\"" + String(HTML_AUTO_REFRESH_SECONDS) + "\">";
    }
    html += "<meta charset=\"utf-8\">";
    html += "<title>Paxtogeddon Reader</title><meta charset=\"utf-8\">";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    html += "<style> .tbl { border-collapse: collapse; margin: 10px 0; font-size: 12px;";
    html += "width:100%; box-shadow: 0 0 20px rgba(0, 0, 0, 0.15); }";
    html += ".tbl thead tr { background-color: #009879; color: #ffffff; text-align: left; }";
    html += ".tbl th, .tbl td { padding: 12px 15px; }";
    html += ".tbl tbody tr { border-bottom: 1px solid #dddddd; }";
    html += ".tbl tbody tr:nth-of-type(even) { background-color: #f3f3f3; }";
    html += ".tbl tbody tr:last-of-type { border-bottom: 2px solid #009879; }";
    html += "a:link { text-decoration: none; color: #000; }";
    html += "a:visited { text-decoration: none; color: #000;}";
    html += "a:hover { text-decoration: none; color: #000;}";
    html += "a:active { text-decoration: none; color: #000;}";
    html += "body { font-family: Arial, sans-serif; font-size: 12px; }";
    html += ".btns { display:flex; font-size: 13px; margin: 0 0 12px 0; }";
    html += ".btn { background-color: #e7e7e7; border:solid 1px #cccccc; color: black;";
    html += "padding: 10px 12px; margin: 0 5px 0 0; text-align: center; text-decoration: none;";
    html += "display: block; cursor: pointer; }";
    html += ".head { background-color:#1F272A; color:white; text-align: center; width:100%;";
    html += "padding: 16px 0; margin: 0 0 10px 0; font-size: 16px; font-weight:bold; }";
    html += ".opcon { font-size: 12px; background-color:#000000; padding: 5px 0 5px 5px; }";
    html += ".output { background-color:#000000; color:#CCC; text-align: left; width:100%;";
    html += "font-size: 12px; font-weight:bold; max-height: 150px; overflow-y: scroll; word-wrap: break-word; }";
    html += "::-webkit-scrollbar { width: 10px; }";
    html += "::-webkit-scrollbar-track { background: #000000; }";
    html += "::-webkit-scrollbar-thumb {  background: #888; }";
    html += "::-webkit-scrollbar-thumb:hover { background: #888; }";
    html += ".binary { word-wrap: break-word; max-width: 10vw; }";
    html += "div.container { width:98%; margin:1%; }";
    html += "@media screen and (max-width: 419px) { .auto-hide1 { display: none; } }";
    html += "@media screen and (max-width: 660px) { .auto-hide { display: none; } } </style>";
    html += "<script> function confirmDelete() {";
    html += "if (confirm(\"Are you sure you want to clear the log?\")) {";
    html += "document.location=\"" + GetBaseURL() + "/clearLog\"; } }";
    html += "function confirmReboot() {";
    html += "if (confirm(\"Are you sure you want to reboot the ESP32?\"))	{";
    html += "document.location=\"" + GetBaseURL() + "/rebootESP32\"; } } </script>";
    html += "</head><body><div class=\"container\">";
    html += "<div class=\"head\">🔻 Paxtogeddon Reader 🔻</div>";
    html += "<div class=\"btns\"><div class=\"btn\"><a href=\"" + GetBaseURL() + "/toggleRefresh\">";
    html += autoRefreshCardData == true ? "⏳ Refresh on" : "📌 Refresh off";
    html += "</a></div><div class=\"btn\"><a href=\"" + GetBaseURL() + "/downloadLog\">🔑 Export</a></div>";
    html += "<div class=\"btn\"><a href=\"javascript:confirmDelete();\">❌ Clear</a></div>";
    html += "<div class=\"btn auto-hide1\"><a href=\"javascript:confirmReboot();\">⚡ Reboot</a></div></div>";
    html += "<div class=\"opcon\"><div class=\"output\">" + lastCardData + "</div></div>";
    html += "<table class=\"tbl\"><thead><tr>";
    html += "<th>Card Number</th>";
    html += "<th>Card Type</th>";
    html += "<th>Colour</th>";
    html += "<th class=\"auto-hide\">Bit Count</th>";
    html += "<th class=\"auto-hide\">Binary</th></tr></thead><tbody>";

    bool gotCards = false;
    File logFile = SPIFFS.open("/card_data.txt", "r");

    if (logFile) {
      while (logFile.available()) {
        String line = logFile.readStringUntil('\n');
        line.trim();

        if (line.length() > 0) {
          gotCards = true;
          String cardNumber = SplitString(line, ',', 0);
          String bitCount = SplitString(line, ',', 1);
          String binary = SplitString(line, ',', 2);
          String cardType = SplitString(line, ',', 3);
          String colour = SplitString(line, ',', 4);

          html += "<tr>";
          html += "<td><a href=\"" + GetBaseURL() + "/replayCard?b="
                  + binary + "&c=" + cardNumber + "\">▶ " + cardNumber + "</a></td>";
          html += "<td>" + cardType + "</td>";
          html += "<td>" + colour + "</td>";
          html += "<td class=\"auto-hide\">" + bitCount + "</td>";
          html += "<td class=\"binary auto-hide\">" + binary + "</td>";
          html += "</tr>";
        }
      }

      logFile.close();
    }

    if (!gotCards) {
      html += "<tr><td>No card data is available</td></tr>";
    }

    html += "</tbody></table></div></body></html>";
    request->send(200, "text/html", html);
  });

  webServer.begin();

  //Keeps task alive
  while (true) {
    //vTaskDelay(10 / portTICK_PERIOD_MS);
    vTaskDelay(portMAX_DELAY);
  }
}

//----- On Card - Interrupt Handler ---------------------------------------------------------------------------------
void IRAM_ATTR OnCard() {
  //This is purely for debug purposes
  interruptFired = true;

  if (processingData) {
    //We are processing the bits so do nothing.
    //We don't want the bit count and card data to be updated whilst processing!
    //I left this code path here for potential future updates! ;-)
  } else {
    //Checks if last recorded micros is higher than the current micros
    //If so, micros has overflowed back to zero.
    //We now need to set the last recorded micros back to zero as well
    if (lastMicros > micros()) {
      lastMicros = 0;
    }

    //Debounce to ensure all bits are recevied correctly
    if (micros() - lastMicros >= DEBOUNCE_TIME) {

      //Add received bit to card array
      //bit is inverted
      cardData[bitCount] = digitalRead(DATA_PIN) == 1 ? 0 : 1;

      //Check for bit count overflow
      if (bitCount < 256) {
        bitCount = bitCount + 1;
      }

      lastMicros = micros();
    }
  }
}


//----- Setup -------------------------------------------------------------------------------------------------------
void setup() {
  pinMode(CLOCK_PIN, INPUT);
  pinMode(DATA_PIN, INPUT);
  pinMode(REPLAY_CLOCK_PIN, OUTPUT);
  pinMode(REPLAY_DATA_PIN, OUTPUT);
  pinMode(WIFI_MODE_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(HEARTBEAT_LED_PIN, OUTPUT);
  digitalWrite(REPLAY_CLOCK_PIN, 1);
  digitalWrite(REPLAY_DATA_PIN, 1);
  digitalWrite(GREEN_LED_PIN, 0);
  digitalWrite(RED_LED_PIN, 0);
  digitalWrite(YELLOW_LED_PIN, 0);
  digitalWrite(HEARTBEAT_LED_PIN, 0);

  if (DEBUG_MODE) {
    Serial.begin(SERIAL_BAUD_RATE);
    delay(2000);
    Serial.println("Booting...");
  }

  if (!SPIFFS.begin(true)) {
    if (DEBUG_MODE) {
      Serial.println("SPIFFS mount failed");
    }

    while (true) {
      LedControl(false, false, true, 100);
    }
  }

  if (DEBUG_MODE) {
    Serial.println("Loading card data...");
    LoadCardData();
  }

  ConfigureWiFi();

  xTaskCreatePinnedToCore(
    WebServerTask,    //Method caled
    "WebServerTask",  //Name
    8192,             //Stack size (bytes)
    NULL,             //Parameter passed to the method
    1,                //Priority
    NULL,             //Handle
    0                 //Pinned to core 0
  );

  LedControl(true, true, true, 100);
  attachInterrupt(CLOCK_PIN, OnCard, FALLING);
  //attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), onCard, FALLING);
}

//----- Loop --------------------------------------------------------------------------------------------------------
void loop() {
  //By default "Ardunio" and "Events" are running on Core 1
  digitalWrite(HEARTBEAT_LED_PIN, 1);
  delay(50);
  digitalWrite(HEARTBEAT_LED_PIN, 0);
  delay(50);

  //This is purely for debug purposes
  if (DEBUG_MODE) {
    if (interruptFired) {
      Serial.println("Interrupt fired");
      Serial.print("micros(): ");
      Serial.println(micros());
      Serial.print("lastMicros: ");
      Serial.println(lastMicros);
      Serial.print("micros() - lastMicros: ");
      Serial.println(micros() - lastMicros);
      interruptFired = false;
    }
  }

  //Reboots the ESP32 after receiving a request from the web server
  //Waits 5 seconds to ensure the web page has been fully sent/rendered
  if (systemReboot) {
    systemReboot = false;
    digitalWrite(HEARTBEAT_LED_PIN, 1);
    delay(3000);
    if (DEBUG_MODE) {
      Serial.println("Rebooting...");
    }
    delay(2000);
    ESP.restart();
    return;
  }

  if (!CheckBitCount()) {
    return;
  }

  if (!CheckLeadin()) {
    return;
  }

  if (!CheckLeadout()) {
    return;
  }

  processingData = true;

  if (bitCount == net2Bits) {
    ParseNet2();
  }

  if (bitCount == switch2Bits) {
    ParseSwitch2();
  }

  bitCount = 0;
  processingData = false;
}