#include "src\Constant\Constant.h"
#include "src\EasyWifi\EasyWifi.h"
#include <FirebaseESP32.h>

EasyWifi wifi;

void setup() {
  Serial.begin(115200);
  wifi.initWifi();
  wifi.initFirebase();
  wifi.writeData("abc", 123.0);
}

void loop() {}
