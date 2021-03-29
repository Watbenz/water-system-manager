#ifndef EASY_WIFI_H
#define EASY_WIFI_H

#include <FirebaseESP32.h>
#include <Arduino.h>

class EasyWifi
{
private:
    enum FirebaseType
    {
        INT,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STR,
        JSON,
        ARRAY,
        BLOB,
        FILE,
        ELSE
    };
    FirebaseData fbdo;
    FirebaseJson json;
    void connecting();
    void printError();
    void printSuccess();
    void printJson();
    void printArray(); 
    void printBlob(); 
    void printFile(); 
    int findType(String str);
public:
    void initWifi();
    void initFirebase();
    void printResult();
    void writeData(const char *path, double data);
};

#endif