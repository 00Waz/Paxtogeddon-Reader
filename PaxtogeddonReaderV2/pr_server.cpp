#include "pr_server.h"

namespace prServer {

String baseURL = "";
bool showCloneAction = false;
bool autoRefresh = false;

void ServerInit(void) {
  //Method called, Name, Stack size (bytes), param passed, priority, handle, core
  xTaskCreatePinnedToCore(ServerTasks, "ServerTasks", 8192, NULL, 1, NULL, 0);
}

static void ServerTasks(void* p) {
  //Connect to WiFi or Start AP
  bool captivePortalEnabled = prSettings::allowCaptivePortal;
  if (prSettings::wifiSSID == "" || prSettings::wifiPassword == "") {
    prSettings::oneShotConnectToAP = false;
  }

  if (prSettings::oneShotConnectToAP) {
    captivePortalEnabled = false;
    WiFi.mode(WIFI_STA);
    WiFi.begin(prSettings::wifiSSID, prSettings::wifiPassword);
    while (WiFi.status() != WL_CONNECTED) {
      prUtil::LedControl(false, true, false, false);
      prUtil::LedControl(true, false, true, false);
    }
    prUtil::LedControl(true, true, true, false);
    baseURL = "http://" + WiFi.localIP().toString();
    prSettings::wifiIP = WiFi.localIP();
  } else {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(prSettings::apSSID, prSettings::apPassword);
    IPAddress apSubnet(255, 255, 255, 0);
    WiFi.softAPConfig(prSettings::apIP, prSettings::apIP, apSubnet);
    delay(500);
    baseURL = "http://" + prSettings::apIP.toString();
  }

  //Start DNS server
  DNSServer dnsServer;
  if (captivePortalEnabled) {
    dnsServer.start(53, "*", prSettings::apIP);
  }

  //Start web server
  AsyncWebServer webServer(80);
  webServer.begin();


  //----- Captive Portal ----------------------------------------------------------------------------------------------------
  if (captivePortalEnabled) {
    //Android captive portal.
    webServer.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->redirect(baseURL);
    });

    //iOS captive portal.
    webServer.on("/hotspot-detect.html", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->redirect(baseURL);
    });

    //Windows captive portal
    webServer.on("/connecttest.txt", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->send(200, "text/html", "ok");
    });

    //Windows captive portal
    webServer.on("/redirect", HTTP_GET, [](AsyncWebServerRequest* request) {
      request->redirect(baseURL);
    });
  }
  //-------------------------------------------------------------------------------------------------------------------------


  //----- Paxtogeddon Reader ------------------------------------------------------------------------------------------------
  //Shows home page
  webServer.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    int requestedPage = 1;
    if (!autoRefresh && request->params() == 1 && request->hasParam("page")) {
      AsyncWebParameter* p1 = request->getParam("page");
      String page = p1->value();
      if (prUtil::IsNumeric(page)) {
        requestedPage = page.toInt();
      }
    }

    String html = prHTML::Header(autoRefresh, requestedPage);
    html += prHTML::Menu(autoRefresh);
    html += prHTML::VersionAndBuild();
    html += prHTML::LastCardData();
    html += prHTML::CardData(autoRefresh, requestedPage, showCloneAction);
    html += prHTML::Footer();
    request->send(200, "text/html", html);
  });


  //Companion detect
  webServer.on("/companionDetect", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", "paxtogeddon-reader");
  });


  //Get special cards (test and functions)
  webServer.on("/getSpecialCards", HTTP_GET, [](AsyncWebServerRequest* request) {
    String data = prSettings::TEST_CARD + ",";
    data += prSettings::FC_DEFAULT + ",";
    data += prSettings::FC_CONNECT_TO_AP + ",";
    data += prSettings::FC_SHOW_AP_INFO;
    request->send(200, "text/html", data);
  });


  //Companion clone action button
  webServer.on("/enableCloneAction", HTTP_GET, [](AsyncWebServerRequest* request) {
    showCloneAction = true;
    request->send(200, "text/html", "ok");
  });

  webServer.on("/disableCloneAction", HTTP_GET, [](AsyncWebServerRequest* request) {
    showCloneAction = false;
    request->send(200, "text/html", "ok");
  });


  //Replays binary data via clock/data
  webServer.on("/replayCard", HTTP_GET, [](AsyncWebServerRequest* request) {
    int requestedPage = 1;

    if (request->params() == 3) {
      String cardNo = "";
      int numOfDigits = 0;
      String binaryData = "";
      int numOfBits = 0;

      if (request->hasParam("page")) {
        AsyncWebParameter* p1 = request->getParam("page");
        String page = p1->value();
        if (prUtil::IsNumeric(page)) {
          requestedPage = page.toInt();
        }
      }

      if (request->hasParam("n")) {
        AsyncWebParameter* p2 = request->getParam("n");
        cardNo = p2->value();
        numOfDigits = cardNo.length();
      }

      if (request->hasParam("b")) {
        AsyncWebParameter* p3 = request->getParam("b");
        binaryData = p3->value();
        numOfBits = binaryData.length();
      }

      if (numOfBits > 0 && numOfDigits > 0) {
        prSettings::replayBin = binaryData;
        prSettings::lastCardData = "Card Replay<br>";
        prSettings::lastCardData += "Card number: " + cardNo + "<br>";
        prSettings::lastCardData += "Bits: " + String(numOfBits) + "<br>";
        prSettings::lastCardData += "Bin: " + binaryData + "<br>";
        prUtil::OLEDShowMessage(":Card Replay:", cardNo, ":Bits:", String(numOfBits), "", "");
      }
    }

    request->redirect(baseURL + "/?page=" + String(requestedPage));
  });


  //Toggle auto refresh on/off
  webServer.on("/toggleRefresh", HTTP_GET, [](AsyncWebServerRequest* request) {
    autoRefresh = !autoRefresh;
    request->redirect(baseURL);
  });


  //Shows send card number page
  webServer.on("/sendCardNumber", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = prHTML::Header(false, 1);
    html += prHTML::SendCardNumber();
    html += prHTML::Footer();
    request->send(200, "text/html", html);
  });


  //Send clock/data (data recevied from send card number page)
  webServer.on("/sendClockData", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->params() == 1) {
      String cardNo = "";
      int numOfDigits = 0;

      if (request->hasParam("n")) {
        AsyncWebParameter* p1 = request->getParam("n");
        cardNo = p1->value();
        numOfDigits = cardNo.length();
      }

      if (numOfDigits > 0 && numOfDigits < 9 && prUtil::IsNumeric(cardNo)) {
        prSettings::replayBin = cardNo;
        prSettings::lastCardData = "Send clock/data<br>";
        prSettings::lastCardData += "Card number: " + cardNo + "<br>";
        prSettings::lastCardData += "Bits: 75 <br>";
        prUtil::OLEDShowMessage(":Card Replay:", cardNo, ":Bits:", "75", "", "");
      }
    }
    request->redirect(baseURL);
  });


  //Download/view raw log
  webServer.on("/exportLog", HTTP_GET, [](AsyncWebServerRequest* request) {
    bool logAvailable = false;
    File logFile = SPIFFS.open("/card_data.txt", "r");
    if (logFile) {
      if (logFile.available()) {
        logAvailable = true;
      }
      logFile.close();
    }

    if (logAvailable && request->params() == 1 && request->hasParam("d")) {
      AsyncWebParameter* p1 = request->getParam("d");
      bool download = true;
      if (p1->value() == "0") {
        download = false;
      }
      request->send(SPIFFS, "/card_data.txt", String(), download);
      return;
    }

    prSettings::lastCardData = "Logfile not available";
    request->redirect(baseURL);
  });


  //Shows confirm clear log page
  webServer.on("/confirmClearLog", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = prHTML::Header(false, 1);
    html += prHTML::ConfirmMessage("clearLog", "Are you sure you want to clear the log?");
    html += prHTML::Footer();
    request->send(200, "text/html", html);
  });


  //Clear log
  webServer.on("/clearLog", HTTP_GET, [](AsyncWebServerRequest* request) {
    SPIFFS.remove("/card_data.txt");
    prSettings::lastCardData = "Logfile cleared";
    request->redirect(baseURL);
  });


  //Shows confirm reboot ESP32 page
  webServer.on("/confirmReboot", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = prHTML::Header(false, 1);
    html += prHTML::ConfirmMessage("rebootESP32", "Are you sure you want to reboot the ESP32?");
    html += prHTML::Footer();
    request->send(200, "text/html", html);
  });


  //Reboot ESP32
  webServer.on("/rebootESP32", HTTP_GET, [](AsyncWebServerRequest* request) {
    autoRefresh = false;
    prSettings::lastCardData = "Reboot command sent";
    prUtil::RequestReboot(5000);
    request->redirect(baseURL);
  });


  //Shows settings page
  webServer.on("/viewSettings", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = prHTML::Header(false, 1);
    html += prHTML::ViewSettings("");
    html += prHTML::Footer();
    request->send(200, "text/html", html);
  });


  //Save settings
  webServer.on("/saveSettings", HTTP_POST, [](AsyncWebServerRequest* request) {
    bool hasAllParams = true;
    String message = "";

    if (request->params() > 0) {
      if (!request->hasParam("apname", true)) { hasAllParams = false; }
      if (!request->hasParam("appassword", true)) { hasAllParams = false; }
      if (!request->hasParam("apip", true)) { hasAllParams = false; }
      if (!request->hasParam("ssid", true)) { hasAllParams = false; }
      if (!request->hasParam("ssidpassword", true)) { hasAllParams = false; }
      if (!request->hasParam("refreshseconds", true)) { hasAllParams = false; }

      if (hasAllParams) {
        AsyncWebParameter* p1 = request->getParam("apname", true);
        String p1_apname = p1->value();
        AsyncWebParameter* p2 = request->getParam("appassword", true);
        String p2_appassword = p2->value();
        AsyncWebParameter* p3 = request->getParam("apip", true);
        String p3_apip = p3->value();
        AsyncWebParameter* p4 = request->getParam("ssid", true);
        String p4_ssid = p4->value();
        AsyncWebParameter* p5 = request->getParam("ssidpassword", true);
        String p5_ssidpassword = p5->value();
        AsyncWebParameter* p6 = request->getParam("refreshseconds", true);
        String p6_refreshseconds = p6->value();

        p1_apname.trim();
        if (p1_apname.length() < 8) {
          hasAllParams = false;
          message += "AP name must be at least 8 characters";
        }

        p2_appassword.trim();
        if (p2_appassword.length() < 8) {
          hasAllParams = false;
          if (message != "") { message += "<br>"; }
          message += "AP password must be at least 8 characters";
        }

        p3_apip.trim();
        if (prUtil::IsIpAddress(p3_apip) == false) {
          hasAllParams = false;
          if (message != "") { message += "<br>"; }
          message += "Please enter a valid AP IP address";
        }

        p6_refreshseconds.trim();
        if (p6_refreshseconds == "") {
          hasAllParams = false;
          if (message != "") { message += "<br>"; }
          message += "HTML auto refresh seconds cannot be empty";
        } else {
          if (prUtil::IsNumeric(p6_refreshseconds) == false) {
            p6_refreshseconds = "5";
          }
          int rs = p6_refreshseconds.toInt();
          if (rs < 1 || rs > 60) {
            p6_refreshseconds = "5";
          }
        }

        if (hasAllParams) {
          prSettings::apSSID = p1_apname;
          prSettings::apPassword = p2_appassword;
          prSettings::apIP.fromString(p3_apip);
          prSettings::wifiSSID = p4_ssid;
          prSettings::wifiPassword = p5_ssidpassword;
          prSettings::webPollSeconds = p6_refreshseconds;
          prSettings::allowCaptivePortal = false;
          prSettings::oledConnected = false;

          if (request->hasParam("allowcaptiveportal", true)) {
            AsyncWebParameter* p7 = request->getParam("allowcaptiveportal", true);
            if (p7->value() == "on") {
              prSettings::allowCaptivePortal = true;
            }
          }

          if (request->hasParam("oledconnected", true)) {
            AsyncWebParameter* p8 = request->getParam("oledconnected", true);
            if (p8->value() == "on") {
              prSettings::oledConnected = true;
            }
          }

          prUtil::SaveSettings();
          message = "Settings have been saved<br>Reboot command sent";
          prUtil::RequestReboot(5000);
        }
      }
    }

    String html = prHTML::Header(false, 1);
    html += prHTML::ViewSettings(message);
    html += prHTML::Footer();
    request->send(200, "text/html", html);
  });
  //-------------------------------------------------------------------------------------------------------------------------


  //----- No found route, send 404 ------------------------------------------------------------------------------------------
  webServer.onNotFound([](AsyncWebServerRequest* request) {
    request->send(404);
  });
  //-------------------------------------------------------------------------------------------------------------------------

  //Keep task alive
  while (true) {
    vTaskDelay(portMAX_DELAY);
  }
}

}  //namespace prServer
