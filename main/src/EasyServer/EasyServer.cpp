#include "EasyServer.h"
#include "ESPAsyncWebServer.h"
#include ".\..\Constant\Constant.h"
#include ".\..\EasyWifi\EasyWifi.h"
#include ".\..\DeviceController\DeviceController.h"
#include <Arduino.h>

void EasyServer::init()
{
    server.begin();
    getNofityData();
    sendingClose();
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

// GET: http://192.168.4.1/off/1
void EasyServer::sendingClose()
{
    server.on(
        "/off/1",
        HTTP_GET,
        [&](AsyncWebServerRequest *request) {
            emergencyClose = true;
            digitalWrite(DEVICE_OUT, LOW);
            device[1] = false;
            request->send_P(RESPONSE_OK, TEXT, "TRUNED OFF DEVICE");
        });
}
