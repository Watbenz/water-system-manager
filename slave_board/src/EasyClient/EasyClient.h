#ifndef EASY_CLIENT_H
#define EASY_CLIENT_H

#include <Arduino.h>

class EasyClient
{
private:
    void waitingWiFi();

public:
    EasyClient();
    void init();
    String httpGETRequest(const char* path);
    String httpPOSTRequest(const char* path, String reqData);
};

#endif
