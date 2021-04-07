#include ".\EasyClient\EasyClient.h"
#include ".\EasyServer\EasyServer.h"
#include ".\Constant\Constaint.h"

#define DEVICE_NUMBER 1
#define INTERVAL 1000

EasyClient client;
EasyServer server;
unsigned long previousMillis = 0;

const char* notifyEndpoint = "http://192.168.4.1/notify";

void setup()
{
  Serial.begin(115200);
  controller.initSTA();
}

void loop()
{
  unsigned long currentMills = millis();

  if (currentMills - previousMillis >= INTERVAL)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println(controller.httpGETRequest(notifyEndpoint));

      previousMillis = currentMills;
    }
    else
    {
      Serial.println("WiFi Disconnected");
      delay(500);
    }
  }
}
