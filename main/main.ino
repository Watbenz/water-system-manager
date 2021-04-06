#include "src\EasyWifi\EasyWifi.h"
#include "src\EasyFirebase\EasyFirebase.h"
#include "src\EasyTime\EasyTime.h"
#include "src\UltrasonicSensor\UltrasonicSensor.h"
#include "src\Util\Util.h"
#include "src\CalculateFirebase\CalculateFirebase.h"
#include "src\Constant\Constant.h"
#include "src\EasyServer\EasyServer.h"
#include <iSYNC.h>
#include <WiFi.h>

#define INTERVAL 60000

EasyWifi wifi;
EasyFirebase firebase;
EasyTime easyTime;
EasyServer server;
UltrasonicSensor ultrasonicSensor;

WiFiClient client;
iSYNC iSYNC(client);

long previousMillis = 0;

void callback(char *topic, byte *payload, unsigned int length)
{
  String cmd = charArrayToString(payload, length);

  if (cmd.startsWith("LINE:"))
    cmd = cmd.substring(5);

  Serial.print("command from line: ");
  Serial.println(cmd);

  if (cmd.equals("เปิดไฟ"))
  {
    iSYNC.mqPub(iSYNC_KEY, "ไฟได้เปิดขึ้นแล้ว"); //Publish
  }
  else if (cmd.equals("ระดับน้ำ"))
  {
    int d = ultrasonicSensor.readDistance();
    double remain = getTankRemainingPercent(d, 20);
    String out = "สถิติระดับน้ำใน 1 ชั่วโมงคือ " + String(remain); 
    iSYNC.mqPub(iSYNC_KEY, out);
  }
  else if (cmd.equals("สถิติ"))
  {
    double val = getStat(firebase);
    String out = "สถิติระดับน้ำใน 1 ชั่วโมงคือ " 
    iSYNC.mqPub(iSYNC_KEY, "สถิติระดับน้ำใน 1 ชั่วโมงคือ");
  }
}


void initMQTT()
{
  Serial.println("Connecting MQTT...");
  while (!iSYNC.mqConnect())
  {
    Serial.println("Reconnect MQTT...");
    delay(3000);
  }
  Serial.println("Connected MQTT...");
  iSYNC.mqSub(iSYNC_KEY); //subscribe key
}

void initISYNC() {
  iSYNC.begin(SSID_WIFI, PASSWORD_WIFI);
  iSYNC.mqInit(iSYNC_USERNAME, iSYNC_AUTH);
  iSYNC.MQTT->setCallback(callback);
  initMQTT();
}

void setup() {
  Serial.begin(115200);
  wifi.init();
  server.init();
  firebase.init();
  easyTime.init();
  initISYNC();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL) {
    registerFirebase(firebase, easyTime);
    writeDataRoutine(firebase, easyTime, ultrasonicSensor);
    previousMillis = currentMillis;
  }

  if (!iSYNC.mqConnected())
    initMQTT();
  iSYNC.mqLoop();
}
