#include "PlanAlpha.h"
#include "wait_api.h"

int main(int __attribute__((unused)) argc, const char __attribute__((unused)) * argv[])
{
    using namespace PlanAlpha;
    while (1) {
        for (int i = -1000; i < 1000; i++) {
            rightMotor.forward(i / 1000.0);
            leftMotor.forward(i / 1000.0);
            wait_ms(1);
        }
        for (int i = 1000; i > -1000; i--) {
            rightMotor.forward(i / 1000.0);
            leftMotor.forward(i / 1000.0);
            wait_ms(1);
        }
    }

    return 0;
}
