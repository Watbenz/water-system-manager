#include "ConnectToWifiController.h"

ConnectToWifiController controller = ConnectToWifiController();

void setup()
{
  Serial.begin(115200);
  controller.initStaAp();
}

void loop()
{
}
