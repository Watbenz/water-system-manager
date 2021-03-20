#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "UlcMu24svAowyI_PvJ6q_TyPQ8sh0onX";
char ssid[] = "watbenz";
char pass[] = "watbenzzzzzz";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
