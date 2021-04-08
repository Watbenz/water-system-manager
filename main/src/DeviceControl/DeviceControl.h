#ifndef DEVICE_CONTROL_H
#define DEVICE_CONTROL_H

#include ".\..\Constant\Constant.h"
#include <Arduino.h>

void initDevice() {
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    pinMode(WATER_SENSOR, INPUT);
}

/*  s = v * t
 *  v = 346 m/s (speed of sound) = 34600 cm/s
 *  t = time when ultrasonic wave back to echo (µs = 10^-6 s)
 *  divided by 2 it mean found object and reflexed back
 */
int readDistance()
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

int readWaterSensor() {
    return analogRead(WATER_SENSOR);
}

#endif