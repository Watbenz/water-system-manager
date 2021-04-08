#ifndef EASY_CLIENT_H
#define EASY_CLIENT_H

#include ".\..\Constant\Constant.h"
#include ".\..\EasyWifi\EasyWifi.h"
#include "ESPAsyncWebServer.h"
#include "HTTPClient.h"
#include <Arduino.h>

String httpPOSTRequest(const char *endpoint, Stirng reqData)
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

String httpGETRequest(const char *endpoint)
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


#endif
