#ifndef __GC6050__
#define __GC6050__

#include "../Core_APIs/I2CDevice.h"
#include <inttypes.h>

class GC6050 {
public:
    struct AccelValue {
        float x;
        float y;
        float z;
    };
    struct GyroValue {
        float x;
        float y;
        float z;
    };

private:
    static constexpr uint8_t i2cAddress    = 104;
    static constexpr uint8_t accelAddress  = 59;
    static constexpr uint8_t gyroAddress   = 67;
    static constexpr uint8_t whoAmIAddress = 117;
    static constexpr uint8_t powerAddress  = 107;
    
    I2CDevice i2c;
    
    AccelValue currentAccelValue = {0, 0, 0};
    GyroValue  currentGyroValue  = {0, 0, 0};
    
    AccelValue accelOffsets = {0, 0, 0};
    GyroValue  gyroOffsets  = {0, 0, 0};
    
public:
    GC6050(I2CDevice::Pin dev, bool isAD0Pulluped = false);
    void updateValues();
    float accelX() {
        return currentAccelValue.x;
    }
    float accelY() {
        return currentAccelValue.y;
    }
    float accelZ() {
        return currentAccelValue.z;
    }
    float gyroX() {
        return currentGyroValue.x;
    }
    float gyroY() {
        return currentGyroValue.y;
    }
    float gyroZ() {
        return currentGyroValue.z;
    }
    void setOffsets();
    void calibrate();
};

#endif
