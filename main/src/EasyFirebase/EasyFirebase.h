#ifndef EASY_FIREBASE_H
#define EASY_FIREBASE_H

#include <FirebaseESP32.h>
#include <Arduino.h>

class EasyFirebase
{
private:
    FirebaseData fbdo;
    void printError();
    void printSuccess();
    void printJson();
    void printArray();
    void printBlob();
    void printFile();

public:
    void init();
    void printResult();
    double readDouble(const String &path);
    bool hasDouble(const String &path);
    void writeDouble(const String &path, double data);
    int readInt(const String &path);
    bool hasInt(const String &path);
    void writeInt(const String &path, int data);
    FirebaseJson readJson(const String &path);
    bool hasJson(const String &path);
    void writeJson(const String &path, FirebaseJson data);
    String readString(const String &path);
    bool hasString(const String &path);
    void writeString(const String &path, const String &data);
    void deleteNode(const String &path);
    void clearAllNodeExcept(const String &path, int *excepts);
};

#endif