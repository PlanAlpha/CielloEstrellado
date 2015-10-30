#ifndef __GCMotor__
#define __GCMotor__

#include "PinNames.h"
#include "DigitalOut.h"
#include "PwmOut.h"

class GCMotor {
    mbed::DigitalOut digital;
    mbed::PwmOut     pwm;
    
public:
    GCMotor(PinName digital, PinName pwm);
    void forward(float power);
    void __attribute__((always_inline)) forward(double power) {
        forward(static_cast<float>(power));
    }
    void free();
};

#endif
