#include "PlanAlpha.h"
#include "wait_api.h"

int PlanAlpha::PAApplicationMain()
{
    using namespace PlanAlpha;
	
	float motorSpeed = 0.2;
//	while (1) {
//		printf("%f", forwardLeftLineSensor.readRawValue());
//		printf("\t");
//		printf("%f", forwardCenterLineSensor.readRawValue());
//		printf("\t");
//		printf("%f", forwardRightLineSensor.readRawValue());
//		printf("\n");
//	}
	while (1) {
		if (forwardLineSensors.read() & PAThreeLineSensors::Left) {
			if (forwardLineSensors.read() & PAThreeLineSensors::Right) {
				//akaaaaaaaaaaaaaaaaaaaaaaan
//				speaker1.play(440, 0.5, 100);
			}else{
//				speaker1.play(600, 0.5, 100);
				leftMotor.forward(-motorSpeed);
				rightMotor.forward(motorSpeed);
			}
		}else{
			if(forwardLineSensors.read() & PAThreeLineSensors::Right) {
				leftMotor.forward(motorSpeed);
				rightMotor.forward(-motorSpeed);
			}else{
				leftMotor.forward(motorSpeed);
				rightMotor.forward(motorSpeed);
			}
		}
	}
	
	
	

    return 0;
}
