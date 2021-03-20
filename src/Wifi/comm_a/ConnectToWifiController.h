#ifndef CONNECT_TO_WIFI_CONTROLLER_H
#define CONNECT_TO_WIFI_CONTROLLER_H

#include "ESPAsyncWebServer.h"

class ConnectToWifiController
{
private:
    // Create AsyncWebServer object on port 80
    AsyncWebServer server = AsyncWebServer(80);
    void initAP();
    void initSTA();
    void initAPI();
    void waitingWiFi();
    void getNofityData();

public:
    ConnectToWifiController();
    char* getWord();
    void initStaAp();
};

#endif
