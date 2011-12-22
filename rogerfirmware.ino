#include <SPI.h>
#include "rf12b.h"
//RF12B * rf12b = RF12B::Instance();
RF12B * rf12 = RF12B::Instance();
void setup() {
	Serial.begin(57600);
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
			rf12->sendPacket(buf, i);
			buf[i+1] = '\0';
			Serial.print("Sent: ");
			Serial.println((char *)buf);
			i=0;
		}
	}
	if (rf12->packetAvailable()) {
		rf12->recvPacket();
	}
}


