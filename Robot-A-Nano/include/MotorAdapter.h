#ifndef __MOTORADAPTER_H__
#define __MOTORADAPTER_H__

#include <Arduino.h>
#include "MyPins.h"

boolean goesForward = false;

void SetupMotor() {
	pinMode(RIGHTMOTOR_FORWARD, OUTPUT);
  pinMode(LEFTMOTOR_FORWARD, OUTPUT);
  pinMode(LEFTMOTOR_FORWARD, OUTPUT);
  pinMode(RIGHTMOTOR_BACKWARD, OUTPUT);
}

void StopMotor(){
  digitalWrite(RIGHTMOTOR_FORWARD, LOW);
  digitalWrite(LEFTMOTOR_FORWARD, LOW);
  digitalWrite(RIGHTMOTOR_BACKWARD, LOW);
  digitalWrite(LEFTMOTOR_FORWARD, LOW);
}

void MoveForward(){
  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LEFTMOTOR_FORWARD, HIGH);
    digitalWrite(RIGHTMOTOR_FORWARD, HIGH);
  
    digitalWrite(LEFTMOTOR_FORWARD, LOW);
    digitalWrite(RIGHTMOTOR_BACKWARD, LOW); 
  }
}

void MoveBackward(){

  goesForward=false;

  digitalWrite(LEFTMOTOR_FORWARD, HIGH);
  digitalWrite(RIGHTMOTOR_BACKWARD, HIGH);
  
  digitalWrite(LEFTMOTOR_FORWARD, LOW);
  digitalWrite(RIGHTMOTOR_FORWARD, LOW);
  
}

void TurnRight(int durationFactor = 500){

  digitalWrite(LEFTMOTOR_FORWARD, HIGH);
  digitalWrite(RIGHTMOTOR_BACKWARD, HIGH);
  
  digitalWrite(LEFTMOTOR_FORWARD, LOW);
  digitalWrite(RIGHTMOTOR_FORWARD, LOW);
  
  delay(durationFactor);
  
  digitalWrite(LEFTMOTOR_FORWARD, HIGH);
  digitalWrite(RIGHTMOTOR_FORWARD, HIGH);
  
  digitalWrite(LEFTMOTOR_FORWARD, LOW);
  digitalWrite(RIGHTMOTOR_BACKWARD, LOW);
}

void TurnLeft(int durationFactor = 500){

  digitalWrite(LEFTMOTOR_FORWARD, HIGH);
  digitalWrite(RIGHTMOTOR_FORWARD, HIGH);
  
  digitalWrite(LEFTMOTOR_FORWARD, LOW);
  digitalWrite(RIGHTMOTOR_BACKWARD, LOW);

  delay(durationFactor);
  
  digitalWrite(LEFTMOTOR_FORWARD, HIGH);
  digitalWrite(RIGHTMOTOR_FORWARD, HIGH);
  
  digitalWrite(LEFTMOTOR_FORWARD, LOW);
  digitalWrite(RIGHTMOTOR_BACKWARD, LOW);
}


#endif
