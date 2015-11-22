#include "PlanAlpha.h"
#include "wait_api.h"
#include <string.h>
#include "Serial.h"
#include "SerialBase.h"

#define PRINT_SENSORS

//---------------------------------------------------------------------

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

//---------------------------------------------------------------------

void PAApplecation::kabe()
{
	float motorSpeed = 0.3;
//	leftMotor.forward(-motorSpeed);
//	rightMotor.forward(-motorSpeed);
//	wait_ms(300);
//	
//	leftMotor.forward(motorSpeed);
//	rightMotor.forward(-motorSpeed);
//	wait_ms(500);
//	
//	while (1) {
//		if (leftTouchSensor.read()) {
//			leftMotor.forward(0.3);
//			rightMotor.forward(-0.3);
//		} else {
//			leftMotor.free();
//			rightMotor.forward(0.3);
//		}
//	}
	
	leftMotor.forward(-motorSpeed);
	rightMotor.forward(-motorSpeed);
	wait_ms(300);
	
	leftMotor.forward(motorSpeed);
	rightMotor.forward(-motorSpeed);
	wait_ms(500);
	
	rightMotor.forward(motorSpeed);
	wait_ms(300);
	
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

//---------------------------------------------------------------------

void PAApplecation::leftCross()
{
	leftMotor.forward(0.0);
	rightMotor.forward(0.5);
	wait_ms(500);
	leftMotor.forward(0.5);
	rightMotor.forward(0.0);
	wait_ms(500);
	leftMotor.forward(0.0);
	rightMotor.forward(-0.5);
	wait_ms(500);
	leftMotor.forward(-0.5);
	rightMotor.forward(0.0);
	wait_ms(500);
	
	leftMotor.forward(0.3);
	rightMotor.forward(0.3);
	wait_ms(400);
	
	leftMotor.free();
	rightMotor.free();
	while (1) {
		if (forwardLeftLineSensor.isBlack()  | forwardRightLineSensor.isBlack()) {
			break;
		}
		leftMotor.forward(-0.3);
		rightMotor.forward(0.3);
	}
}

//---------------------------------------------------------------------

void PAApplecation::crossJudge(int direction)
{
	float motorSpeed = 0.27;
	
	if (direction == isLeftGreen) {
//		leftMotor.forward(motorSpeed);
//		rightMotor.forward(motorSpeed);
		wait_ms(1000);
		while (1) {
			if (forwardLeftLineSensor.isBlack()) {
				leftMotor.forward(-motorSpeed);
				rightMotor.forward(motorSpeed);
				wait_ms(300);
				break;
			} else {
				leftMotor.forward(-motorSpeed);
				rightMotor.forward(motorSpeed);
			}
		}
		leftMotor.free();
		rightMotor.free();
	}
}

//---------------------------------------------------------------------

void PAApplecation::main()
{
//	pc.attach(this, &PAApplecation::serialHandler);
	
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
		printf("%d", leftColorSensor.isBlack(leftColor));
		printf("\t");
		printf("%d", leftColorSensor.isGreen(leftColor));
		printf("\t");
//
		printf("%d", rightColor.red);
		printf("\t");
		printf("%d", rightColor.green);
		printf("\t");
		printf("%d", rightColor.blue);
		printf("\t");
		printf("%d", leftColorSensor.isBlack(rightColor));
		printf("\t");
		printf("%d", rightColorSensor.isGreen(rightColor));
		printf("\t");
		
		printf("%d", forwardLeftLineSensor.readRawValue());
		printf("\t");
		printf("%d", forwardLeftLineSensor.isBlack());
		printf("\t");
		printf("%d", middleLeftLineSensor.readRawValue());
		printf("\t");
		printf("%d", middleLeftLineSensor.isBlack());
		printf("\t");
		printf("%d", forwardCenterLineSensor.readRawValue());
		printf("\t");
		printf("%d", forwardCenterLineSensor.isBlack());
		printf("\t");
		printf("%d", middleRightLineSensor.readRawValue());
		printf("\t");
		printf("%d", middleRightLineSensor.isBlack());
		printf("\t");
		printf("%d", forwardRightLineSensor.readRawValue());
		printf("\t");
		printf("%d", forwardRightLineSensor.isBlack());
		printf("\r\n");
		
		wait_ms(50);
	}
#endif
	
	//---------------------------------------------------------------------
	
//	mbed::Timer timer;
//	uint16_t leftGreenJudgeValue = 20000;
//	uint16_t rightGreenJudgeValue = 40000;
	float motorSpeed = 0.27;
//	timer.start();
	while (1) {
		
		/*
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
		 */
		
//		if (forwardLeftLineSensor.isBlack() && forwardCenterLineSensor.isBlack() && forwardRightLineSensor.isBlack()) {
//			leftMotor.forward(motorSpeed);
//			rightMotor.forward(motorSpeed);
//			wait_ms(300);
//			
//			while (1) {
//				leftMotor.forward(-motorSpeed);
//				rightMotor.forward(motorSpeed);
//				if (forwardLeftLineSensor.isBlack()) {
//					break;
//				}
//			}
////			crossJudge(isAllBlack);
//			
//		}
//		else if (forwardLeftLineSensor.isBlack() && forwardCenterLineSensor.isBlack()) {
//			leftMotor.free();
//			rightMotor.free();
//			crossJudge(isLeftGreen);
//		}
		
		if (forwardLeftLineSensor.isBlack()) {
			leftMotor.forward(-motorSpeed);
			rightMotor.forward(motorSpeed);
			while (forwardLeftLineSensor.isBlack()) wait_ms(10);
		}
		if (forwardRightLineSensor.isBlack()) {
			leftMotor.forward(motorSpeed);
			rightMotor.forward(-motorSpeed);
			while (forwardRightLineSensor.isBlack()) wait_ms(10);
		}
		if (middleLeftLineSensor.isBlack()) {
			if (middleRightLineSensor.isBlack()) {
				leftMotor.forward(motorSpeed);
				rightMotor.forward(motorSpeed);
			} else {
				leftMotor.forward(-motorSpeed);
				rightMotor.forward(motorSpeed);
			}
		} else {
			if (middleRightLineSensor.isBlack()) {
				leftMotor.forward(motorSpeed);
				rightMotor.forward(-motorSpeed);
			} else {
				leftMotor.forward(motorSpeed);
				rightMotor.forward(motorSpeed);
//				pid_forward();
			}
		}
		if (leftTouchSensor.read() & rightTouchSensor.read()) {
			kabe();
		}
		
		auto leftColorValue = leftColorSensor.read();
		auto rightColorValue = rightColorSensor.read();
		if (leftColorSensor.isGreen(leftColorValue)) {
//			leftMotor.free();
//			rightMotor.free();
//			wait_ms(500);
			
			leftMotor.forward(motorSpeed);
			rightMotor.forward(motorSpeed);
			while (! ((forwardLeftLineSensor.isBlack() || middleLeftLineSensor.isBlack()))) ;
			while (forwardLeftLineSensor.isBlack() || middleLeftLineSensor.isBlack() || middleRightLineSensor.isBlack() || forwardRightLineSensor.isBlack()) ;
			leftMotor.free();
			rightMotor.free();
//			while (powerSwitch) ;
			wait_ms(500);
			
			leftMotor.forward(-motorSpeed);
			rightMotor.forward(motorSpeed);
//			while (! forwardRightLineSensor.isBlack()) ;
//			while (middleRightLineSensor.isBlack() || forwardRightLineSensor.isBlack()) ;
//			while (! forwardRightLineSensor.isBlack()) ;
//			while (forwardLeftLineSensor.isBlack()) ;
//			while (! forwardLeftLineSensor.isBlack()) ;
//			while (! middleLeftLineSensor.isBlack()) ;
//			while (forwardCenterLineSensor.isBlack()) ;
//			while (! forwardCenterLineSensor.isBlack()) ;
//			while (! (! middleLeftLineSensor && forwardCenterLineSensor.isBlack() && ! middleRightLineSensor.isBlack())) ;
			while (! leftColorSensor.isBlack()) ;
			while (leftColorSensor.isBlack()) ;
			
//			leftMotor.free();
//			rightMotor.free();
//			wait_ms(200);
//			while (powerSwitch) ;
			leftMotor.free();
			while (! rightColorSensor.isBlack()) ;
//			while (! forwardCenterLineSensor.isBlack()) ;
		} else if (rightColorSensor.isGreen(rightColorValue)) {
////			leftMotor.free();
////			rightMotor.free();
////			wait_ms(500);
//			
//			leftMotor.forward(motorSpeed);
//			rightMotor.forward(motorSpeed);
//			while (! ((forwardLeftLineSensor.isBlack() || middleLeftLineSensor.isBlack()) && (middleRightLineSensor.isBlack() || forwardRightLineSensor.isBlack()))) ;
//			while (forwardLeftLineSensor.isBlack() || middleLeftLineSensor.isBlack() || middleRightLineSensor.isBlack() || forwardRightLineSensor.isBlack()) ;
//			leftMotor.free();
//			rightMotor.free();
//			wait_ms(200);
//			
//			leftMotor.forward(motorSpeed);
//			rightMotor.forward(-motorSpeed);
////			while (! forwardLeftLineSensor.isBlack()) ;
////			while (middleLeftLineSensor.isBlack() || forwardLeftLineSensor.isBlack()) ;
//			while (! forwardRightLineSensor.isBlack()) ;
////			while (forwardRightLineSensor.isBlack()) ;
////			while (! forwardRightLineSensor.isBlack()) ;
//			
//			rightMotor.free();
//			while (! forwardCenterLineSensor.isBlack() ) ;
			
			leftMotor.forward(motorSpeed);
			rightMotor.forward(motorSpeed);
			while (! ((forwardLeftLineSensor.isBlack() || middleLeftLineSensor.isBlack()))) ;
			while (forwardLeftLineSensor.isBlack() || middleLeftLineSensor.isBlack() || middleRightLineSensor.isBlack() || forwardRightLineSensor.isBlack()) ;
			leftMotor.free();
			rightMotor.free();
			wait_ms(500);
			
			leftMotor.forward(motorSpeed);
			rightMotor.forward(-motorSpeed);
			while (! rightColorSensor.isBlack()) ;
			while (rightColorSensor.isBlack()) ;
			
			rightMotor.free();
			while (! leftColorSensor.isBlack()) ;
		}
		
//		if (leftColorSensor.isBlack(leftColorValue) && rightColorSensor.isBlack(rightColorValue)) {
//			speaker1.play(440, 0.8, 1000);
//			leftMotor.forward(motorSpeed);
//			rightMotor.forward(motorSpeed);
//			
//			wait_ms(300);
////			while (! (forwardLeftLineSensor.isBlack() && forwardRightLineSensor.isBlack())) ;
////			while (forwardLeftLineSensor.isBlack() || forwardRightLineSensor.isBlack()) ;
//		}
		
//		if (rightColorSensor.isBlack(rightColorValue) && leftColorSensor.isBlack(leftColorValue)) {
//			speaker1.play(440, 0.8, 1000);
//			leftMotor.forward(motorSpeed);
//			rightMotor.forward(motorSpeed);
//			while (1) {
//				if (forwardLeftLineSensor.isBlack() || middleLeftLineSensor.isBlack()) {
//					Timer timer;
//					timer.start();
//					while (timer.read_ms() <= 100) {
//						if (middleRightLineSensor.isBlack() || forwardRightLineSensor.isBlack()) {
//							while (forwardLeftLineSensor.isBlack() || middleLeftLineSensor.isBlack() || middleRightLineSensor.isBlack() || forwardRightLineSensor.isBlack()) ;
//							goto endOfStraightCross;
//						}
//					}
//					leftMotor.forward(-motorSpeed);
//					rightMotor.forward(motorSpeed);
//					break;
//				} else if (middleRightLineSensor.isBlack() || forwardRightLineSensor.isBlack()) {
//					Timer timer;
//					timer.start();
//					while (timer.read_ms() <= 100) {
//						if (middleLeftLineSensor.isBlack() || forwardLeftLineSensor.isBlack()) {
//							while (forwardLeftLineSensor.isBlack() || middleLeftLineSensor.isBlack() || middleRightLineSensor.isBlack() || forwardRightLineSensor.isBlack()) ;
//							goto endOfStraightCross;
//						}
//					}
//					leftMotor.forward(motorSpeed);
//					rightMotor.forward(-motorSpeed);
//					break;
//				}
//			}
//			
//		endOfStraightCross:;
//		}
		
//		if (isPausing) {
//			leftMotor.free();
//			rightMotor.free();
//			while (isPausing) {
//				printf("Pause now \r\n");
//			}
//			printf("Resume");
//		}
		
//		led4.write(0);
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
