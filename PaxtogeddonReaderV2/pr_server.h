#ifndef PR_SERVER_H
#define PR_SERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include "pr_settings.h"
#include "pr_util.h"
#include "pr_html.h"

namespace prServer {

void ServerInit(void);
static void ServerTasks(void* p);

}  //namespace prServer

#endif
