#include "PlanAlpha.h"
#include "wait_api.h"
#include <string.h>

//#define PRINT_SENSORS

void PAApplecation::main()
{
	
#ifdef PRINT_SENSORS
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
		printf("%d", forwardCenterLineSensor.isBlack());
		printf("\t");
		printf("%d", forwardRightLineSensor.readRawValue());
		printf("\t");
		printf("%d", forwardRightLineSensor.isBlack());
		printf("\r\n");
		
		wait_ms(50);
	}
#endif
	
	
	float motorSpeed = 0.5;
	while (1) {
        switch (forwardLineSensors.read()) {
            case PAThreeLineSensors::Left | PAThreeLineSensors::Center:
            case PAThreeLineSensors::Left:
//                led4.write(1);
                leftMotor.forward(-motorSpeed);
                rightMotor.forward(motorSpeed);
                break;
                
            case PAThreeLineSensors::Left | PAThreeLineSensors::Right:
                leftMotor.forward(-motorSpeed);
                rightMotor.forward(-motorSpeed);
//                led4.write(0);
//                led3.write(0);
                break;
                
            case PAThreeLineSensors::Right | PAThreeLineSensors::Center:
            case PAThreeLineSensors::Right:
//                led3.write(1);
                leftMotor.forward(motorSpeed);
                rightMotor.forward(-motorSpeed);
                break;
                
            default:
                pid_forward();
//                led4.write(0);
//                led3.write(0);
                break;
        }
        
        if (rightTouchSensor && leftTouchSensor) {
            leftMotor.forward(-motorSpeed);
            rightMotor.forward(-motorSpeed);
            wait_ms(300);
            
            leftMotor.forward(motorSpeed);
            rightMotor.forward(-motorSpeed);
            wait_ms(500);
            
            while (1) {
                leftMotor.free();
                rightMotor.forward(motorSpeed);
                while (! leftTouchSensor) {
                    if (forwardLineSensors.read()) {
                        goto out;
                    }
                }
                leftMotor.forward(motorSpeed);
                rightMotor.forward(-motorSpeed);
                wait_ms(150);
            }
        out:
            leftMotor.forward(motorSpeed);
            rightMotor.forward(-motorSpeed);
            wait_ms(600);
            leftMotor.forward(motorSpeed);
            rightMotor.forward(motorSpeed);
            while (! (forwardLineSensors.read() & PAThreeLineSensors::Right)) ;
            leftMotor.forward(motorSpeed);
            rightMotor.forward(-motorSpeed);
        }
        
		wait_ms(10);
	}
}
