#include "UltrasonicSensor.h"
#include ".\..\Constant\Constant.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(int cm)
{
    this->tankHeight = cm;
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

void UltrasonicSensor::setTankHeight(int cm)
{
    this->tankHeight = cm;
}

/*  s = v * t
 *  v = 346 m/s (speed of sound) = 34600 cm/s
 *  t = time when ultrasonic wave back to echo (µs = 10^-6 s)
 *  divided by 2 it mean found object and reflexed back
 */
int UltrasonicSensor::readDistance()
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

double UltrasonicSensor::getTankLeftPercent()
{
    return (readDistance() / tankHeight) * 100.0;
}
