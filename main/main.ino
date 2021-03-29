#include "src\EasyWifi\EasyWifi.h"
#include "src\EasyTime\EasyTime.h"

EasyWifi wifi;
EasyTime t;

void setup() {
  Serial.begin(115200);
  wifi.initWifi();
  wifi.initFirebase();
  t.initTime();
}

void loop() {
  Serial.println(t.getCurrentDate());
  delay(1000);
}
