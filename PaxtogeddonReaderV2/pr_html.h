#ifndef PR_HTML_H
#define PR_HTML_H

#include <Arduino.h>
#include <SPIFFS.h>
#include "pr_settings.h"
#include "pr_util.h"

namespace prHTML {

String Header(bool autoRefresh, int requestedPage);
String Menu(bool autoRefresh);
String VersionAndBuild(void);
String LastCardData(void);
int TotalCardsInLog(void);
String CardData(bool autoRefresh, int requestedPage, bool showCloneAction);
String ConfirmMessage(String action, String message);
String SendCardNumber(void);
String ViewSettings(String message);
String Footer(void);

}  //namespace prHTML

#endif
