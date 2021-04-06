#ifndef CALCULATE_FIREBASE_H
#define CALCULATE_FIREBASE_H

#include ".\..\EasyFirebase\EasyFirebase.h"
#include ".\..\EasyTime\EasyTime.h"
#include ".\..\Util\Util.h"
#include "FirebaseESP32.h"
#include <Arduino.h>

void writeDataRoutine(EasyFirebase &firebase, EasyTime &easyTime)
{
    String current = easyTime.getHourAndMinutes();
    int hour = getSplitedHour(current).toInt();
    int min = getSplitedMinute(current).toInt();

    //    int distance = ultrasonicSensor.readDistance();
    //    double percent = getTankRemainingPercent(distance, 20)    cent = random(0,101);
    double percent = random(0, 101);
    String path = "root/hour/" + String(hour) + "/" + String(min);
    Serial.print("time: ");
    Serial.println(current);
    firebase.writeDouble(path, percent);
}

void clearAllInHourExcept(EasyFirebase &firebase, int *except, int length)
{
    Serial.println("deleting");
    // if (!firebase.hasJson("root/hour"))
    //     return;

    // FirebaseJsonData jsonData;
    FirebaseJson json = firebase.readJson("root/hour");
    Serial.println("read finished");

    // jsonData.getJSON(json);
    size_t end = json.iteratorBegin();
    int type;
    String key, value;

    for (size_t it = 0; it < end; it++)
    {
        json.iteratorGet(it, type, key, value);
        Serial.print("Type: ");
        Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
        if (type == FirebaseJson::JSON_OBJECT)
        {
            Serial.print(", Key: ");
            Serial.print(key);
            // if (!isContain(except, length, key.toInt()))
            // {
            //     Serial.print("deleting: ");
            //     Serial.print("root/hour/");
            //     Serial.println(key);
            //     firebase.deleteNode("root/hour/" + key);
            // }
        }
        Serial.print(", Value: ");
        Serial.println(value);
    }

    json.iteratorEnd();
}

#endif