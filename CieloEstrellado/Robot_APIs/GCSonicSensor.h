#ifndef __GCSonicSensor__
#define __GCSonicSensor__

#include "PinNames.h"
#include "DigitalInOut.h"

class GCSonicSensor {
    static const int timeout;
    static const int interval;
    mbed::DigitalInOut pin;
    unsigned long closeToWall;
    unsigned long farFromWall;
    
public:
    GCSonicSensor(PinName pin, unsigned long closeToWall);
    GCSonicSensor(PinName pin, unsigned long closeToWall, unsigned long farFromWall);
    bool isClose();
    bool isFar();
    unsigned long getValue();
    unsigned long value = 0;
};

#endif
