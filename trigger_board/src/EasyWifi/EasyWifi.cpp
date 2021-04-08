#include "EasyWifi.h"
#include "WiFi.h"
#include ".\..\Constant\Constant.h"

void EasyWifi::initWifi()
{
    WiFi.mode(WIFI_STA);

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