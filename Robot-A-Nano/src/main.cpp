#include <Arduino.h>
#include <neotimer.h>
#include "RF24Address.h"
#include "RF24NetworkAdapter.h"
#include "UltrasonicAdapter.h"
#include "CompassAdapter.h"
#include "MotorAdapter.h"
#include "ServoAdapter.h"
#include "SpeedSensorAdapter.h"

Neotimer sensorReadingTimer;

unsigned int distanceCM;
int compassX, compassY, compassZ;
float headingDegrees;
float speedCmPerSec;

void handleMessageReceived(char* message);
void handleReadSensor();
void handleCommand(const char* command);
void tester();
void tester2();

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
	Serial.println("Setup Robot A - Arduino Nano...");

	SetupRF24Network(ROBOT_NODE_A, handleMessageReceived);
	SetupMotor();
	SetupServo();
	SetupCompass();
	SetupSpeedSensor();
	StartReadSpeedTimer();
	sensorReadingTimer.set(3000);
}

void loop() {
	Serial.println("Loop Start");

	UpdateRF24Network();
	ServoScanLoop();
	ReadSpeedLoop(speedCmPerSec);

	if(sensorReadingTimer.repeat()) {
		handleReadSensor();
	}


	tester();
	// tester2();
}

void handleMessageReceived(char* message)
{
	Serial.print("Main - Received Message: ");
	Serial.println(message);
	handleCommand(message);
}

char mainBuffer[MAX_PAYLOAD_SIZE];

void handleReadSensor() {
	// Ultrasonic
	distanceCM = ReadUltrasonic();
	
	// Compass
	ReadCompass(compassX, compassY, compassZ, headingDegrees);

	// Speed Sensor
	// ReadSpeed(speedRps);

	String toSend = String(distanceCM) + ',' + 
		String(compassX) + ',' +
		String(compassY) + ',' +
		String(compassZ) + ',' +
		String(headingDegrees) + ',' + 
		String(speedCmPerSec);

	// Serial.print("ToSend: ");
	// Serial.println(toSend);
	toSend.toCharArray(mainBuffer, MAX_PAYLOAD_SIZE);
	SendMessage(MASTER_NODE, mainBuffer);
}

#pragma region Test Code

void tester() {
	if(Serial.available() > 0){
		char ch = Serial.read();
		Serial.println(ch);
		Serial.flush();

		String hehe = String(ch);
		handleCommand(hehe.c_str());
	}
}

void tester2() {
	distanceCM = ReadUltrasonic();
	Serial.print("Tester 2: ");
	Serial.println(distanceCM);

	if(distanceCM < 15  || distanceCM > 300) {
		Serial.println("Obstacle Detected");
		Serial.println("MoveBackward");
		MoveBackward();
		delay(1000);

		Serial.println("TurnRight");
		TurnRight();
		delay(1000);
	}

	Serial.println("MoveForward");
	MoveForward();
	// handleCommand("4");
	// delay(3000);

	// handleCommand("7");
	// delay(2000);

	// handleCommand("5");
	// delay(2000);

	// handleCommand("6");
	// delay(2000);

	// handleCommand("4");
	// delay(3000);
}

void handleCommand(const char* command){
	Serial.print("Handle Command: ");
	Serial.println(command);
	if(strcmp(command, "1") == 0) {
		Serial.println("Start Servo Scan");
		ServoScanStart();
	}
	else if (strcmp(command, "2") == 0) {
		Serial.println("Stop Servo Scan");
		ServoScanStop();
	}
	else if (strcmp(command, "3") == 0) {
		Serial.println("Read and Send");
		handleReadSensor();
	}
	else if (strcmp(command, "4") == 0) {
		Serial.println("MoveForward");
		MoveForward();
	}
	else if (strcmp(command, "5") == 0) {
		Serial.println("MoveBackward");
		MoveBackward();
	}
	else if (strcmp(command, "6") == 0) {
		Serial.println("TurnLeft");
		TurnLeft();
	}
	else if (strcmp(command, "7") == 0) {
		Serial.println("TurnRight");
		TurnRight();
	}
	else if (strcmp(command, "8") == 0) {
		Serial.println("StopMotor");
		StopMotor();
	}
}


#pragma endregion
