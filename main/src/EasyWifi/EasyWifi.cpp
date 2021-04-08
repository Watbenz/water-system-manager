#include "EasyWifi.h"
#include "WiFi.h"
#include ".\..\Constant\Constant.h"

void EasyWifi::initWifi()
{
    WiFi.begin(SSID_WIFI, PASSWORD_WIFI);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();

    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

void EasyWifi::initSTAAP()
{
    WiFi.mode(WIFI_AP_STA);
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    WiFi.softAP(SSID_AP, PASSWORD_AP);
    Serial.print("ESP32 IP on the WiFi network: ");
    Serial.println(WiFi.localIP());
}