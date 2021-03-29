#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "5rOa0Lho0aXWUUPSH_KZujAad0eLkdoO";
char ssid[] = "watbenz";
char pass[] = "watbenzzzzzz";

void setup()
{
  Serial.begin(115200);+
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
