#include "PAL3G4200D.h"

PAL3G4200D::PAL3G4200D(I2CDevice::Pin pin) : device(pin, i2cAddress)
{
    while (1) {
        uint8_t who = device.read(WHO_AM_I);
        if (who != 211) {
            printf("error reading whoami %d\n", who);
        } else {
            break;
        }
    }
    
    /* set the frequency to 800 Hz */
    /* disable sleep mode */
    device.write(CTRL_REG1, 0b11001111);
    
    /* set the bit order to MSB (big endian) */
    /* set the full scale to 2000 dps */
    device.write(CTRL_REG4, 0b01110000);
}

float PAL3G4200D::readX()
{
    Data data;
    device.read(OUT_X_L, data.buf, 2);
    return xAverage.addValue(data.value);
}

float PAL3G4200D::readY()
{
    Data data;
    device.read(OUT_Y_L, data.buf, 2);
    return yAverage.addValue(data.value);
}

float PAL3G4200D::readZ()
{
    Data data;
    device.read(OUT_Z_L, data.buf, 2);
    return zAverage.addValue(data.value);
}
