#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

class UltrasonicSensor
{
private:
    int tankHeight;
public:
    UltrasonicSensor(int cm);
    void setTankHeight(int cm);
    int readDistance();
    double getTankLeftPercent();
};

#endif