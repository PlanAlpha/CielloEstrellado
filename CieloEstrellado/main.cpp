#include "PlanAlpha.h"
#include "wait_api.h"
#include <string.h>
#include "Serial.h"
#include "SerialBase.h"

//#define PRINT_SENSORS

bool isPausing = false;

void PAApplecation::serialHandler()
{
	led4 = ! led4;
	char c = pc.getc();
	
	switch (c) {
		case 'p':
			isPausing = true;
			break;
		case 's':
			isPausing = false;
			break;
		default:
			break;
	}
}
void PAApplecation::kabe()
{
	float motorSpeed = 0.3;
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
	
}
void PAApplecation::unknownCross()
{
	float motorSpeed = 0.3;
	leftMotor.forward(motorSpeed);
	rightMotor.forward(motorSpeed);
	wait_ms(500);
	if (forwardCenterLineSensor.isBlack()) {
		goto end;
	}
	
	leftMotor.forward(-motorSpeed);
	rightMotor.forward(-motorSpeed);
	while(1){
		mbed::Timer timer;
		timer.start();
		while(timer.read_ms() < 1000){
			leftMotor.forward(-motorSpeed);
			rightMotor.forward(motorSpeed);
			if(forwardRightLineSensor.isBlack()){
				goto end;
				break;
			}
		}
		while(1){
			leftMotor.forward(motorSpeed);
			rightMotor.forward(-motorSpeed);
			if (forwardLeftLineSensor.isBlack()) {
				break;
			}
		}
	}
end:;
}

void PAApplecation::leftCross()
{
	leftMotor.forward(0.25);
	rightMotor.forward(0.25);
	wait_ms(300);
	leftMotor.free();
	rightMotor.free();
	leftMotor.forward(-0.3);
	rightMotor.forward(0.3);
	wait_ms(800);
	while (!forwardRightLineSensor.isBlack()) {
		leftMotor.forward(-0.3);
		rightMotor.forward(0.3);
	}
	leftMotor.forward(0.25);
	rightMotor.forward(0.25);
	wait_ms(500);
	
	//	mbed::Timer timer;
	//	timer.start();
	//	while (timer.read_ms() < 800) {
	//		if (forwardLeftLineSensor.isBlack()) {
	//			break;
	//		}
	//		leftMotor.forward(-0.4);
	//		rightMotor.forward(0.4);
	//	}
}

void PAApplecation::main()
{
	pc.attach(this, &PAApplecation::serialHandler);
	
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
		
		//		if (forwardLeftLineSensor.isBlack()) {
		//			speaker2.play(600, 0.7, 50);
		//		}
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
		printf("\t");
		printf("%d", middleLeftLineSensor.readRawValue());
		printf("\t");
		printf("%d", middleLeftLineSensor.isBlack());
		printf("\t");
		printf("%d", middleRightLineSensor.readRawValue());
		printf("\t");
		printf("%d", middleRightLineSensor.isBlack());
		printf("\r\n");
		
		//		wait_ms(50);
	}
#endif
	
	mbed::Timer timer;
	float motorSpeed = 0.27;
	timer.start();
	while (1) {
		static int leftGreenCount = 0;
		if (leftColorSensor.isGreen()) {
			leftGreenCount++;
			speaker2.play(440, 0.8, 50);
		}
		if (leftGreenCount > 3) {
			leftMotor.free();
			rightMotor.free();
			puts("detect Green Mark");
			wait_ms(1000);
			leftCross();
		}
		if (timer.read_ms() > 100) {
			printf("%d \r\n", leftGreenCount);
			leftGreenCount = 0;
			timer.reset();
		}
		if (forwardLeftLineSensor.isBlack()) {
			if (forwardRightLineSensor.isBlack()) {
				//				leftMotor.forward(-motorSpeed);
				//				rightMotor.forward(-motorSpeed);
				unknownCross();
			} else {
				leftMotor.forward(-motorSpeed*2);
				rightMotor.forward(motorSpeed*2);
				wait_ms(50);
			}
		} else {
			if (forwardRightLineSensor.isBlack()) {
				leftMotor.forward(motorSpeed*2);
				rightMotor.forward(-motorSpeed*2);
				wait_ms(50);
			} else {
				leftMotor.forward(motorSpeed);
				rightMotor.forward(motorSpeed);
			}
		}
		if (leftTouchSensor.read() | rightTouchSensor.read()) {
			kabe();
		}
		
		
		if (isPausing) {
			leftMotor.free();
			rightMotor.free();
			while (isPausing) {
				printf("Pause now \r\n");
			}
			printf("Resume");
		}
		
		led4.write(0);
	}
	//	while (1) {
	//		auto forwardLineValue = forwardLineSensors.read();
	//		if (forwardLineValue & PAThreeLineSensors::Left) {
	//			if (forwardLineValue & PAThreeLineSensors::Right) {
	//				leftMotor.forward(-motorSpeed);
	//				rightMotor.forward(-motorSpeed);
	//			} else {
	//				leftMotor.forward(-motorSpeed);
	//				rightMotor.forward(motorSpeed);
	//			}
	//		} else {
	//			if (forwardLineValue & PAThreeLineSensors::Right) {
	//				leftMotor.forward(motorSpeed);
	//				rightMotor.forward(-motorSpeed);
	////				led3.write(1);
	//			} else {
	//				leftMotor.forward(motorSpeed);
	//				rightMotor.forward(motorSpeed);
	////				pid_forward();
	//			}
	//		}
	//		static int leftGreenCount = 0;
	//		if (leftColorSensor.isGreen()) {
	//			speaker1.play(440, 0.7, 50);
	//			leftGreenCount++;
	//		}
	//		static int rightGreenCount = 0;
	//		if (rightColorSensor.isGreen()) {
	//			speaker1.play(440, 0.7, 50);
	//			rightGreenCount++;
	//		}
	//		if (timer.read_ms() > 100) {
	////			printf("%d", leftGreenCount);
	////			printf("\t");
	////			printf("%d \r\n", rightGreenCount);
	//			leftGreenCount = 0;
	//			rightGreenCount = 0;
	//			timer.reset();
	//		}
	////		led3.write(0);
	//	}
	
	//	while (1) {
	//        switch (forwardLineSensors.read()) {
	//            case PAThreeLineSensors::Left | PAThreeLineSensors::Center:
	//            case PAThreeLineSensors::Left:
	////                led4.write(1);
	//                leftMotor.forward(-motorSpeed);
	//                rightMotor.forward(motorSpeed);
	//                break;
	//
	//            case PAThreeLineSensors::Left | PAThreeLineSensors::Right:
	//                leftMotor.forward(-motorSpeed);
	//                rightMotor.forward(-motorSpeed);
	////                led4.write(0);
	////                led3.write(0);
	//                break;
	//
	//            case PAThreeLineSensors::Right | PAThreeLineSensors::Center:
	//            case PAThreeLineSensors::Right:
	////                led3.write(1);
	//                leftMotor.forward(motorSpeed);
	//                rightMotor.forward(-motorSpeed);
	//                break;
	//
	//            default:
	//                pid_forward();
	////                led4.write(0);
	////                led3.write(0);
	//                break;
	//        }
	//
	//        if (rightTouchSensor && leftTouchSensor) {
	//            leftMotor.forward(-motorSpeed);
	//            rightMotor.forward(-motorSpeed);
	//            wait_ms(300);
	//
	//            leftMotor.forward(motorSpeed);
	//            rightMotor.forward(-motorSpeed);
	//            wait_ms(500);
	//
	//            while (1) {
	//                leftMotor.free();
	//                rightMotor.forward(motorSpeed);
	//                while (! leftTouchSensor) {
	//                    if (forwardLineSensors.read()) {
	//                        goto out;
	//                    }
	//                }
	//                leftMotor.forward(motorSpeed);
	//                rightMotor.forward(-motorSpeed);
	//                wait_ms(150);
	//            }
	//        out:
	//            leftMotor.forward(motorSpeed);
	//            rightMotor.forward(-motorSpeed);
	//            wait_ms(600);
	//            leftMotor.forward(motorSpeed);
	//            rightMotor.forward(motorSpeed);
	//            while (! (forwardLineSensors.read() & PAThreeLineSensors::Right)) ;
	//            leftMotor.forward(motorSpeed);
	//            rightMotor.forward(-motorSpeed);
	//        }
	//
	//		wait_ms(10);
	//	}
}
