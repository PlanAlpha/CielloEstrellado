#ifndef __GCADJD__
#define __GCADJD__

#include "../Core_APIs/I2CDevice.h"
#include <inttypes.h>

class GCADJD {
    static constexpr int i2cAddress = 0x74 << 1;
    static constexpr int cap_red    = 6;
    static constexpr int cap_green  = 7;
    static constexpr int cap_blue   = 8;
    static constexpr int cap_clear  = 9;
    static constexpr int cap_value  = 10;
    static constexpr int caps[] = {
        cap_red,
        cap_green,
        cap_blue,
        cap_clear,
    };
    static constexpr char int_red   = 10;
    static constexpr char int_green = 12;
    static constexpr char int_blue  = 14;
    static constexpr char int_clear = 16;
    static constexpr char integrations[] = {
        int_red,
        int_green,
        int_blue,
        int_clear,
    };
    static constexpr char low_int_value  = 2500 & 255;
    static constexpr char high_int_value = 2500 >> 8;
    static constexpr char ctrl = 0;
    static constexpr char getSensorReading = 1;
    static constexpr char data_red_lo   = 64;
    static constexpr char data_red_hi   = 65;
    static constexpr char data_green_lo = 66;
    static constexpr char data_green_hi = 67;
    static constexpr char data_blue_lo  = 68;
    static constexpr char data_blue_hi  = 69;
    static constexpr char data_clear_lo = 70;
    static constexpr char data_clear_hi = 71;
    I2CDevice sensor;
    
public:
    struct GCADJDValue {
        uint16_t red;
        uint16_t green;
        uint16_t blue;
        uint16_t clear;
    };
    
    GCADJD(I2CDevice::Pin pin);
    GCADJDValue read();
	bool isGreen() {
		return isGreen(read());
	}
	bool isGreen(GCADJDValue value);
	bool isBlack() {
		return isBlack(read());
	}
	bool isBlack(GCADJDValue value);
};

#endif
