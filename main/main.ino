#include "src\Constant\Constant.h"
#include "src\EasyWifi\EasyWifi.h"

EasyWifi wifi;

void setup() {
  Serial.begin(115200);
  wifi.initWifi();
  wifi.initFirebase();
  wifi.writeDouble("abc", 123.0);
  wifi.writeInt("def", 4567);
}

void loop() {
   Serial.println(wifi.readInt("def"));
   delay(500);
}
