#include "GCMotor.h"
#include <limits>

GCMotor::GCMotor(PinName _digital, PinName _pwm) : digital(_digital, 0), pwm(_pwm)
{
    free();
}

void GCMotor::forward(float power)
{
    if (power >= 0) {
        digital = 0;
        pwm = power;
    } else {
        digital = 1;
        pwm = -power;
    }
}

void GCMotor::free()
{
    pwm = 0;
}
