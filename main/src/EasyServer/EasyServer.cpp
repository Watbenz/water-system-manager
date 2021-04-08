#include "EasyServer.h"
#include "ESPAsyncWebServer.h"
#include ".\..\Constant\Constant.h"
#include ".\..\EasyWifi\EasyWifi.h"

void EasyServer::init()
{
    server.begin();
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

// GET: http://192.168.4.1/notify
void EasyServer::sendingOpen(int pos)
{
    server.on(
        "/notify",
        HTTP_POST,
        [&](AsyncWebServerRequest *request) {
            request->send_P(RESPONSE_OK, TEXT, "This is a testing word");
        });
}
