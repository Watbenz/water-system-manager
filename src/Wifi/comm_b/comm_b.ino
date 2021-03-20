#include <WiFi.h>
#include <HTTPClient.h>
#include "CallServiceController.h"
#include "Constant.h"

CallServiceController controller = CallServiceController();
const unsigned int interval = 5000;
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

  if (currentMills - previousMillis >= interval)
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
