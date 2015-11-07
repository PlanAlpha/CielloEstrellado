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

namespace PlanAlpha {
    extern PASpeaker          speaker1;
    extern PASpeaker          speaker2;
    extern GCADJD             leftColorSensor;
    extern GCADJD             rightColorSensor;
    extern GC6050             gyroAcceleroSensor;
    extern PAL3G4200D         gyroSensor;
    extern PALineSensor       forwardLeftLineSensor;
    extern PALineSensor       forwardCenterLineSensor;
    extern PALineSensor       forwardRightLineSensor;
    extern PALineSensor       middleLeftLineSensor;
    extern PALineSensor       middleRightLineSensor;
    extern PAThreeLineSensors forwardLineSensors;
    extern GCMotor            leftMotor;
    extern GCMotor            rightMotor;
    extern mbed::DigitalIn    powerSwitch;
    extern PAPIDController    pid;
    extern mbed::DigitalIn    rightTouchSensor;
    extern mbed::DigitalIn    leftTouchSensor;
    // p7
	
	extern mbed::PwmOut	      led1;
	extern mbed::PwmOut       led2;
	extern mbed::PwmOut       led3;
	extern mbed::PwmOut       led4;
    
    int PAApplicationMain();
    void pid_forward();
}

#endif
