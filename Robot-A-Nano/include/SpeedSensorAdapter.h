#ifndef SPEEDSENSORADAPTER__H_
#define SPEEDSENSORADAPTER__H_

#include <Arduino.h>
#include "MyPins.h"
#include <neotimer.h>

unsigned long start_time = 0;
unsigned long end_time = 0;
long steps=0;
long steps_old=0;
long temp=0;
float rps=0;
int currentValue=0;

void SetupSpeedSensor()
{
	Serial.println("Setup Speed Sensor...");

	pinMode(SPEED_SENSOR_PIN,INPUT_PULLUP);
}

int digitize(int value, int threshold)
{
	if(value >= threshold) return 1;
	return 0;
}

void StartReadSpeedTimer()
{
		Serial.println("Start Speed Sensor Timer...");

	start_time=millis();
 	end_time=start_time+1000;
	currentValue = digitize(analogRead(SPEED_SENSOR_PIN), 500);
}

void ReadSpeedLoop(float& cmPerSec)
{
	int value = digitize(analogRead(SPEED_SENSOR_PIN), 500);

	if(currentValue != value)
	{
		steps++;
		currentValue = value;
		// Serial.println(steps);
	}

	if(millis() >= end_time)
	{
		temp=steps-steps_old;
		steps_old=steps;
		rps=(temp/20.0);

		// 2 * PI * Radius * RPS
		cmPerSec = 2 * PI * 3.5 * rps;

		// Reset
		start_time = millis();
		end_time=start_time+1000;
		// Serial.println("Done");
	}
}


#endif
