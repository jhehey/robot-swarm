#include <Arduino.h>
#include <neotimer.h>
#include "RF24NetworkAdapter.h"
#include "RF24Address.h"
#include "MotorAdapter.h"
#include "CompassAdapter.h"
#include "UltrasonicAdapter.h"
#include "ServoAdapter.h"

Neotimer testTimer;
Neotimer sensorReadingTimer;

void handleMessageReceived(char* message);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
	Serial.println("Setup Robot A - Arduino Nano...");

	SetupRF24Network(ROBOT_NODE_A, handleMessageReceived);
	SetupMotor();
	SetupServo();
	SetupCompass();

	sensorReadingTimer.set(1000);
}

void loop() {
	UpdateRF24Network();

  // put your main code here, to run repeatedly:
	if(testTimer.repeat()) {
		// Serial.print("Hello from Robot A");
		// Serial.println(millis());
		// SendMessage(MASTER_NODE, "Hello from Robot A");

		// Serial.print("Sensor 02: ");
		// Serial.print(ultrasonic.read(CM)); // Prints the distance making the unit explicit
		// Serial.println("cm");
	}

	if(sensorReadingTimer.repeat()) {
		OnSensorReading_TimedEvent();
	}
}

void handleMessageReceived(char* message)
{
	Serial.print("Main - Received Message: ");
	Serial.println(message);
}


void OnSensorReading_TimedEvent() {
	// Ultrasonic
	unsigned int distanceCM = ReadUltrasonic();
	
	// Compass
	int x, y, z;
	float headingDegress;
	ReadCompass(x, y, z, headingDegress);

	// TODO: Speed Sensor


}
