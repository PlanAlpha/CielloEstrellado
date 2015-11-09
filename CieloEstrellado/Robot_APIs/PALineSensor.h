#ifndef __PALineSensor__
#define __PALineSensor__

#include "PinNames.h"
#include "AnalogIn.h"

class PALineSensor {
    mbed::AnalogIn pin;
    const uint16_t blackValue;
    
public:
    PALineSensor(PinName pin, uint16_t blackValue);
    bool isBlack() {
        return pin.read_u16() <= blackValue;
    }
    operator bool () {
        return isBlack();
    }
    uint16_t readRawValue() {
        return pin.read_u16();
    }
    float readFloatValue() {
        return pin.read();
    }
};

#endif
