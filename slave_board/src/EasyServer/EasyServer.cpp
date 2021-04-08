#include "EasyServer.h"
#include "WiFi.h"
#include ".\..\Constant\Constant.h"

void EasyServer::init()
{
    server.begin();
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
