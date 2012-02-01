#include <SPI.h>
#include <RF12B.h>
#include <rf_packet.h>
#include <EEPROM.h>
#include "console.h"
#include "MemoryFree.h"

#define BUFFER_SIZE 40
#define TIMEOUT 50
#define PRE_GUARD 1
#define RADIO 2
#define CC_CHECK 3
#define CONSOLE 4

int console_active=0;
int commandState = RADIO;
int last_pos=0;
byte buf[BUFFER_SIZE];
int i = 0;
int counter = 0;
unsigned long t = 0,s=0;
unsigned long seq = 0;
bool enterConsole = false;
bool exitConsole = false;

void setup() {
	pinMode(1, INPUT);
	Serial.begin(57600);
	RF12.begin();
	console.begin();
	t=millis();
	Serial.println("freeMem()=");
	Serial.println(freeMemory());
}


void loop() {
	if (enterConsole) {
		RF12.disableISR();
		console.printUsage();
		//Serial.flush();
		enterConsole = false;
		console_active = true;
		Serial.println("freeMem()=");
		Serial.println(freeMemory());
	}

	if (console_active) {
		console.show();
	}

	if (exitConsole) {
		exitConsole = false;
		RF12.enableISR();
		commandState = RADIO;
	}

	if (Serial.available()>0 && commandState != CONSOLE) {
		char c = Serial.read();
		buf[i++] = c;
		if (commandState == RADIO && millis()-t>1000) {
			commandState = PRE_GUARD;
			s = millis();
		} 
		if(commandState == PRE_GUARD && i >= 3 && millis() - s <1000
					&& buf[i-3] == '+'
					&& buf[i-2] == '+'
					&& buf[i-1] == '+' ) {
			commandState = CC_CHECK;
		} 

		if (millis()-s>1000) commandState = RADIO;
		
		t = millis();
	
	}

	if(commandState == CC_CHECK && millis()-t>1000) {
		commandState = CONSOLE;
		enterConsole = true;
	}

	if ((i >= BUFFER_SIZE || millis() - t > TIMEOUT) && i > 0) {
		RFPacket packet(buf, i, 1, 1,2);
		RF12.send(packet, packet.size()); 
		i=0;
		t = millis();
	}

	if (RF12.packetAvailable()) {
		RFPacket p = RF12.recvPacket();
		if (p.valid()) {
			Serial.print(p);
		}
		Serial.println(counter++);
	}
	
}


