#include "pr_cardreader.h"

namespace prCardReader {

const unsigned long DEBOUNCE_TIME = 350;
volatile unsigned long lastMicros = 0;
volatile unsigned int bitCount = 0;
volatile bool processingData = false;
volatile unsigned int cardData[256];
unsigned int net2Bits = 75;
unsigned int switch2Bits = 220;

void CardReaderInit(void) {
  attachInterrupt(prSettings::CLOCK_PIN, OnCard, FALLING);
}

void ParseCard(void) {
  if (prSettings::replayBin != "") {
    processingData = true;
    if (prSettings::replayBin.length() < net2Bits) {
      String binary = prUtil::CalculateBinary(prSettings::replayBin);
      prUtil::SendClockData(binary);
    } else {
      prUtil::SendClockData(prSettings::replayBin);
    }
    prSettings::replayBin = "";
    bitCount = 0;
    processingData = false;
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

static void IRAM_ATTR OnCard(void) {
  if (!processingData) {
    if (lastMicros > micros()) {
      lastMicros = 0;
    }

    //Debounce to ensure all bits are recevied correctly
    if (micros() - lastMicros >= DEBOUNCE_TIME) {

      //Add received bit to card array, bit is inverted
      cardData[bitCount] = digitalRead(prSettings::DATA_PIN) == 1 ? 0 : 1;

      //Check for bit count overflow
      if (bitCount < 256) {
        bitCount = bitCount + 1;
      }

      lastMicros = micros();
    }
  }
}

static bool IsFunctionCard(String cardNumber) {
  if (cardNumber == prSettings::FC_DEFAULT) { return true; }
  if (cardNumber == prSettings::FC_CONNECT_TO_AP) { return true; }
  if (cardNumber == prSettings::FC_SHOW_AP_INFO) { return true; }
  return false;
}

static void ProcessFunctionCard(String cardNumber) {
  if (cardNumber == prSettings::FC_DEFAULT) {
    prSettings::lastCardData = "Function card: Default settings";
    prUtil::OLEDShowMessage(":Function Card:", "Default settings", "", "", "", "");
    prUtil::LedControl(true, false, false, false);
    prUtil::ClearSettings();
    prUtil::RequestReboot(1000);
  }

  if (cardNumber == prSettings::FC_CONNECT_TO_AP) {
    if (prSettings::oneShotConnectToAP) {
      prSettings::lastCardData = "Function card: Create AP";
      prUtil::OLEDShowMessage(":Function Card:", "Create AP", "", "", "", "");
      prUtil::LedControl(true, false, false, false);
      prUtil::RequestReboot(1000);
    } else {
      prSettings::lastCardData = "Function card: Connect to AP";
      prUtil::OLEDShowMessage(":Function Card:", "Connect to AP", "", "", "", "");
      prUtil::LedControl(true, false, false, false);
      prUtil::RequestRebootAndConnectToAP(1000);
    }
  }

  if (cardNumber == prSettings::FC_SHOW_AP_INFO) {
    prSettings::lastCardData = "Function card: Show AP Info on OLED";
    prUtil::OLEDShowAPInfo();
    prUtil::LedControl(true, false, false, false);
  }
}

static bool SaveCardData(String cardNumber, String bitCount, String binary, String cardType, String colour) {
  File logFile = SPIFFS.open("/card_data.txt", "a");
  if (!logFile) {
    return false;
  }

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

static bool CheckBitCount(void) {
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

    //If the bit count doesn't match Net2 or Switch2 then something went wrong!
    if (bitCount != net2Bits && bitCount != switch2Bits) {
      prSettings::lastCardData = "Bit count error, received: " + String(bitCount);
      prUtil::OLEDShowMessage("Bit count error", "Recevied", String(bitCount), "Expected", String(net2Bits), String(switch2Bits));
      prUtil::LedControl(false, false, true, false);
    } else {
      return true;
    }
  }

  bitCount = 0;
  return false;
}

static bool CheckLeadin(void) {
  //Check first 10 bits are all zero
  for (int i = 0; i < 10; i++) {
    if (cardData[i] != 0) {
      prSettings::lastCardData = "Leadin error";
      prUtil::OLEDShowMessage("Leadin error", "", "", "", "", "");
      prUtil::LedControl(false, false, true, false);
      bitCount = 0;
      return false;
    }
  }

  return true;
}

static bool CheckLeadout(void) {
  //Check last 10 bits are all zero
  for (int i = bitCount - 10; i < bitCount; i++) {
    if (cardData[i] != 0) {
      prSettings::lastCardData = "Leadout error";
      prUtil::OLEDShowMessage("Leadout error", "", "", "", "", "");
      prUtil::LedControl(false, false, true, false);
      bitCount = 0;
      return false;
    }
  }

  return true;
}

static void ParseNet2(void) {
  String cardNumber = "";
  String binary = "";
  String cardType = "Net2";
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
      prSettings::lastCardData = "Row odd parity LRC error<br>";
      prSettings::lastCardData += binary;
      prUtil::OLEDShowMessage("LRC error", "Row odd parity", "", "", "", "");
      prUtil::LedControl(false, false, true, false);
      return;
    }

    //Index 10 from for loop iterator +=5
    //Checks the card start bits are equal to 11 (B in HEX)
    if (i == 10) {
      if (dval != 11) {
        prSettings::lastCardData = "Start bits error - expected 11 but received " + String(dval);
        prUtil::OLEDShowMessage("Start bits error", "Expected", "11", "Received", String(dval), "");
        prUtil::LedControl(false, false, true, false);
        return;
      }
    }

    //Index 55 from for loop iterator +=5
    //Checks the card stop bits are equal to 15 (F in HEX)
    if (i == 55) {
      if (dval != 15) {
        prSettings::lastCardData = "Stop bits error - expected 15 but received " + String(dval);
        prUtil::OLEDShowMessage("Stop bits error", "Expected", "15", "Received", String(dval), "");
        prUtil::LedControl(false, false, true, false);
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
        prSettings::lastCardData = "Column even parity LRC error<br>";
        prSettings::lastCardData += binary;
        prUtil::OLEDShowMessage("LRC error", "Column even parity", "", "", "", "");
        prUtil::LedControl(false, false, true, false);
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

  if (cardNumber == prSettings::TEST_CARD) {
    cardType = "TEST CARD";
  }

  if (!IsFunctionCard(cardNumber)) {
    prSettings::lastCardData = "Card number: " + cardNumber + "<br>";
    prSettings::lastCardData += "Card type: " + cardType + "<br>";
    prSettings::lastCardData += "Card colour: None<br>";
    prSettings::lastCardData += "Bits: " + String(bitCount) + "<br>";
    prSettings::lastCardData += "Bin: " + binary + "<br>";

    if (!SaveCardData(cardNumber, String(bitCount), binary, cardType, "None")) {
      prSettings::lastCardData = "Card save error";
      prUtil::OLEDShowMessage("Card save error", "", "", "", "", "");
      prUtil::LedControl(false, true, false, false);
      return;
    }
    prUtil::OLEDShowMessage(":Card Number:", cardNumber, ":Card Type:", cardType, ":Card Colour:", "None");
    prUtil::LedControl(true, false, false, true);
    return;
  }

  ProcessFunctionCard(cardNumber);
}

static void ParseSwitch2(void) {
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
      prSettings::lastCardData = "Row odd parity LRC error<br>";
      prSettings::lastCardData += binary;
      prUtil::OLEDShowMessage("LRC error", "Row odd parity", "", "", "", "");
      prUtil::LedControl(false, false, true, false);
      return;
    }

    //Index 10 from for loop iterator +=5
    //Checks the card start bits are equal to 11 (B in HEX)
    if (i == 10) {
      if (dval != 11) {
        prSettings::lastCardData = "Start bits error - expected 11 but received " + String(dval);
        prUtil::OLEDShowMessage("Start bits error", "Expected", "11", "Received", String(dval), "");
        prUtil::LedControl(false, false, true, false);
        return;
      }
    }

    //Index 55 from for loop iterator +=5
    //Checks the card digit bits are equal to 13 (D in HEX)
    if (i == 55) {
      if (dval != 13) {
        prSettings::lastCardData = "Digit bits error - expected 13 but received " + String(dval);
        prUtil::OLEDShowMessage("Stop bits error", "Expected", "13", "Received", String(dval), "");
        prUtil::LedControl(false, false, true, false);
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
        prSettings::lastCardData = "Digit bits error - expected 13 but received " + String(dval);
        prUtil::OLEDShowMessage("Stop bits error", "Expected", "13", "Received", String(dval), "");
        prUtil::LedControl(false, false, true, false);
        return;
      }
    }

    //Index 200 from for loop iterator +=5
    //Checks the card stop bits are equal to 15 (F in HEX)
    if (i == 200) {
      if (dval != 15) {
        prSettings::lastCardData = "Stop bits error - expected 15 but received " + String(dval);
        prUtil::OLEDShowMessage("Stop bits error", "Expected", "15", "Received", String(dval), "");
        prUtil::LedControl(false, false, true, false);
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
        prSettings::lastCardData = "Column even parity LRC error<br>";
        prSettings::lastCardData += binary;
        prUtil::OLEDShowMessage("LRC error", "Column even parity", "", "", "", "");
        prUtil::LedControl(false, false, true, false);
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

  if (cardNumber == prSettings::TEST_CARD) {
    cardType = "TEST CARD";
  }

  if (!IsFunctionCard(cardNumber)) {
    prSettings::lastCardData = "Card number: " + cardNumber + "<br>";
    prSettings::lastCardData += "Card type: " + cardType + "<br>";
    prSettings::lastCardData += "Card colour: " + colour + "<br>";
    prSettings::lastCardData += "Bits: " + String(bitCount) + "<br>";
    prSettings::lastCardData += "Bin: " + binary + "<br>";

    if (!SaveCardData(cardNumber, String(bitCount), binary, cardType, colour)) {
      prSettings::lastCardData = "Card save error";
      prUtil::OLEDShowMessage("Card save error", "", "", "", "", "");
      prUtil::LedControl(false, true, false, false);
      return;
    }
    prUtil::OLEDShowMessage(":Card Number:", cardNumber, ":Card Type:", cardType, ":Card Colour:", colour);
    prUtil::LedControl(true, false, false, true);
    return;
  }

  ProcessFunctionCard(cardNumber);
}

}  //namespace prCardReader
