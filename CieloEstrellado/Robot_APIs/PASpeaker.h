#ifndef __Speaker__
#define __Speaker__

#include <stdint.h>
#include "PinNames.h"
#include "PwmOut.h"
#include "Timeout.h"
#include "RtosTimer.h"
#include "MemoryPool.h"

class PASpeaker {
    mbed::PwmOut pwm;
//    mbed::Timeout timeout;
    int8_t buf[sizeof(rtos::RtosTimer)];
    rtos::RtosTimer *timer;
    static void callback(const void *arg);
    
public:
    PASpeaker(PinName pin);
    void init();
    void play(uint32_t frequency, float level, uint32_t duration);
    void off();
};

#endif
