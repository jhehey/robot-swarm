#include <Arduino.h>
#include "RF24NetworkAdapter.h"
#include "RF24Address.h"
#include <neotimer.h>

Neotimer testTimer;

void handleMessageReceived(char* message);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
	Serial.println("Setup Robot B - Arduino Nano...");

	SetupRF24Network(ROBOT_NODE_B, handleMessageReceived);

	testTimer.set(1000);
}

void loop() {
	UpdateRF24Network();

  // put your main code here, to run repeatedly:
	if(testTimer.repeat()) {
		Serial.print("Hello from Robot B");
		Serial.println(millis());
		SendMessage(MASTER_NODE, "Hello from Robot B");
	}
}

void handleMessageReceived(char* message)
{
	Serial.print("Main - Received Message: ");
	Serial.println(message);
}
