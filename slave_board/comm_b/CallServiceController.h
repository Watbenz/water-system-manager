#ifndef CALL_SERVICE_CONTROLLER_H
#define CALL_SERVICE_CONTROLLER_H

#include "Arduino.h"

class CallServiceController
{
private:
    void waitingWiFi();

public:
    CallServiceController();
    void initSTA();
    String httpGETRequest(const char* path);
};

#endif
