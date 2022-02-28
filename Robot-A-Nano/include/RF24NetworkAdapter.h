#ifndef __RF24NETWORKADAPTER_H__
#define	__RF24NETWORKADAPTER_H__

#include <avr/pgmspace.h>
#include "printf.h"
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include "MyPins.h"

#define DEBUG_MODE

/***********************************************************************
************* Set the Node Address *************************************
/***********************************************************************/

// These are the Octal addresses that will be assigned
const uint16_t node_address_set[5] = { 00, 01, 02, 03, 04 };

// 0 = Master
// 1-4 (01, 02, 03, 04)   = Children of Master(00)

/***********************************************************************/
/***********************************************************************/

RF24 radio(RFNETWORK_CE, RFNETWORK_CS);                           // CE & CS pins to use (Using 7,8 on Uno,Nano)
RF24Network network(radio);
 
const uint8_t radioChannel = 100;						// Channel for all nodes in the network
uint16_t thisNode;                          // Our node address
char dataBuffer[MAX_PAYLOAD_SIZE];					// Default payload size is 144 bytes (RF24Network_config.h)

typedef void (*receiveCallback_t)(char* message);								// Function to call when a message is received
receiveCallback_t receiveMessageCallback;

bool SendMessage(uint8_t to, const char* message);
void ReceiveMessage(RF24NetworkHeader& header, uint16_t& payloadSize);


void SetupRF24Network(uint8_t address, receiveCallback_t receiveCallback) // TODO: pass callback
{
	printf_begin(); // needed for RF24* libs' internal printf() calls
	while (!Serial) {
    // some boards need this because of native USB capability
  }
  Serial.println(F("Setup RF24Network..."));
 
  thisNode = node_address_set[address];            // Which node are we?
	receiveMessageCallback = receiveCallback;

	if (!radio.begin()) {
    Serial.println("RF24 - Radio hardware not responding, recheck connections and restart...");
    while (1) {
      // hold in infinite loop
    }
  }

	radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(radioChannel);
  network.begin(/*node address*/ thisNode);
  Serial.println("RF24 - Radio setup successful...");
}

void UpdateRF24Network()
{
	network.update();
	while(network.available()) {
		RF24NetworkHeader header; 
		uint16_t payloadSize = network.peek(header);
		ReceiveMessage(header, payloadSize);
	}
}

bool SendMessage(uint8_t to, const char* message)
{
	// find the address of receiver node
	uint16_t receiver = node_address_set[to];

	// put message to the buffer
	sprintf(dataBuffer, "%s", message);

	// write to the network
	RF24NetworkHeader header(receiver);
	bool ok = network.write(header, &dataBuffer, MAX_PAYLOAD_SIZE);
	if(!ok) {
		Serial.println("RF24 - Error in writing to the network...");
	}

	#if defined(DEBUG_MODE)
		Serial.print("RF24 - Send Message - to: ");
		Serial.print(receiver);
		Serial.print(" msg: ");
		Serial.println(dataBuffer);
	#endif
}

void ReceiveMessage(RF24NetworkHeader& header, uint16_t& payloadSize)
{
	network.read(header, &dataBuffer, payloadSize);

	#if defined(DEBUG_MODE)
		Serial.print("RF24 - Received Message: ");
		Serial.println(dataBuffer);
	#endif

	receiveMessageCallback(dataBuffer);
}



#endif
