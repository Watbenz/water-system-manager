
#include "src\EasyWifi\EasyWifi.h"
#include "src\EasyFirebase\EasyFirebase.h"
#include "src\EasyTime\EasyTime.h"
#include "src\UltrasonicSensor\UltrasonicSensor.h"
#include "src\Util\Util.h"
#include "src\Constant\Constant.h"
#include "src\EasyServer\EasyServer.h"
#include <iSYNC.h>
#include <WiFi.h>


EasyWifi wifi;
EasyFirebase firebase;
EasyTime easyTime;
EasyServer server;
UltrasonicSensor ultrasonicSensor;

WiFiClient client;
iSYNC iSYNC(client);

const long interval = 2000;
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
  else if (cmd.equals("ปิดไฟ"))
  {
    iSYNC.mqPub(iSYNC_KEY, "ไฟปิดลงแล้ว"); //Publish
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
  if (currentMillis - previousMillis >= interval) {
    //    String path = "root/" + easyTime.getCurrentDate() + "/" + easyTime.getCurrentTime();
    //    String path = "root/hour/";
    int head;

    if (firebase.hasInt("root/hour/head")) {
      head = firebase.readInt("root/hour/head");
    }
    else {
      firebase.writeInt("root/hour/head", 0);
      head = 0;
    }

//    int distance = ultrasonicSensor.readDistance();
//    double percent = getTankRemainingPercent(distance, 20)    cent = random(0,101);
    double percent = random(0,101);

    firebase.writeDouble("root/hour/" + String(head), percent);

    head = ((head+1)>=60) ? 0 : head+1;
    firebase.writeInt("root/hour/head", head);
    
    previousMillis = currentMillis;
  }

  if (!iSYNC.mqConnected())
    initMQTT();
  iSYNC.mqLoop();
}
