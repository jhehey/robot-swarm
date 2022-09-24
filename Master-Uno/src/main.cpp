#include <Arduino.h>
#include "RF24NetworkAdapter.h"
#include "RF24Address.h"
#include <neotimer.h>

Neotimer testTimer;

void handleMessageReceived(char* message);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
	Serial.println("Setup Master - Arduino Uno...");

	SetupRF24Network(MASTER_NODE, handleMessageReceived);

	testTimer.set(1000);
}

void loop() {
	UpdateRF24Network();

	if(Serial.available() > 0){
		char ch = Serial.read();
		Serial.println(ch);
		SendMessage(ROBOT_NODE_A, &ch);
		// SendMessage(ROBOT_NODE_B, &ch);
		Serial.flush();
	}

  // // put your main code here, to run repeatedly:
	// if(testTimer.repeat()) {
	// 	Serial.print("Hello from Master");
	// 	Serial.println(millis());
	// 	SendMessage(ROBOT_NODE_A, "Hello from Master");
	// 	SendMessage(ROBOT_NODE_B, "Hello from Master");
	// }
}

void handleMessageReceived(char* message)
{
	// Serial.print("Main - Received Message: ");
	// Serial.println(message);
}
