#ifndef __PAPIDController__
#define __PAPIDController__

#include <stdint.h>
#include <limits>
#include "Timer.h"

class PAPIDController {
    const float Kp;
    const float Ki;
    const float Kd;
    float integrationValue = 0;
    float integrationLimit;
    uint16_t lastTime = 0;
    float lastError = 0;
    mbed::Timer timer;
    
public:
    PAPIDController(float Kp, float Ki, float Kd, float integrationLimit = std::numeric_limits<float>::max());
    float next(float error);
    void resetIntegrationValue() {
        integrationValue = 0;
    }
    void initialize();
};

#endif
