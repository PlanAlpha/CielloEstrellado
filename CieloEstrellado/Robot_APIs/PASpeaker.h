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
    rtos::RtosTimer *timer;
    static void callback(const void *arg);
	rtos::MemoryPool<rtos::RtosTimer, 1> pool;
    
public:
    PASpeaker(PinName pin);
    void init();
    void play(uint32_t frequency, float level, uint32_t duration);
    void off();
};

#endif
