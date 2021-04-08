#ifndef CALCULATE_FIREBASE_H
#define CALCULATE_FIREBASE_H

#include ".\..\EasyFirebase\EasyFirebase.h"
#include ".\..\EasyTime\EasyTime.h"
#include ".\..\DeviceController\DeviceController.h"
#include ".\..\Util\Util.h"
#include "FirebaseESP32.h"
#include <Arduino.h>

void writeDataRoutine(EasyFirebase &firebase, EasyTime &easyTime, DeviceController &deviceController)
{
       int distance = deviceController.readDistance();
       double percent = getTankRemainingPercent(distance);

    String splitted[5];
    splitPath(easyTime.getTimePath(), splitted);

    String hour = String(splitted[3].toInt());
    String min = String(splitted[4].toInt());

    firebase.writeInt("root/data/" + hour + "/" + min, percent);

    if (!firebase.hasInt("root/cal/" + hour + "/sum")) {
        firebase.writeInt("root/cal/" + hour + "/sum", percent);
    }
    else {
        int sum = firebase.readInt("root/cal/" + hour + "/sum");
        firebase.writeInt("root/cal/" + hour + "/sum", sum + percent);
    }

    if (!firebase.hasInt("root/cal/" + hour + "/n")) {
        firebase.writeInt("root/cal/" + hour + "/n", 1);
    }
    else {
        int n = firebase.readInt("root/cal/" + hour + "/n");
        firebase.writeInt("root/cal/" + hour + "/n", ++n);
    }
}

void registerFirebase(EasyFirebase &firebase, EasyTime &easyTime) {
    firebase.writeString("root/regis/session", easyTime.getTimePath());
}

double getStat(EasyFirebase &firebase) {
    String splitted[5];
    String time = firebase.readString("root/regis/session");
    splitPath(time, splitted);

    int hour = splitted[3].toInt();
    int sum = firebase.readInt("root/cal/" + String(hour) + "/sum");
    int n = firebase.readInt("root/cal/" + String(hour) + "/n");

    return double(sum)/double(n);
}

#endif