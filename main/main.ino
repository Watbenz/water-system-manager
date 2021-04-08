#include "src\EasyWifi\EasyWifi.h"
#include "src\EasyFirebase\EasyFirebase.h"
#include "src\EasyTime\EasyTime.h"
#include "src\DeviceController\DeviceController.h"
#include "src\Util\Util.h"
#include "src\CalculateFirebase\CalculateFirebase.h"
#include "src\Constant\Constant.h"
#include "src\EasyClient\EasyClient.h"
#include <iSYNC.h>
#include <WiFi.h>

#define INTERVAL 60000

EasyFirebase firebase;
EasyTime easyTime;
AsyncWebServer server(80);
EasyWifi wifi;
DeviceController deviceController;
unsigned int tankHeigth = 20;

WiFiClient client;
iSYNC iSYNC(client);

long previousMillis = 0;
bool askForClose = false;
bool askForOpen = false;

void callback(char *topic, byte *payload, unsigned int length)
{
  String cmd = charArrayToString(payload, length);

  if (cmd.startsWith("LINE:"))
  {
    cmd = cmd.substring(5);
  }

  Serial.print("command from line: ");
  Serial.println(cmd);

  if (askForClose)
  {
    int pos = cmd.toInt();
    if ((pos > 0) && (pos <= NUMBER_OF_DEVICE))
    {
      iSYNC.mqPub(iSYNC_KEY, "ก๊อกน้ำช่องที่ " + String(pos) + " ปิดแล้ว");

      switch (pos)
      {
        case 1:
          deviceController.turnOffDevice();
          break;
        case 2:
          httpGETRequest("http://192.168.4.1/off/2");
          break;
        default:
          break;
      }
      device[pos] = false;
      askForOpen = false;
      askForClose = false;
    }
  }
  else if (askForOpen)
  {
    int pos = cmd.toInt();
    if ((pos > 0) && (pos <= NUMBER_OF_DEVICE))
    {
      iSYNC.mqPub(iSYNC_KEY, "ก๊อกน้ำช่องที่ " + String(pos) + " เปิดแล้ว");

      switch (pos)
      {
        case 1:
          deviceController.turnOnDevice();
          break;
        case 2:
          httpGETRequest("http://192.168.4.1/on/2");
          break;
        default:
          break;
      }
      device[pos] = true;
      askForOpen = false;
      askForClose = false;
    }
  }

  if (cmd.equals("เปิดน้ำ"))
  {
    askForOpen = true;
    askForClose = false;
    String out = "";
    for (int i = 1; i <= NUMBER_OF_DEVICE; i++)
    {
      out += "น้ำตำแหน่งที่ " + String(i) + (device[i] ? ": เปิดอยู่" : ": ปิดอยู่") + "\n";
    }
    out += "กรุณาพิมพ์ตัวเลขตำแหน่งน้ำเพื่อสั่งเปิด";
    iSYNC.mqPub(iSYNC_KEY, out);
  }
  else if (cmd.equals("ปิดน้ำ"))
  {
    askForOpen = false;
    askForClose = true;
    String out = "";
    for (int i = 1; i <= NUMBER_OF_DEVICE; i++)
    {
      out += "น้ำตำแหน่งที่ " + String(i) + (device[i] ? ": เปิดอยู่" : ": ปิดอยู่") + "\n";
    }
    out += "กรุณาพิมพ์ตัวเลขตำแหน่งน้ำเพื่อสั่งปิด";
    iSYNC.mqPub(iSYNC_KEY, out);
  }
  else if (cmd.equals("ระดับน้ำ"))
  {
    askForOpen = false;
    askForClose = false;
    int d = deviceController.readDistance();
    double remain = getTankRemainingPercent(d);
    iSYNC.mqPub(iSYNC_KEY, "ระดับน้ำปัจจุบันมีน้ำอยู่ " + String(remain) + "%");
  }
  else if (cmd.equals("สถิติ"))
  {
    askForOpen = false;
    askForClose = false;

    String splitted[5];
    splitPath(easyTime.getTimePath(), splitted);

    double val = getStat(firebase);
    iSYNC.mqPub(iSYNC_KEY, "สถิติระดับน้ำตั้งแต่ " + splitted[3] + ":00 ถึง " + splitted[3] + ":" + splitted[4] + " คือ " + String(val) + "%");
  }
  else if (cmd.equals("ตำแหน่ง"))
  {
    askForOpen = false;
    askForClose = false;
    String out = "";
    for (int i = 1; i <= NUMBER_OF_DEVICE; i++)
    {
      out += "น้ำตำแหน่งที่ " + String(i) + (device[i] ? ": เปิดอยู่" : ": ปิดอยู่") + "\n";
    }
    iSYNC.mqPub(iSYNC_KEY, out);
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

void initISYNC()
{
  iSYNC.begin(SSID_WIFI, PASSWORD_WIFI);
  iSYNC.mqInit(iSYNC_USERNAME, iSYNC_AUTH);
  iSYNC.MQTT->setCallback(callback);
  initMQTT();
}

void initAPI() {
  server.begin();
  server.on(
    "/off/1",
    HTTP_GET,
  [&](AsyncWebServerRequest * request) {
    emergencyClose = true;
    digitalWrite(DEVICE_OUT, LOW);
    device[1] = false;
    iSYNC.mqPub(iSYNC_KEY, "ระบบน้ำช่องที่ 1 ปิดฉุกเฉิน");
    request->send_P(RESPONSE_OK, TEXT, "TRUNED OFF DEVICE");
  });
}

void setup()
{
  Serial.begin(115200);
  initISYNC();
  wifi.initSTAAP();
  initAPI();
  firebase.init();
  easyTime.init();
  deviceController.init();
}
//
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL) {
    registerFirebase(firebase, easyTime);
    writeDataRoutine(firebase, easyTime, deviceController);
    previousMillis = currentMillis;
  }

  if (!iSYNC.mqConnected())
    initMQTT();
  iSYNC.mqLoop();
}
