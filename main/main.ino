#include "src\EasyWifi\EasyWifi.h"
#include "src\EasyFirebase\EasyFirebase.h"
#include "src\EasyTime\EasyTime.h"
#include "src\UltrasonicSensor\UltrasonicSensor.h"
#include "src\Calculate\Calculate.h"

EasyWifi wifi;
EasyFirebase firebase;
EasyTime easyTime;
UltrasonicSensor ultrasonicSensor;

const long interval = 60000;
long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  wifi.init();
  firebase.init();
  easyTime.init();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    String path = "root/" + easyTime.getCurrentDate() + "/" + easyTime.getCurrentTime();
    
    int distance = ultrasonicSensor.readDistance();
    double percent = getTankRemainingPercent(distance, 20);
    firebase.writeDouble(path, percent);
    
    previousMillis = currentMillis;
  }
}
