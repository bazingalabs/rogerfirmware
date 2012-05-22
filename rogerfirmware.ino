#include <SPI.h>
#include <RF12B.h>
#include <rf_packet.h>
#include <EEPROM.h>
#include "Utils.h"
#include <Messenger.h>
//#include <MemoryFree.h>
#include "CircularBuffer.h"
#include "digitalWriteFast.h"


#define SERIAL_BUFFER_SIZE 200
#define TIMEOUT 50
#define PRE_GUARD 1
#define RADIO 2
#define CC_CHECK 3
#define CONSOLE 4
#define INPUT_PIN A0
#define OUTPUT_PIN A3

int console_active=0;
int commandState = RADIO;
int last_pos=0;
CircularBuffer<byte,200> buf;
int i = 0;
int counter = 0;
unsigned long t = 0,s=0;
unsigned long seq = 0;
bool enterConsole = false;
bool exitConsole = false;
bool consoleActive = false;
Messenger console = Messenger(); 
byte pin_state = 0;

void setup() {
	pinMode(1, INPUT);
	Serial.begin(57600);
	RF12.begin();
	console.attach(handleConsole);
	t=millis();
        RF12.setFrequency(433);
        RF12.setDatarate(57600);
        
        // Add reset capability
        // Pin D0 as input and Pin D3 as output (for compatibility with arduino fio) 
        pinMode(INPUT_PIN,INPUT);
        pinMode(OUTPUT_PIN,OUTPUT);
        pin_state = digitalRead(INPUT_PIN);
	
}

void loop() {
        if(pin_state != digitalReadFast(INPUT_PIN)) {
            RFPacket packet(&pin_state, 1, 1, 1,PIN_CHANGE);
            RF12.send(packet, packet.size()); 
            pin_state = digitalRead(INPUT_PIN);
        }
	if (enterConsole) {
		RF12.disableISR();
		printConsoleHelp();
		//Serial.flush();
		enterConsole = false;
		consoleActive = true;
		//Serial.println("freeMem()=");
		//Serial.println(freeMemory());
	}

	if (consoleActive) {
		if ( Serial.available() ) console.process(Serial.read ());
	}

	if (exitConsole) {
		exitConsole = false;
		RF12.enableISR();
		commandState = RADIO;
	}

	if (Serial.available()>0 && commandState != CONSOLE) {
		byte c = Serial.read();
		//buf[i++] = c;
                buf.push((byte)c);
                //Serial.println("Buffer size:");
                //Serial.println(buf.remain(),DEC);
		if (commandState == RADIO && millis()-t>1000) {
			commandState = PRE_GUARD;
			s = millis();
		} 
		/*if(commandState == PRE_GUARD && i >= 3 && millis() - s <1000
					&& buf[i-3] == '+'
					&& buf[i-2] == '+'
					&& buf[i-1] == '+' ) {
			commandState = CC_CHECK;
		} */

		if (millis()-s>1000) commandState = RADIO;
		
		t = millis();
	
	}

	if(commandState == CC_CHECK && millis()-t>1000) {
		commandState = CONSOLE;
		enterConsole = true;
	}

	if ((buf.remain() >= SERIAL_BUFFER_SIZE || millis() - t > TIMEOUT) && buf.remain() > 0) {
		RFPacket packet(&buf, buf.remain(), 1, 1,DATA_PACKET);
		RF12.send(packet, packet.size()); 
		i=0;
		t = millis();
	}

	if (RF12.packetAvailable()) {
		RFPacket p = RF12.recvPacket();
		if (p.valid()) {
                     switch(p.getType()) {
                        case PIN_CHANGE:
                            digitalWriteFast(OUTPUT_PIN, !(*p.getData()));
                        break;
                        case DATA_PACKET:
                            Serial.write(p.getData(), p.dataSize());
                        break;
                     }
		}
		//Serial.println(counter++);
	}
	
}


