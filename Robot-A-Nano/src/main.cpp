#include <Arduino.h>
#include "RF24NetworkAdapter.h"
#include "RF24Address.h"
#include <neotimer.h>

Neotimer testTimer;

void handleMessageReceived(char* message);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
	Serial.println("Setup Robot A - Arduino Nano...");

	SetupRF24Network(ROBOT_NODE_A, handleMessageReceived);

	testTimer.set(1000);
}

void loop() {
	UpdateRF24Network();

  // put your main code here, to run repeatedly:
	if(testTimer.repeat()) {
		Serial.print("Hello from Robot A");
		Serial.println(millis());
		SendMessage(MASTER_NODE, "Hello from Robot A");
	}
}

void handleMessageReceived(char* message)
{
	Serial.print("Main - Received Message: ");
	Serial.println(message);
}
