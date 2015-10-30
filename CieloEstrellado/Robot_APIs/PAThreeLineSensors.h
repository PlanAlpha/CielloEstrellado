#ifndef __PAThreeLineSensors__
#define __PAThreeLineSensors__

#include "PALineSensor.h"

class PAThreeLineSensors {
    PALineSensor *left;
    PALineSensor *center;
    PALineSensor *right;
    
public:
    typedef uint8_t Sensors;
    const static Sensors Left   = 1;
    const static Sensors Center = 1 << 1;
    const static Sensors Right  = 1 << 2;
    
    PAThreeLineSensors(PALineSensor *left, PALineSensor *center, PALineSensor *right);
    Sensors read();
};

#endif
