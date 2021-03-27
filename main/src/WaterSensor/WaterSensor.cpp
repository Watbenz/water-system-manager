#include "WaterSensor.h"
#include ".\..\Constant\Constant.h"
#include <Arduino.h>

WaterSensor::WaterSensor() {
    pinMode(WATER_SENSOR, INPUT);
}

int WaterSensor::getWaterValue() {
    return analogRead(WATER_SENSOR);
}