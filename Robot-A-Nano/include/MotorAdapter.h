#ifndef __MOTORADAPTER_H__
#define __MOTORADAPTER_H__

#include <Arduino.h>
#include "MyPins.h"

boolean goesForward = false;

void SetupMotor() {
	Serial.println("Setup Motor...");
	pinMode(RIGHTMOTOR_FORWARD, OUTPUT);
  pinMode(LEFTMOTOR_FORWARD, OUTPUT);
  pinMode(RIGHTMOTOR_BACKWARD, OUTPUT);
  pinMode(LEFTMOTOR_BACKWARD, OUTPUT);
}

void StopMotor(){
	goesForward=false;

  digitalWrite(RIGHTMOTOR_FORWARD, LOW);
  digitalWrite(LEFTMOTOR_FORWARD, LOW);

  digitalWrite(RIGHTMOTOR_BACKWARD, LOW);
  digitalWrite(LEFTMOTOR_BACKWARD, LOW);
}

void MoveForward(){
  if(!goesForward){

    goesForward=true;
			
		digitalWrite(LEFTMOTOR_BACKWARD, HIGH);
		digitalWrite(RIGHTMOTOR_BACKWARD, HIGH);
		
		digitalWrite(LEFTMOTOR_FORWARD, LOW);
		digitalWrite(RIGHTMOTOR_FORWARD, LOW);

  }
}

void MoveBackward(){

  goesForward=false;

	digitalWrite(LEFTMOTOR_FORWARD, HIGH);
	digitalWrite(RIGHTMOTOR_FORWARD, HIGH);

	digitalWrite(LEFTMOTOR_BACKWARD, LOW);
	digitalWrite(RIGHTMOTOR_BACKWARD, LOW); 
}

void TurnRight(int durationFactor = 700){

  digitalWrite(LEFTMOTOR_FORWARD, HIGH);
  digitalWrite(RIGHTMOTOR_BACKWARD, HIGH);
  
  digitalWrite(LEFTMOTOR_BACKWARD, LOW);
  digitalWrite(RIGHTMOTOR_FORWARD, LOW);
  
  // delay(durationFactor);
	// StopMotor();
  
  // digitalWrite(LEFTMOTOR_FORWARD, HIGH);
  // digitalWrite(RIGHTMOTOR_FORWARD, HIGH);
  
  // digitalWrite(LEFTMOTOR_BACKWARD, LOW);
  // digitalWrite(RIGHTMOTOR_BACKWARD, LOW);
}

void TurnLeft(int durationFactor = 700){

  digitalWrite(LEFTMOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHTMOTOR_FORWARD, HIGH);
  
  digitalWrite(LEFTMOTOR_FORWARD, LOW);
  digitalWrite(RIGHTMOTOR_BACKWARD, LOW);

  // delay(durationFactor);

	// StopMotor();
  
  // digitalWrite(LEFTMOTOR_FORWARD, HIGH);
  // digitalWrite(RIGHTMOTOR_FORWARD, HIGH);
  
  // digitalWrite(LEFTMOTOR_BACKWARD, LOW);
  // digitalWrite(RIGHTMOTOR_BACKWARD, LOW);
}


#endif
