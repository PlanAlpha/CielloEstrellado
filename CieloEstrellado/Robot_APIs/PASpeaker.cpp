#include "PASpeaker.h"

void PASpeaker::callback(const void *arg)
{
    reinterpret_cast<PASpeaker *>(const_cast<void *>(arg))->off();
}

PASpeaker::PASpeaker(PinName pin) : pwm(pin), timer()
{
}

void PASpeaker::init()
{
	timer = new rtos::RtosTimer(&PASpeaker::callback, osTimerOnce, this);
}

void PASpeaker::play(uint32_t frequency, float level, uint32_t duration)
{
    uint32_t period = 1000000 / frequency;
    pwm.period_us(period);
    pwm = level;
    if (duration) {
        timer->start(duration);
    }
}

void PASpeaker::off()
{
    pwm = 0;
}
