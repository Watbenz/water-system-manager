#include "ConnectToWifiController.h"
#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include "Constant.h"

ConnectToWifiController::ConnectToWifiController()
{
    WiFi.mode(WIFI_AP_STA);
}

char* ConnectToWifiController::getWord()
{
    return "This is a testing word";
}

void ConnectToWifiController::initStaAp()
{
    initSTA();
    initAP();
    initAPI();
    server.begin();
}

void ConnectToWifiController::initAP()
{
    WiFi.softAP(SSID_AP, PASSWORD_AP);
    Serial.print("ESP32 IP on the WiFi network: ");
    Serial.println(WiFi.localIP());
}

void ConnectToWifiController::initSTA()
{
    WiFi.begin(SSID, PASSWORD);
    waitingWiFi();
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}

void ConnectToWifiController::initAPI()
{
    getNofityData();
}

void ConnectToWifiController::waitingWiFi()
{
    Serial.print("Connecting to WiFi..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
}

// GET: http://192.168.4.1/notify
void ConnectToWifiController::getNofityData()
{
    server.on(
        "/notify",
        HTTP_GET,
        [&](AsyncWebServerRequest *request) {
            request->send_P(RESPONSE_OK, TEXT, getWord());
        });
}
