#ifndef EASY_FIREBASE_H
#define EASY_FIREBASE_H

#include <FirebaseESP32.h>
#include <Arduino.h>

class EasyFirebase
{
private:
    FirebaseData fbdo;
    FirebaseJson json;
    void printError();
    void printSuccess();
    void printJson();
    void printArray();
    void printBlob();
    void printFile();

public:
    void init();
    void printResult();
    double readDouble(String path);
    void writeDouble(String path, double data);
    int readInt(String path);
    void writeInt(String path, int data);
    String readString(String path);
    void writeString(String path, String data);
};

#endif