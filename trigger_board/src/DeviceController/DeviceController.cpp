#include "DeviceController.h"
#include ".\..\Constant\Constant.h"
#include <Arduino.h>

void DeviceController::init()
{
    pinMode(WATER_SENSOR, INPUT);
}

int DeviceController::readWaterSensor()
{
    return analogRead(WATER_SENSOR);
}
