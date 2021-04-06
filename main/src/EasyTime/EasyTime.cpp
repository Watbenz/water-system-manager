#include "EasyTime.h"
#include ".\..\Constant\Constant.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>

void EasyTime::init()
{
    timeClient.begin();
    timeClient.setTimeOffset(GMT);
}

String EasyTime::getCurrentDateTime()
{
    while (!timeClient.update())
    {
        timeClient.forceUpdate();
    }

    return timeClient.getFormattedDate();
}

String EasyTime::getCurrentDate()
{
    String formattedDate = getCurrentDateTime();
    int splitT = formattedDate.indexOf("T");
    return formattedDate.substring(0, splitT);
}

String EasyTime::getCurrentTime()
{
    String formattedDate = getCurrentDateTime();
    int splitT = formattedDate.indexOf("T");
    return formattedDate.substring(splitT + 1, formattedDate.length() - 2);
}

String EasyTime::getHourAndMinutes() {
    String formattedDate = getCurrentTime();
    int split = formattedDate.lastIndexOf(":");
    return formattedDate.substring(0, split);
}
