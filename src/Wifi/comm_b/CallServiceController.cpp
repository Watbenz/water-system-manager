#include "CallServiceController.h"
#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include "Constant.h"
#include "HTTPClient.h"

CallServiceController::CallServiceController() {
  WiFi.mode(WIFI_STA);
}

void CallServiceController::waitingWiFi()
{
    Serial.print("Connecting to WiFi..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
}

void CallServiceController::initSTA()
{
    WiFi.begin(SSID_AP, PASSWORD_AP);
    waitingWiFi();
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}

String CallServiceController::httpGETRequest(const char* endpoint) 
{
  HTTPClient http;
  http.begin(endpoint);

  int httpResponseCode = http.GET();

  String payload = "--";
  
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
