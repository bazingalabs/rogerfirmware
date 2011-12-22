#include <SPI.h>
#include "rf12b.h"

void setup() {
	Serial.begin(57600);
   // asm("cli");
	delay(100);
	portInit();
	rfInit();
    
  //  if (MODE) {
	FIFOReset();
    //}
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
			sendPacket(buf, i);
			buf[i+1] = '\0';
			Serial.print("Sent: ");
			Serial.println((char *)buf);
			i=0;
		}
	}
	if (packetAvailable()) {
		recvPacket();
	}
}


