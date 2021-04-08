#include ".\src\EasyClient\EasyClient.h"
#include ".\src\DeviceController\DeviceController.h"
#include ".\src\Constant\Constant.h"
#include ".\src\EasyWifi\EasyWifi.h"

EasyWifi wifi;
DeviceController deviceController;
unsigned long previousMillis = 0;

const char* trigger_endpoint = "http://192.168.4.1/off/1";

void setup()
{
  Serial.begin(115200);
  wifi.initWifi();
  deviceController.init();
}

void loop()
{
  int val = deviceController.readWaterSensor();
  Serial.print("Water Sensor: ");
  Serial.println(val);
  if (val > 0) {
    httpGETRequest(trigger_endpoint);
  }
  delay(1000);
}
