#ifndef __I2CDevice__
#define __I2CDevice__

#include <stdint.h>
#include "I2C.h"

class I2CDevice {
    uint8_t address;
    union I2CUnion {
        mbed::I2C object;
        uint8_t buffer[sizeof(mbed::I2C)];
        I2CUnion() {}
    } i2cObject;
    
public:
    enum class Pin {
        I2C0,
        I2C1,
    };
    I2CDevice(Pin dev, uint8_t address);
    void write(uint8_t reg, uint8_t data);
    void write(uint8_t reg, const uint8_t *datas, uint16_t length);
    uint8_t read(uint8_t reg);
    void read(uint8_t reg, const uint8_t *buf, uint16_t length);
};

#endif
