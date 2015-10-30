#ifndef __PALineSensor__
#define __PALineSensor__

#include "PinNames.h"
#include "AnalogIn.h"

class PALineSensor {
    mbed::AnalogIn pin;
    const float blackValue;
    
public:
    PALineSensor(PinName pin, float blackValue);
    bool isBlack() {
        return pin <= blackValue;
    }
    operator bool () {
        return isBlack();
    }
    float readRawValue() {
        return pin;
    }
};

#endif
