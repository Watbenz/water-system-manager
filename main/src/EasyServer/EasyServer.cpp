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
        "/off",
        HTTP_GET,
        [&](AsyncWebServerRequest *request) {
            int n = request->params();
            for (int i = 0; i < n; i++)
            {
                AsyncWebParameter *p = request->getParam(i);
                DeviceController deviceController;
                if (p->name() == "pos")
                {
                    int data = p->value().toInt();

                    switch (data)
                    {
                    case -1:
                        emergencyClose = true;
                        deviceController.turnOffDevice();
                        request->send_P(RESPONSE_OK, TEXT, "TRUNED OFF DEVICE");
                        device[1] = false;
                        break;
                    default:
                        break;
                    }
                }
            }
        });
}

// GET: http://192.168.4.1/on/1
void EasyServer::sendingOpen()
{
    server.on(
        "/off/1",
        HTTP_GET,
        [&](AsyncWebServerRequest *request) {
            // int n = request->params();
            // for (int i = 0; i < n; i++)
            // {
            //     AsyncWebParameter *p = request->getParam(i);
            //     DeviceController deviceController;
            //     if (p->name() == "pos")
            //     {
            //         int data = p->value().toInt();

            //         switch (data)
            //         {
            //         case -1:
            //             emergencyClose = true;
            //             deviceController.turnOnDevice();
                        request->send_P(RESPONSE_OK, TEXT, "TRUNED ON DEVICE 1");
            //             device[1] = false;
            //             break;
            //         default:
            //             break;
            //         }
            //     }
            // }
        });
}
