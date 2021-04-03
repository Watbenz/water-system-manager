#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

class UltrasonicSensor
{
private:
    int tankHeight;
public:
    UltrasonicSensor();
    int readDistance();
};

#endif