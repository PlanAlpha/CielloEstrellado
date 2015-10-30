#ifndef __Speaker__
#define __Speaker__

#include <stdint.h>
#include "PinNames.h"
#include "PwmOut.h"
#include "Timeout.h"

class PASpeaker {
    mbed::PwmOut pwm;
    mbed::Timeout timeout;
    void callback();
    
public:
    PASpeaker(PinName pin);
    void play(uint32_t frequency, float level, uint32_t duration);
};

#endif
