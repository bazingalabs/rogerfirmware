#include <SPI.h>
#include <RF12B.h>
#include <rf_packet.h>
#include "MemoryFree.h"
//RF12B * rf12b = RF12B::Instance();
//RF12B * rf12;
void setup() {
	
	Serial.begin(57600);
	RF12.begin();
	//rf12 = RF12B::Instance();
   // asm("cli");
	Serial.println("Booted");
}
byte buf[50];
int i = 0;
void loop() {
	if (Serial.available()>0) {
    ///Serial.println("AVAILABLE");
		char c = Serial.read();
		buf[i++] = c;
		if (c == '\n') {
			RF12.sendPacket(buf, i);
			buf[i+1] = '\0';
			Serial.print("Sent: ");
			Serial.println((char *)buf);
			i=0;
		}
	}
	if (RF12.packetAvailable()) {
		RFPacket p = RF12.recvPacket();
		p.dump();
		//free(p);
		Serial.print("freeMemory()=");
		    Serial.println(freeMemory());
	}
}


