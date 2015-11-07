#ifndef __PAL3G4200D__
#define __PAL3G4200D__

#include "../Core_APIs/I2CDevice.h"
#include "PAMovingAverage.h"

class PAL3G4200D {
    static constexpr uint8_t i2cAddress = 105;
    static constexpr uint8_t WHO_AM_I = 15;
    static constexpr uint8_t CTRL_REG1 = 32;
    static constexpr uint8_t CTRL_REG2 = 33;
    static constexpr uint8_t CTRL_REG3 = 34;
    static constexpr uint8_t CTRL_REG4 = 35;
    static constexpr uint8_t OUT_X_L = 40;
    static constexpr uint8_t OUT_Y_L = 42;
    static constexpr uint8_t OUT_Z_L = 44;
    I2CDevice device;
    PAMovingAverage<float, 10> xAverage;
    PAMovingAverage<float, 10> yAverage;
    PAMovingAverage<float, 50> zAverage;
    union Data {
        char buf[2];
        int16_t value;
    };
    
public:
    PAL3G4200D(I2CDevice::Pin pin);
    float readX();
    float readY();
    float readZ();
};

#endif
