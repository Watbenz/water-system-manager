#include ".\src\EasyClient\EasyClient.h"
#include ".\src\Constant\Constant.h"
#include ".\src\EasyWifi\EasyWifi.h"

EasyWifi wifi;

const char* status_endpoint = "http://192.168.4.1/status/2";

void setup()
{
  Serial.begin(115200);
  pinMode(DEVICE_OUT, OUTPUT);
  wifi.initWifi();
}

void loop()
{
  int val = httpGETRequest(status_endpoint).toInt();
  Serial.print("RESPONSE: ");
  Serial.println(val);
  if (val == 0) {
    digitalWrite(DEVICE_OUT, LOW);
  }
  else {
    digitalWrite(DEVICE_OUT, HIGH);
  }
  
  delay(1000);
}
