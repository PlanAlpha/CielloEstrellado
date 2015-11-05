#include "PlanAlpha.h"
#include "wait_api.h"

int PlanAlpha::PAApplicationMain()
{
    using namespace PlanAlpha;
	
	float motorSpeed = 0.25;
	
//	while (1) {
//		leftMotor.forward(motorSpeed);
//		rightMotor.forward(motorSpeed);
//		wait(1);
//		leftMotor.forward(-motorSpeed);
//		rightMotor.forward(-motorSpeed);
//		wait(1);
//	}

	while (1) {
		printf("%d", forwardLeftLineSensor.readRawValue());
		printf("\t");
		printf("%d", forwardLeftLineSensor.isBlack());
		printf("\t");
		printf("%d", forwardCenterLineSensor.readRawValue());
		printf("\t");
		printf("%d", forwardLeftLineSensor.isBlack());
		printf("\t");
		printf("%d", forwardRightLineSensor.readRawValue());
		printf("\t");
		printf("%d", forwardLeftLineSensor.isBlack());
		printf("\n");
	}
	
	const float threshold = 0.4;
	while (1) {
		if (forwardLeftLineSensor.readRawValue() < threshold) {
			if (forwardRightLineSensor.readRawValue() < threshold) {
				leftMotor.forward(-motorSpeed);
				rightMotor.forward(-motorSpeed);
			}else{
//				speaker1.play(500, 0.5, 100);
				leftMotor.forward(motorSpeed);
				rightMotor.forward(-motorSpeed);
			}
		}else{
			if(forwardRightLineSensor.readRawValue() < threshold) {
//				speaker1.play(600, 0.5, 100);
				leftMotor.forward(-motorSpeed);
				rightMotor.forward(motorSpeed);
			}else{
//				speaker1.play(700, 0.5, 100);
				leftMotor.forward(motorSpeed);
				rightMotor.forward(motorSpeed);
			}
		}
		printf("%f", forwardLeftLineSensor.readRawValue());
		printf("\t");
		printf("%f", forwardCenterLineSensor.readRawValue());
		printf("\t");
		printf("%f", forwardRightLineSensor.readRawValue());
		printf("\n");
		
		// this leds was gone \(¥_¥)/
//		led1.write(forwardRightLineSensor.readRawValue());
//		led4.write(forwardLeftLineSensor.readRawValue());
//		led2.write(forwardCenterLineSensor.readRawValue());
//		led3.write(forwardCenterLineSensor.readRawValue());
	}
	
	
	

    return 0;
}
