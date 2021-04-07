#include "EasyClient.h"
#include "ESPAsyncWebServer.h"
#include ".\..\Constant\Constant.h"
#include ".\..\EasyWifi\EasyWifi.h"
#include "HTTPClient.h"
#include <Arduino.h>

void EasyClient::init()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_AP, PASSWORD_AP);
  waitingWiFi();
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

String EasyClient::httpPOSTRequest(const char *endpoint, Stirng reqData)
{
  HTTPClient http;
  http.begin(endpoint);

  int httpResponseCode = http.POST(reqData);
  String payload = "";

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}

String EasyClient::httpGETRequest(const char *endpoint)
{http.POST
  HTTPClient http;
  http.begin(endpoint);

  int httpResponseCode = http.GET();

  String payload = "";

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}
