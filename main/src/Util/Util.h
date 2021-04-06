#ifndef Util_H
#define Util_H

#include <Arduino.h>

double getTankRemainingPercent(int d, int tankHeight)
{
    if ((d <= 0) || (d >= tankHeight))
        return -1;
    return 100.0 - ((d / (double)tankHeight) * 100.0);
}

String charArrayToString(byte* payload, unsigned int length) {
  String out = "";
  for (int i = 0; i < length; i++) out += (char) payload[i];
  return out;
}

String getSplitedHour(const String &hourAndMin) {
    int split = hourAndMin.indexOf(":");
    return hourAndMin.substring(0, split);
}

String getSplitedMinute(const String &hourAndMin) {
    int split = hourAndMin.indexOf(":");
    return hourAndMin.substring(split+1, hourAndMin.length());
}

bool isContains(int x, int* arr, int length) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == x) return true;
    }
    return false;
}

void splitPath(const String &path, String out[5]) {
    out[0] = path.substring(0,4);
    out[1] = path.substring(5,7);
    out[2] = path.substring(8,10);
    out[3] = path.substring(11,13);
    out[4] = path.substring(14,16);
}

#endif