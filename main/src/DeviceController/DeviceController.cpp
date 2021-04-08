#include "DeviceController.h"
#include ".\..\Constant\Constant.h"
#include <Arduino.h>

void DeviceController::init()
{
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    pinMode(WATER_SENSOR, INPUT);

    pinMode(DEVICE_OUT, OUTPUT);
}

/*  s = v * t
 *  v = 346 m/s (speed of sound) = 34600 cm/s
 *  t = time when ultrasonic wave back to echo (µs = 10^-6 s)
 *  divided by 2 it mean found object and reflexed back
 */
int DeviceController::readDistance()
{
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);

    // Open Trig then close
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    long t = pulseIn(ECHO, HIGH);
    return 0.034 * t / 2;
}

int DeviceController::readWaterSensor()
{
    return analogRead(WATER_SENSOR);
}

void DeviceController::turnOnDevice()
{
    digitalWrite(DEVICE_OUT, HIGH);
    Serial.print("PIN: ");
    Serial.print(DEVICE_OUT);
    Serial.println(" has been opened");
}

void DeviceController::turnOffDevice()
{
    digitalWrite(DEVICE_OUT, LOW);
    Serial.print("PIN: ");
    Serial.print(DEVICE_OUT);
    Serial.println(" has been opened");
}