#ifndef EASY_SERVER_H
#define EASY_SERVER_H

#include "ESPAsyncWebServer.h"

class EasyServer
{
private:
    AsyncWebServer server = AsyncWebServer(80);  // Create AsyncWebServer object on port 80
    void initAPI();
    void getNofityData();
public:
    void init();
    void sendingOpen(int pos);
};

#endif