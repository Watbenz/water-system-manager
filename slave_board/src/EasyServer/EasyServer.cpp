#include "EasyServer.h"
#include "WiFi.h"
#include ".\..\Constant\Constant.h"

void EasyServer::init()
{
    WiFi.mode(WIFI_AP_STA);
    initSTA();
    initAP();
    initAPI();
    server.begin();
}

void EasyServer::initSTA()
{
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}

void EasyServer::initAP()
{
    WiFi.softAP(SSID_AP, PASSWORD_AP);
    Serial.print("ESP32 IP on the WiFi network: ");
    Serial.println(WiFi.localIP());
}

void EasyServer::initAPI()
{
    getNofityData();
}

// GET: http://192.168.4.1/notify
void EasyServer::getNofityData()
{
    server.on(
        "/notify",
        HTTP_GET,
        [&](AsyncWebServerRequest *request) {
            request->send_P(RESPONSE_OK, TEXT, "This is a testing word");
        });
}
