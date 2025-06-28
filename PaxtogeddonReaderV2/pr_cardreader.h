#ifndef PR_CARDREADER_H
#define PR_CARDREADER_H

#include <Arduino.h>
#include <SPIFFS.h>
#include "pr_settings.h"
#include "pr_util.h"

namespace prCardReader {

void CardReaderInit(void);
void ParseCard(void);
static void OnCard(void);
static bool IsFunctionCard(String cardNumber);
static void ProcessFunctionCard(String cardNumber);
static bool SaveCardData(String cardNumber, String bitCount, String binary, String cardType, String colour);
static bool CheckBitCount(void);
static bool CheckLeadin(void);
static bool CheckLeadout(void);
static void ParseNet2(void);
static void ParseSwitch2(void);

}  //namespace prCardReader

#endif
