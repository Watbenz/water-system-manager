#include "BluetoothSerial.h"
#define BUTTON 23

BluetoothSerial SerialBT;
uint8_t ESP32_B_BDA[6] = {0xF0, 0x08, 0xD1, 0xC5, 0xAE, 0x92};
bool connected;

void setup_device() {
  pinMode(BUTTON, INPUT);
}

void setup() {
  setup_device();
  Serial.begin(115200);
  SerialBT.begin("watbenz_server", true);
  Serial.println("The device started in master mode, make sure remote BT device is on!");

  connected = SerialBT.connect(ESP32_B_BDA);

  if (connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while (!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
    }
  }
  if (SerialBT.disconnect()) {
    Serial.println("Disconnected Succesfully!");
  }
  SerialBT.connect();
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
    SerialBT.write(1);
    Serial.println("Writing 1 into BLE");
  }
  else {
    SerialBT.write(0);
    Serial.println("Writing 0 into BLE");
  }
  delay(100);
}
