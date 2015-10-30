#include "I2CDevice.h"

I2CDevice::I2CDevice(Pin devIndex, uint8_t _address) : address(_address)
{
    switch (devIndex) {
        case Pin::I2C0:
            i2cObject.object = mbed::I2C(MBED_I2C0);
            break;
            
        case Pin::I2C1:
            i2cObject.object = mbed::I2C(MBED_I2C1);
            break;
            
        default:
            MBED_ASSERT(0);
            break;
    }
}

void I2CDevice::write(uint8_t reg, uint8_t data)
{
    write(reg, &data, 1);
}

void I2CDevice::write(uint8_t reg, const uint8_t *datas, uint16_t length)
{
    uint8_t buf[length + 1];
    buf[0] = reg;
    memcpy(&buf[1], datas, length);
    i2cObject.object.write(address, reinterpret_cast<const char *>(buf), length + 1);
}

uint8_t I2CDevice::read(uint8_t reg)
{
    uint8_t buf[1];
    read(reg, buf, 1);
    return buf[0];
}

void I2CDevice::read(uint8_t reg, const uint8_t *datas, uint16_t length)
{
    uint8_t buf[length + 1];
    buf[0] = reg;
    memcpy(&buf[1], datas, length);
    i2cObject.object.read(address, reinterpret_cast<char *>(buf), length + 1);
}
