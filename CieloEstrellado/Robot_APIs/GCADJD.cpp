#include "GCADJD.h"

constexpr int GCADJD::caps[];
constexpr int GCADJD::integrations[];

GCADJD::GCADJD(I2CDevice::Pin pin) : sensor(pin, i2cAddress)
{
    for (int i : caps) {
        sensor.write(i, cap_value);
    }
    uint8_t integValues[] = {
        low_int_value,
        high_int_value,
    };
    for (int i : integrations) {
        sensor.write(i, integValues, sizeof(integValues) / sizeof(integValues[0]));
    }
}

GCADJD::GCADJDValue GCADJD::read()
{
    sensor.write(ctrl, getSensorReading);
    while (sensor.read(ctrl)) ;
    union {
        uint8_t  buf[8];
        uint16_t values[4];
    } data;
    sensor.read(data_red_lo, data.buf, 8);
    return {
        data.values[0],
        data.values[1],
        data.values[2],
        data.values[3]
    };
}

bool GCADJD::isGreen()
{
    GCADJDValue value = read();
    return value.red < 850 && value.green > 1000 && value.blue < 850;
}
