#ifndef EASY_TIME_H
#define EASY_TIME_H

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>

class EasyTime
{
private:
    WiFiUDP ntpUDP = WiFiUDP();
    NTPClient timeClient = NTPClient(ntpUDP);
    String getCurrentDateTime();

public:
    void initTime();
    String getCurrentDate();
    String getCurrentTime();
};

#endif