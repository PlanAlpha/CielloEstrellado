#include "PAThreeLineSensors.h"

PAThreeLineSensors::PAThreeLineSensors(PALineSensor *_left, PALineSensor *_center, PALineSensor *_right) : left(_left), center(_center), right(_right)
{
    
}

PAThreeLineSensors::Sensors PAThreeLineSensors::read()
{
    return *left | *center << 1 | *right << 2;
}
