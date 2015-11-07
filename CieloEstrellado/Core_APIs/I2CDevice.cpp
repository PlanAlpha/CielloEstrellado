#include "I2CDevice.h"

I2CDevice::I2CDevice(Pin devIndex, int _address) : address(_address),
    i2c(devIndex == Pin::I2C0 ? mbed::I2C(MBED_I2C0) : mbed::I2C(MBED_I2C1))
{
    switch (devIndex) {
        case Pin::I2C0:
		case Pin::I2C1:
            break;
            
        default:
            MBED_ASSERT(0);
            break;
    }
}

void I2CDevice::write(char reg, char data)
{
    write(reg, &data, 1);
}

void I2CDevice::write(char reg, const char *datas, int length)
{
    char buf[length + 1];
    buf[0] = reg;
    memcpy(&buf[1], datas, length);
    if (i2c.write(address, buf, length + 1)) puts("I2C write failed");
}

uint8_t I2CDevice::read(char reg)
{
    char buf[1];
    read(reg, buf, 1);
    return buf[0];
}

void I2CDevice::read(char reg, char *datas, int length)
{
	if (i2c.write(address, &reg, 1, true)) puts("I2C write failed");
    if (i2c.read(address, datas, length)) puts("I2C read failed");
}
