#include "PlanAlpha.h"
#include "wait_api.h"
#include <string.h>

#define DEBUG

int PlanAlpha::PAApplicationMain()
{
    using namespace PlanAlpha;
	
#ifdef DEBUG
	while (1) {
		auto leftColor = leftColorSensor.read();
		if (leftColorSensor.isGreen()) {
			speaker1.play(440, 0.5, 50);
		}
		auto rightColor = rightColorSensor.read();
		if (rightColorSensor.isGreen()) {
			speaker2.play(440, 0.5, 50);
		}
		
		printf("%d", leftColor.red);
		printf("\t");
		printf("%d", leftColor.green);
		printf("\t");
		printf("%d", leftColor.blue);
		printf("\t");
		
		printf("%d", rightColor.red);
		printf("\t");
		printf("%d", rightColor.green);
		printf("\t");
		printf("%d", rightColor.blue);
		printf("\t");
		
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
		printf("\r\n");
		
		wait_ms(50);
	}
#endif
	
	
	float motorSpeed = 0.25;
	while (1) {
		if (forwardLineSensors.read() & PAThreeLineSensors::Left) {
			if (forwardLineSensors.read() & PAThreeLineSensors::Right) {
				leftMotor.forward(-motorSpeed);
				rightMotor.forward(-motorSpeed);
			}else{
				led4.write(1);
				leftMotor.forward(motorSpeed);
				rightMotor.forward(-motorSpeed);
			}
		}else{
			if(forwardLineSensors.read() & PAThreeLineSensors::Right) {
				led3.write(1);
				leftMotor.forward(-motorSpeed);
				rightMotor.forward(motorSpeed);
			}else{
				leftMotor.forward(motorSpeed);
				rightMotor.forward(motorSpeed);
			}
		}
		wait_ms(10);
		led4.write(0);
		led3.write(0);
	}
	
	
	

    return 0;
}
