#ifndef DEVICE_CONTROL_H
#define DEVICE_CONTROL_H

class DeviceController
{
private:
public:
    void init();
    int readDistance();
    int readWaterSensor();
    void turnOnDevice();
    void turnOffDevice();
};

#endif