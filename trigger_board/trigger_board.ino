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
  wifi.initSTAAP();
  deviceController.init();
}

void loop()
{
    if (deviceController.readWaterSensor()) {
        httpGETRequest(trigger_endpoint);
    }
    delay(1000);
}
