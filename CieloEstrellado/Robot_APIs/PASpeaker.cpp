#include "PASpeaker.h"

PASpeaker::PASpeaker(PinName pin) : pwm(pin)
{
}

void PASpeaker::callback()
{
    pwm = 0;
}

void PASpeaker::play(uint32_t frequency, float level, uint32_t duration)
{
    uint32_t period = 1000000 / frequency;
    pwm.period_us(period);
    pwm = level;
    timeout.attach_us(this, &PASpeaker::callback, duration * 1000);
}
