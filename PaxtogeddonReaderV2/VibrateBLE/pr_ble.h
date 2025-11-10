#ifndef PR_BLE_H
#define PR_BLE_H

#include <Arduino.h>
#include "BLEDevice.h"
#include "BLEClient.h"
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "pr_settings.h"
#include "pr_util.h"

namespace prBLE {

void FitProM4Init(void);
void MaintainConnection(void);
void InputTriggerHandler(void);
void ScanDevices(void);
static void Vibrate(void);

}  //namespace prBLE

#endif
