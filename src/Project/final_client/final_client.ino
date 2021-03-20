#include "BluetoothSerial.h"
#include <WiFi.h>
#include <iSYNC.h>

#define LED 2
#define iSYNC_USERNAME "watbenz"
#define iSYNC_AUTH "6047312e62c47f64b13fb5ad"
#define iSYNC_KEY "6047319862c47f64b13fbe3e"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

WiFiClient client;
iSYNC iSYNC(client);
BluetoothSerial SerialBT;
int req;

String ssid = "Wachirawit_2.4G";
String pass = "3422273580";

String charArrayToString(byte* payload, unsigned int length) {
  String out = "";
  for (int i = 0; i < length; i++) out += (char) payload[i];
  return out;
}

void callback(char* topic, byte* payload, unsigned int length) {
  String cmd = charArrayToString(payload, length);

  if (cmd.startsWith("LINE:")) cmd = cmd.substring(5);

  Serial.print("command from line: ");
  Serial.println(cmd);

  if (cmd.equals("เปิดไฟ")) {
    digitalWrite(LED, HIGH);
    iSYNC.mqPub(iSYNC_KEY, "ไฟได้เปิดขึ้นแล้ว");  //Publish
  }
  else if (cmd.equals("ปิดไฟ")) {
    digitalWrite(LED, LOW);
    iSYNC.mqPub(iSYNC_KEY, "ไฟปิดลงแล้ว");  //Publish
  }
}

void connectMQTT() {
  Serial.println("Connecting MQTT...");
  while (!iSYNC.mqConnect()) {
    Serial.println("Reconnect MQTT...");
    delay(3000);
  }
  Serial.println("Connected MQTT...");
  //  iSYNC.mqSubProject(); //subscribe all key in your project
  iSYNC.mqSub(iSYNC_KEY); //subscribe key
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  SerialBT.begin("watbenz_client"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  Serial.println(iSYNC.getVersion());
  iSYNC.begin(ssid, pass);
  iSYNC.mqInit(iSYNC_USERNAME, iSYNC_AUTH);
  iSYNC.MQTT->setCallback(callback);
  connectMQTT();
}

long last = 0;
void loop() {
  if (!iSYNC.mqConnected())connectMQTT();
  iSYNC.mqLoop();

  if (SerialBT.available()) {
    req = SerialBT.read();
    Serial.println(req);
    if (req == 1) {
      digitalWrite(LED, HIGH);
    }
    else {
      digitalWrite(LED, LOW);
    }
  }
  delay(100);
}
