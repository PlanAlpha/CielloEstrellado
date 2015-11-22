#include "GCADJD.h"

constexpr int GCADJD::caps[];
constexpr char GCADJD::integrations[];

GCADJD::GCADJD(I2CDevice::Pin pin) : sensor(pin, i2cAddress)
{
    for (int i : caps) {
        sensor.write(i, cap_value);
    }
    char integValues[] = {
        low_int_value,
        high_int_value,
    };
    for (char i : integrations) {
        sensor.write(i, integValues, sizeof(integValues) / sizeof(integValues[0]));
    }
}

GCADJD::GCADJDValue GCADJD::read()
{
    sensor.write(ctrl, getSensorReading);
    while (sensor.read(ctrl)) ;
    union {
        char buf[8];
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

bool GCADJD::isGreen(GCADJD::GCADJDValue value)
{
	return value.blue >= value.red && (value.blue - value.red) < 100  && value.green < 850 /* && value.red < 500 */;
}

bool GCADJD::isBlack(GCADJD::GCADJDValue value)
{
	return (value.blue - value.red) < 50 /* && value.red != 1023 */ && (value.red != 1023 || value.blue != 1023) && value.green == 1023 /* && value.blue != 1023 */;
}
