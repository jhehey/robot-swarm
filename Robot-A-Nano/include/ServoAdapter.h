#ifndef __SERVOADAPTER_H__
#define __SERVOADAPTER_H__

#include <Servo.h>          //Servo motor library. This is standard library
#include "MyPins.h"
#include <neotimer.h>

Servo servo_motor; //our servo name

Neotimer servoTimer;

/* Configuration */
float servoAdder = 40.0f;
int servoScanTimeMS = 1000;

bool servoScanning = false;
float servoAngle = 90.0f;

int startAngle = 20;
int stopAngle  = 160;


void SetupServo() {
	Serial.println("Setup Servo...");
	servo_motor.attach(SERVO_PIN); //our servo pin
  servo_motor.write(90);

	servoTimer.set(servoScanTimeMS);
}

void ServoScanStart() {
	servoAngle = 90;
	servo_motor.write(servoAngle);
	servoScanning = true;
}

void ServoScanStop() {
	servoAngle = 90;
	servo_motor.write(servoAngle);
	servoScanning = false;
}

void ServoScanLoop() {
	if(!servoScanning) return;

	if(servoTimer.repeat()) {

		if(servoAngle > stopAngle) {
			servoAdder = abs(servoAdder) * -1;
			Serial.print("LEFT: ");
		}

		if(servoAngle < startAngle){
			servoAdder = abs(servoAdder);
			Serial.println("RIGHT: ");
		}
		
		servoAngle += servoAdder;

		Serial.println(servoAngle);
		servo_motor.write(servoAngle);
	}
}

void LookRight(){  
	servo_motor.write(10);
	servo_motor.write(90);
}

void LookLeft(){  
	servo_motor.write(170);
	servo_motor.write(90);
}

void LookCenter(){  
	servo_motor.write(90);
}

#endif
