#include "BluetoothSerial.h"
#include <set>
#include "command.h"
#include <string>

int enum_command(const string str) {
    command.find();
}

void writing(const string dir)
{
    switch (dir)
    {
    case CLOSE:
        Serial.println("This is CLOSE");
        break;
    case OPEN:
        Serial.println("This is OPEN");
        break;
    default:
        Serial.println("This is INVALID " + dir);
        break;
    }
}
