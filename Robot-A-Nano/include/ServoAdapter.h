#ifndef __SERVOADAPTER_H__
#define __SERVOADAPTER_H__

#include <Servo.h>          //Servo motor library. This is standard library
#include "MyPins.h"

Servo servo_motor; //our servo name

void SetupServo() {
	servo_motor.attach(SERVO_PIN); //our servo pin
  servo_motor.write(90);
}

void LookRight(){  
  servo_motor.write(10);
  servo_motor.write(90);
}

void LookLeft(){
  servo_motor.write(170);
  servo_motor.write(90);
}


#endif
