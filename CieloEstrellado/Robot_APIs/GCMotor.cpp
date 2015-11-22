#include "GCMotor.h"
#include <limits>

GCMotor::GCMotor(PinName _digital, PinName _pwm, bool _reverse) : digital(_digital, 0), pwm(_pwm), reverse(_reverse)
{
	pwm.period_us(1000);
    free();
}

void GCMotor::forward(float power)
{
    if (power >= 0) {
        digital = reverse;
        pwm = power;
    } else {
        digital = !reverse;
        pwm = -power;
    }
}

void GCMotor::free()
{
    pwm = 0;
}
