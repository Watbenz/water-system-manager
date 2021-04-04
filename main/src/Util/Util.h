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

#endif