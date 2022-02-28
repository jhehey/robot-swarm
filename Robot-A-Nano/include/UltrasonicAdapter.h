#ifndef __ULTRASONICADAPTER_H__
#define __ULTRASONICADAPTER_H__

#include <Ultrasonic.h>
#include "MyPins.h"

Ultrasonic ultrasonic(ULTRASONIC_TRIG, ULTRASONIC_ECHO);

unsigned int ReadUltrasonic(){
	return ultrasonic.read(CM);
}

#endif
