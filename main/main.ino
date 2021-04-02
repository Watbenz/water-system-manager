#include "src\EasyWifi\EasyWifi.h"
#include "src\EasyTime\EasyTime.h"
#include "src\UltrasonicSensor\UltrasonicSensor.h"

EasyWifi wifi;
EasyTime easyTime;
UltrasonicSensor ultrasonicSensor(20);

void setup() {
  Serial.begin(115200);
  wifi.initWifi();
  wifi.initFirebase();
  easyTime.initTime();
}

void loop() {
  Serial.println(easyTime.getCurrentDate());
  delay(1000);
}
