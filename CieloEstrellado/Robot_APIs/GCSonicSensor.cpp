#include "GCSonicSensor.h"
#include <limits>
#include "Timer.h"
#include "wait_api.h"

const int GCSonicSensor::timeout  = 10000;
const int GCSonicSensor::interval = 15;

GCSonicSensor::GCSonicSensor(PinName _pin, unsigned long _closeToWall)
: pin(_pin), closeToWall(_closeToWall), farFromWall(std::numeric_limits<typeof(farFromWall)>::max())
{
}

GCSonicSensor::GCSonicSensor(PinName _pin, unsigned long _closeToWall, unsigned long _farFromWall)
: pin(_pin), closeToWall(_closeToWall), farFromWall(_farFromWall)
{
}

bool GCSonicSensor::isClose()
{
    return value <= closeToWall;
}

bool GCSonicSensor::isFar()
{
    return value >= farFromWall;
}

unsigned long GCSonicSensor::getValue()
{
    pin.output();
    pin.write(1);
    wait_us(interval);
    pin.write(0);
    pin.input();
    mbed::Timer timer;
    timer.start();
    while (pin) ;
    return value = timer.read_us() * 17 / 1000;
}
