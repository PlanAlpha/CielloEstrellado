#ifndef __I2CDevice__
#define __I2CDevice__

#include <stdint.h>
#include "I2C.h"
#include "MemoryPool.h"

class I2CDevice {
    int address;
	mbed::I2C *i2c;
	rtos::MemoryPool<mbed::I2C, 1> pool;
	
public:
    enum class Pin {
        I2C0,
        I2C1,
    };
    I2CDevice(Pin dev, int address);
    void write(char reg, char data);
    void write(char reg, const char *datas, int length);
    uint8_t read(char reg);
    void read(char reg, char *buf, int length);
};

#endif
