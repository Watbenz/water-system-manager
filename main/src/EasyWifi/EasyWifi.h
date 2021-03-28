#ifndef EASY_WIFI_H
#define EASY_WIFI_H

#include <FirebaseESP32.h>

class EasyWifi
{
private:
    FirebaseData fbdo;
    FirebaseJson json;
    void connecting();
    void printError();
    void printSuccess();
public:
    void initWifi();
    void initFirebase();
    void printResult();
    void writeData(const char *path, double data);
};

#endif