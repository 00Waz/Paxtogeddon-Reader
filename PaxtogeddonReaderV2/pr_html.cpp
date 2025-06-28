#include "pr_html.h"

namespace prHTML {

String Header(bool autoRefresh, int requestedPage) {
  String html = "<!DOCTYPE html><html onclick=\"\"><head>";
  html += autoRefresh == true ? "<meta http-equiv=\"refresh\" content=\"" + prSettings::webPollSeconds + "\">" : "";
  html += "<meta charset=\"utf-8\"><title>Paxtogeddon Reader</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style type=\"text/css\">";
  html += "body,hr{margin:0}";
  html += ".logo,a:link{color:#fff}";
  html += ".btn,.dropdown-content a,a:link{text-decoration:none}";
  html += ".infoPanel,.tbl,button{font-weight:700}";
  html += ".btns,.infoPanel,.tbl tbody tr{border-bottom:1px solid #404040}";
  html += "body,td,th{color:#ccc;font-family:arial,sans-serif;font-size:12px;-webkit-text-size-adjust:100%}";
  html += "body{background-color:#0d0d0d}";
  html += "hr{padding:0;border:0;height:1px;background:#404040}";
  html += "a:active,a:hover,a:visited{text-decoration:none;color:#fff}";
  html += ".logo{height:60px;font-size:32px}";
  html += ".btns,.infoPanel,button{font-size:12px}";
  html += ".headSpacer{padding-bottom:5px}";
  html += ".btns{display:flex;padding:0 0 10px}";
  html += ".btn{background-color:#1f1f1f;border:1px solid #404040;border-radius:5px;color:#ccc;padding:12px;margin:0 8px 0 0;text-align:center;cursor:pointer}";
  html += ".btn:hover,.dropdown-content{background-color:#2e2e2e}";
  html += ".dropdown,.tooltip{position:relative;display:inline-block}";
  html += ".dropdown-content{display:none;position:absolute;top:42px;min-width:160px;border-radius:5px;box-shadow:0 8px 16px 0 rgba(0,0,0,.2);z-index:1}";
  html += ".dropdown-content a{color:#ccc;font-weight:700;padding:16px;display:block}";
  html += ".dropdown-content a:hover{background-color:#3d3d3d}";
  html += ".dropdown:hover .dropdown-content{display:block}";
  html += ".infoPanel{padding:0 30px 10px 10px;background-color:#0d0d0d;color:#ccc;word-break:break-all}";
  html += ".tbl{border-collapse:collapse;width:100%}";
  html += ".tbl thead tr{background-color:#141414;text-align:left}";
  html += ".tbl td,.tbl th{padding:20px 0 20px 10px;word-break:break-all}";
  html += ".cellSpace{min-width:150px}";
  html += ".cellSpaceBin{width:550px}";
  html += ".actions{display:flex}";
  html += ".action{font-size:18px;padding:0 12px 0 0}";
  html += ".tooltip .tooltiptext{font-size:12px;visibility:hidden;width:120px;background-color:#1f1f1f;color:#fff;text-align:center;border-radius:6px;padding:5px 0;position:absolute;z-index:1;top:0;right:120%}";
  html += ".tooltip .tooltiptext::after{content:\"\";position:absolute;top:50%;left:100%;margin-top:-5px;border-width:5px;border-style:solid;border-color:transparent transparent transparent #1f1f1f}";
  html += ".tooltip:hover .tooltiptext{visibility:visible}";
  html += "form{border:none}";
  html += ".settingsHeader{color:#fff;padding:10px 0 15px;text-decoration:underline}";
  html += ".settingsName{padding:10px 0 5px}";
  html += "input[type=number],input[type=text]{background-color:#0d0d0d;color:#fff;border:1px solid #2a2a2a;border-radius:5px;height:24px;width:100%;max-width:400px;margin:0 0 10px}";
  html += "input[type=checkbox]{position:relative;left:10px;top:2px;margin:0 0 10px}";
  html += "@media screen and (max-width:1100px){ .cellSpace{min-width:100px}}";
  html += "@media screen and (max-width:900px){ .autoHide{display:none} .cellSpace{min-width:50px}}";
  html += "</style><script>";

  html += "var allowMessages = false;";
  html += "function EnableCompanion() { ";
  html += "var companionMenu = document.getElementById('companionMenu');";
  html += "companionMenu.removeAttribute('style','');";
  html += "allowMessages = true; }";
  html += "function PostMessage(message) {";
  html += "if (allowMessages) { window.chrome.webview.postMessage(message);";
  html += "} else { alert('Please open this page in Paxtogeddon Reader Companion to enable this option.') } }";
  html += "</script></head><body><table width=\"100%\" height=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\"><tr><td align=\"center\" valign=\"top\">";
  html += "<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" class=\"headSpacer\"><tr>";
  html += "<td height=\"60\" align=\"left\" valign=\"middle\" bgcolor=\"#1F272A\">";
  html += "<div class=\"logo\"><a href=\"/?page=" + String(requestedPage) + "\"><img src=\"" + prSettings::LOGO_HTML + "\" width=\"240\" height=\"60\"/></a></div></td>";
  html += "</tr></table>";
  return html;
}

String Menu(bool autoRefresh) {
  String html = "";
  html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr><td align=\"left\" valign=\"top\"> ";
  html += "<div class=\"btns\"><form method=\"get\" action=\"/toggleRefresh\">";
  html += "<button type=\"submit\" class=\"btn\">";
  html += autoRefresh == true ? "⏳&nbsp;&nbsp;Auto Refresh On&nbsp;&nbsp;" : "📌&nbsp;&nbsp;Auto Refresh Off&nbsp;&nbsp;";
  html += "</button></form>";

  if (!autoRefresh) {
    html += "<div class=\"dropdown\">";
    html += "<button class=\"btn\">🔽&nbsp;&nbsp;Options&nbsp;&nbsp;</button>";
    html += "<div class=\"dropdown-content\">";
    html += "<a href=\"/sendCardNumber\">Send Card Number</a><hr>";
    html += "<a href=\"/exportLog?d=1\">Download Log</a>";
    html += "<a href=\"/exportLog?d=0\">View Raw Log</a>";
    html += "<a href=\"/confirmClearLog\">Clear Log</a><hr>";
    html += "<a href=\"/confirmReboot\">Reboot</a><hr>";
    html += "<a href=\"/viewSettings\">Settings</a>";
    html += "</div></div>";
    html += "<div id=\"companionMenu\" style=\"visibility: hidden;\" class=\"dropdown\">";
    html += "<button class=\"btn\">🔻&nbsp;&nbsp;Companion&nbsp;&nbsp;</button>";
    html += "<div class=\"dropdown-content\">";
    html += "<a href=\"javascript:PostMessage('PAX_WRITE_CARD')\">Write Card</a><hr>";
    html += "<a href=\"javascript:PostMessage('PAX_SETTINGS')\">Settings</a>";
    html += "</div></div>";
  }

  html += "</div></td></tr></table>";
  return html;
}

String VersionAndBuild(void) {
  String html = "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"infoPanel\">";
  html += "Version: " + prSettings::VERSION_NUMBER + "<br>";
  html += "Build Date: " + prSettings::BUILD_DATE;
  html += "</div></td></tr></table>";
  return html;
}

String LastCardData(void) {
  String html = "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"infoPanel\">";
  html += prSettings::lastCardData;
  html += "</div></td></tr></table>";
  return html;
}

int TotalCardsInLog(void) {
  int logCount = 0;
  File logFile = SPIFFS.open("/card_data.txt", "r");
  if (logFile) {
    while (logFile.available()) {
      String line = logFile.readStringUntil('\n');
      line.trim();
      if (line.length() > 0) {
        logCount++;
      }
    }
    logFile.close();
  }
  return logCount;
}

String CardData(bool autoRefresh, int requestedPage, bool showCloneAction) {
  int logCount = TotalCardsInLog();
  String cardRows[logCount + 10];
  int totalPages = 0;

  if (logCount <= 10) {
    totalPages = 1;
    requestedPage = 1;
  } else {
    totalPages = ceil((float)logCount / 10);
    if (requestedPage > totalPages) {
      requestedPage = 1;
    }
  }

  if (logCount > 0) {
    File logFile = SPIFFS.open("/card_data.txt", "r");
    if (logFile) {
      for (int i = 0; i < logCount + 10; i++) {
        cardRows[i] = "";
      }
      int i = logCount;
      while (logFile.available()) {
        String line = logFile.readStringUntil('\n');
        line.trim();
        if (line.length() > 0) {
          cardRows[i] = line;
          i--;
        }
      }
      logFile.close();
    } else {
      logCount = 0;
    }
  }

  String html = "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"infoPanel\">";
  html += "Total cards in log: " + String(logCount) + "<br>";
  html += logCount > 0 ? "Page " + String(requestedPage) + " of " + String(totalPages) : "";
  html += "</div></td></tr></table>";

  if (!autoRefresh && logCount > 10) {
    html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
    html += "<td align=\"left\" valign=\"top\"><div class=\"btns\">";
    html += requestedPage > 1 ? "<a href=\"/?page=" + String(requestedPage - 1) + "\" class=\"btn\">◀&nbsp;&nbsp;Previous&nbsp;</a>" : "";
    html += requestedPage < totalPages ? "<a href=\"/?page=" + String(requestedPage + 1) + "\" class=\"btn\">&nbsp;Next&nbsp;&nbsp;▶</a>" : "";
    html += "</div></td></tr></table>";
  }

  html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"> <table class=\"tbl\"><thead><tr>";
  html += "<th class=\"cellSpace\">Number</th>";
  html += "<th class=\"cellSpace\">Type</th>";
  html += "<th class=\"cellSpace\">Colour</th>";
  html += "<th class=\"cellSpace\">Actions</th>";
  html += "<th class=\"cellSpace autoHide\">Bits</th>";
  html += "<th class=\"cellSpaceBin autoHide\">Bin</th>";
  html += "</tr></thead><tbody>";

  if (logCount > 0) {
    int start = 1;
    int end = requestedPage * 10;
    if (requestedPage > 1) {
      start = ((requestedPage - 1) * 10) + 1;
    }

    for (int i = start; i <= end; i++) {
      if (cardRows[i] == "") {
        break;
      }

      String cardNumber = prUtil::SplitString(cardRows[i], ',', 0);
      String bits = prUtil::SplitString(cardRows[i], ',', 1);
      String bin = prUtil::SplitString(cardRows[i], ',', 2);
      String cardType = prUtil::SplitString(cardRows[i], ',', 3);
      String cardColour = prUtil::SplitString(cardRows[i], ',', 4);

      String cardRow = "<tr>";
      cardRow += "<td>" + cardNumber + "</td>";
      cardRow += "<td>" + cardType + "</td>";
      cardRow += "<td>" + cardColour + "</td>";

      if (!autoRefresh) {
        cardRow += "<td><div class=\"actions\">";
        cardRow += "<a class=\"action tooltip\" href=\"/replayCard?page=" + String(requestedPage) + "&n=" + cardNumber + "&b=" + bin + "\">";
        cardRow += "🔑<span class=\"tooltiptext\">Replay Card</span></a>";
        if (showCloneAction && cardType == "Net2") {
          cardRow += "<a class=\"action tooltip\" href=\"javascript:PostMessage('CLONE_CARD," + cardNumber + "," + cardType + "," + cardColour + "," + bin + "')\">";
          cardRow += "🔐<span class=\"tooltiptext\">Clone Card</span></a>";
        }
        cardRow += "</div></td>";
      } else {
        cardRow += "<td>-</td>";
      }

      cardRow += "<td class=\"autoHide\">" + bits + "</td>";
      cardRow += "<td class=\"autoHide\">" + bin + "</td>";
      cardRow += "</tr>";
      html += cardRow;
    }
  } else {
    html += "<tr><td>Log is empty</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>";
    html += "<td class=\"autoHide\">&nbsp;</td><td class=\"autoHide\">&nbsp;</td> </tr>";
  }

  html += "</tbody></table></td></tr></table>";
  return html;
}

String ConfirmMessage(String action, String message) {
  String html = "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"btns\">";
  html += "<a href=\"/" + action + "\" class=\"btn\">✅&nbsp;&nbsp;OK&nbsp;&nbsp;</a>";
  html += "<a href=\"/\" class=\"btn\">❌&nbsp;&nbsp;Cancel&nbsp;&nbsp;</a>";
  html += "</div></td></tr></table>";
  html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"infoPanel\">";
  html += "<p>" + message + "</p>";
  html += "</div></td></tr></table>";
  return html;
}

String SendCardNumber(void) {
  String html = "<form id=\"esp32\" name=\"esp32\" method=\"get\" enctype=\"multipart/form-data\" action=\"/sendClockData\">";
  html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"btns\">";
  html += "<button type=\"submit\" class=\"btn\">✅&nbsp;&nbsp;Send&nbsp;&nbsp;</button>";
  html += "<a href=\"/\" class=\"btn\">❌&nbsp;&nbsp;Cancel&nbsp;&nbsp;</a>";
  html += "</div></td></tr></table>";
  html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"infoPanel\">";
  html += "<div class=\"settingsName\">Net2 Card Number</div><input type=\"number\" id=\"n\" name=\"n\">";
  html += "</div></td></tr></table></form>";
  return html;
}

String ViewSettings(String message) {
  String allowCaptivePortal = prSettings::allowCaptivePortal == true ? "checked" : "";
  String oledConnected = prSettings::oledConnected == true ? "checked" : "";
  String html = "<form id=\"esp32Settings\" name=\"esp32Settings\" method=\"post\" enctype=\"multipart/form-data\" action=\"/saveSettings\">";
  html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"btns\">";
  html += "<button type=\"submit\" class=\"btn\">✅&nbsp;&nbsp;Save&nbsp;&nbsp;</button>";
  html += "<a href=\"/\" class=\"btn\">❌&nbsp;&nbsp;Cancel&nbsp;&nbsp;</a>";
  html += "</div></td></tr></table>";

  if (message != "") {
    html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
    html += "<td align=\"left\" valign=\"top\"><div class=\"infoPanel\">";
    html += "<p>" + message + "</p>";
    html += "</div></td></tr></table>";
  }

  html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"infoPanel\">";
  html += "<div class=\"settingsHeader\">When creating an Access Point</div>";
  html += "<div class=\"settingsName\">Access Point Name</div><input type=\"text\" id=\"apname\" name=\"apname\" value=\"" + prSettings::apSSID + "\">";
  html += "<div class=\"settingsName\">Access Point Password</div><input type=\"text\" id=\"appassword\" name=\"appassword\" value=\"" + prSettings::apPassword + "\">";
  html += "<div class=\"settingsName\">Access Point IP Address</div><input type=\"text\" id=\"apip\" name=\"apip\" value=\"" + prSettings::apIP.toString() + "\">";
  html += "</div></td></tr></table>";
  html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"infoPanel\">";
  html += "<div class=\"settingsHeader\">When connecting to an Access Point</div>";
  html += "<div class=\"settingsName\">SSID</div><input type=\"text\" id=\"ssid\" name=\"ssid\" value=\"" + prSettings::wifiSSID + "\">";
  html += "<div class=\"settingsName\">Password</div><input type=\"text\" id=\"ssidpassword\" name=\"ssidpassword\" value=\"" + prSettings::wifiPassword + "\">";
  html += "</div></td></tr></table>";
  html += "<table width=\"100%\" border=\"0\" cellspacing=\"5\" cellpadding=\"0\"><tr>";
  html += "<td align=\"left\" valign=\"top\"><div class=\"infoPanel\">";
  html += "<div class=\"settingsHeader\">General Settings</div>";
  html += "<div class=\"settingsName\">HTML Auto Refresh (seconds)</div><input type=\"number\" min=\"1\" max=\"60\" id=\"refreshseconds\" name=\"refreshseconds\" value=\"" + prSettings::webPollSeconds + "\">";
  html += "<div class=\"settingsName\">Allow Captive Portal:<input type=\"checkbox\" id=\"allowcaptiveportal\" name=\"allowcaptiveportal\" " + allowCaptivePortal + "> </div>";
  html += "<div class=\"settingsName\">OLED Connected:<input type=\"checkbox\" id=\"oledconnected\" name=\"oledconnected\" " + oledConnected + "></div>";
  html += "</div></td></tr></table></form>";
  return html;
}

String Footer(void) {
  return "<p>&nbsp;</p></td></tr></table></body></html>";
}


}  //namespace prHTML
