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
    void printJson();
    void printArray();
    void printBlob();
    void printFile();

public:
    void initWifi();
    void initFirebase();
    void printResult();
    double readDouble(const char *path);
    void writeDouble(const char *path, double data);
    int readInt(const char *path);
    void writeInt(const char *path, int data);
};

#endif