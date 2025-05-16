/*-------------------------------------------------------------------------------------------------------------------
Simple run one time code to format SPIFFS correctly

Flash this to the ESP32 and monitor the serial to make sure it formats correctly
Once done, go ahead and flash Paxtogeddon code
-------------------------------------------------------------------------------------------------------------------*/

#include <Arduino.h>
#include <SPIFFS.h>

void setup() {
  Serial.begin(115200);
  delay(1000); // Allow time for the serial monitor to connect

  Serial.println("Starting SPIFFS formatting...");
  
  if (SPIFFS.begin(true)) { // The `true` argument formats the filesystem if it fails to mount
    Serial.println("SPIFFS mounted successfully");
  } else {
    Serial.println("SPIFFS mount failed. Formatting...");
    if (SPIFFS.format()) {
      Serial.println("SPIFFS formatted successfully");
    } else {
      Serial.println("SPIFFS format failed");
    }
  }
}

void loop() {
  // Nothing to do here
}
