#include "pr_BLE.h"

namespace prBLE {

BLEClient *pClient = nullptr;
BLERemoteCharacteristic *pCharacteristic = nullptr;

void FitProM4Init(void) {
  BLEDevice::init("");
  BLEDevice::setPower(ESP_PWR_LVL_P9);
  pClient = BLEDevice::createClient();
}

void MaintainConnection(void) {
  if (pClient == nullptr) { return; }
  if (pClient->isConnected()) { return; }

  if (prSettings::bleMAC == "") {
    prUtil::StatusLED("flash", 100);
    return;
  }

  if (!pClient->isConnected()) {
    pClient->disconnect();
    pCharacteristic = nullptr;
    prUtil::StatusLED("flash", 1000);
  }

  BLEAddress bleAddress(prSettings::bleMAC.c_str());
  prUtil::StatusLED("flash", 1000);
  pClient->connect(bleAddress, BLE_ADDR_TYPE_PUBLIC, 10000);
  if (pClient->isConnected()) {
    prUtil::StatusLED("flash", 1000);
    BLERemoteService *pService = pClient->getService("6e400001-b5a3-f393-e0a9-e50e24dcca9d");
    if (pService) {
      pCharacteristic = pService->getCharacteristic("6e400002-b5a3-f393-e0a9-e50e24dcca9d");
      if (pCharacteristic != nullptr) {
        prUtil::StatusLED("on", 0);
        Vibrate();
        return;
      }
    }
  }
}

void InputTriggerHandler(void) {
  int count = 0;
  while (digitalRead(prSettings::TRIGGER_PIN) == 0) {
    if (count == 0) {
      Vibrate();
    }
    delay(10);
    count++;
    if (count >= 400) {
      prUtil::ClearSettings();
      ESP.restart();
    }
  }
}

class BLECallBack : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice bleDevice) {
    if (bleDevice.getName() == prSettings::bleManufacturerTarget
        && prSettings::bleMAC == "") {
      prSettings::bleMAC = bleDevice.getAddress().toString();
    }
  }
};

void ScanDevices(void) {
  if (pClient == nullptr) { return; }
  pClient->disconnect();
  pCharacteristic = nullptr;
  prUtil::StatusLED("flash", 500);
  BLEScan *pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new BLECallBack());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->start(5, false);
  pBLEScan->clearResults();
  if (prSettings::bleMAC != "") {
    prUtil::SaveSettings();
    prSettings::bleScanMode = false;
  }
}

static void Vibrate(void) {
  if (pClient == nullptr) { return; }
  if (!pClient->isConnected()) { return; }
  uint8_t vibrateCmd[] = { 205, 0, 6, 18, 1, 11, 0, 1, 1 };
  uint8_t stopCmd[] = { 220, 0, 5, 21, 1, 0, 20, 1 };
  pCharacteristic->writeValue(vibrateCmd, 9);
  prUtil::StatusLED("off", 500);
  pCharacteristic->writeValue(stopCmd, 8);
  prUtil::StatusLED("on", 0);
}

}  //namespace prBLE
