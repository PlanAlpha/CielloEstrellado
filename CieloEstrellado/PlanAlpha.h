/*********************************************
 
 　　　　　　　　　　　 i!
 　　　　　　　　＿＿＿ﾉ;}
 　　　　　 ,　 ´: : : : : ｀ヽ、,_ _
 　　　　／: : : : : :: : : : : : ＼:ヽ
 　　　/: : : l: : | : : : : ﾄ、 : ヽ :ヽ
 　　/: : : :  : 八 : :: :./:.ヽ_ : ヽ: |
 　 ,: :: : : !: : :ﾉ 　ヽl＼/　　ヽ:ノ: |
 　 l: :: :|  / TT　　　 　TT 　:i: |: :j
 　 \:\ :: :|　　Ｕ　 　　　Ｕ 　 |: | :,'
 　　 ＼: ::i 　 , ,　　　　, , :l::八丿
 　　　　ヽ :|_ 　　　　＿,　　ｨ~
 　　　　　ヽrｹ､=‐-t------r-ァ:イ/
 　 　 　 　 ｀　., '｀iヽヽ//､::i|:;
 　　　　　　　/　 ,'个-｀_8:、｀､
 　　　　　　 /　 ,'::;;:;:;: 、ヽ
 　　　　　 /((┃))＿＿＿＿_＿i　|　 キュッキュッ
 　　　　  /ヽ,,⌒) ￣￣￣￣￣（,,ノ ＼
 　　　   /＿＿＿＿＿＿＿＿＿＿ヽ.. 　  ＼

 
 
 　　　　　　　　　　　 i!
 　　　　　　　　＿＿＿ﾉ;}
 　　　　　 ,　 ´: : : : : ｀ヽ、,_ _
 　　　　／: : : : : :: : : : : : ＼:ヽ
 　　　/: : : l: : | : : : : ﾄ、 : ヽ :ヽ
 　　/: : : :  : 八 : :: :./:.ヽ_ : ヽ: |
 　 ,: :: : : !: : :ﾉ 　ヽl＼/　　ヽ:ノ: |
 　 l: :: :|  / TT　　　 　TT 　:i: |: :j
 　 \:\ :: :|　　Ｕ　 　　　Ｕ 　 |: | :,'
 　　 ＼: ::i 　 , ,　　　　, , :l::八丿
 　　　　ヽ :|_ 　　　　＿,　　ｨ~
 　　　　　ヽrｹ､=‐-t------r-ァ:イ/
 　 　 　 　 ｀　., '｀iヽヽ//､::i|:;
 　　　　　　　/　 ,'个-｀_8:、｀､
 　　　　　　 /　 ,'::;;:;:;: 、ヽ
 　　　　　  |￣￣￣￣￣￣￣￣￣￣￣|　　ﾄﾝ
 　　 　（,,)　　　　　　　　　　(,,）_
 　 　  ／.　|   PlanAlpha.h    |＼
   　 ／　　.|＿＿＿＿＿＿＿＿＿＿.|　 ＼
 
**********************************************/

#ifndef __PlanAlpha__
#define __PlanAlpha__

#include "Robot_APIs/PASpeaker.h"
#include "Robot_APIs/GCADJD.h"
#include "Robot_APIs/GC6050.h"
#include "Robot_APIs/PAL3G4200D.h"
#include "Robot_APIs/PALineSensor.h"
#include "Robot_APIs/PAThreeLineSensors.h"
#include "Robot_APIs/GCMotor.h"
#include "Robot_APIs/PAPIDController.h"
#include "DigitalIn.h"
#include "Serial.h"
#include "Servo/Servo.h"

class PAApplecation {
	const int isLeftGreen = 1;
	const int isRightGreen = 2;
	const int isAllBlack = 3;
	bool isPausing = false;
	void serialHandler();
	void crossJudge(int);
	void leftCross();
	void unknownCross();
	void kabe();
	
protected:
	float pidValue = 0;
    PASpeaker          speaker1                 = PASpeaker(p23);
    PASpeaker          speaker2                 = PASpeaker(p24);
    GCADJD             leftColorSensor          = GCADJD(I2CDevice::Pin::I2C0);
    GCADJD             rightColorSensor         = GCADJD(I2CDevice::Pin::I2C1);
    //GC6050             gyroAcceleroSensor     = GC6050(I2CDevice::Pin::I2C0);
    //PAL3G4200D         gyroSensor             = PAL3G4200D(I2CDevice::Pin::I2C0);
    PALineSensor       forwardLeftLineSensor    = PALineSensor(p15, 10000);
    PALineSensor       forwardCenterLineSensor  = PALineSensor(p19, 16500);
    PALineSensor       forwardRightLineSensor   = PALineSensor(p17, 30000);
    PALineSensor       middleLeftLineSensor     = PALineSensor(p16, 30000);
    PALineSensor       middleRightLineSensor    = PALineSensor(p20, 30000);
    PAThreeLineSensors forwardLineSensors       = PAThreeLineSensors(
                            &forwardLeftLineSensor, &forwardCenterLineSensor, &forwardRightLineSensor
                       );
    GCMotor            rightMotor               = GCMotor(p30, p25, true);
    GCMotor            leftMotor                = GCMotor(p29, p26, true);
    mbed::DigitalIn    powerSwitch              = mbed::DigitalIn(p18, PullNone);
    PAPIDController    pid                      = PAPIDController(0.000001, 0.000000, 0.000000, 50000);
    mbed::DigitalIn    rightTouchSensor         = mbed::DigitalIn(p7, PullNone);
    mbed::DigitalIn    leftTouchSensor          = mbed::DigitalIn(p8, PullNone);
    
    mbed::PwmOut       led1                     = mbed::PwmOut(LED1);
    mbed::PwmOut       led2                     = mbed::PwmOut(LED2);
    mbed::PwmOut       led3                     = mbed::PwmOut(LED3);
    mbed::PwmOut       led4                     = mbed::PwmOut(LED4);
	mbed::Serial pc;
	mbed::DigitalIn    mercury					= mbed::DigitalIn(p14, PullNone);
	bool leftFirst = true;
	
public:
	PAApplecation() : pc(USBTX, USBRX) {}
    void main();
    void pid_forward();
};

#endif
