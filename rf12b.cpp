#include "CircularBuffer.h"
#include "rf12b.h"


int mode = RX;
boolean rfa = false;
byte remaining = 0;
byte state = STATE_LENGTH;
boolean packet_received = false;

CircularBuffer<byte,50> recv_buffer = CircularBuffer<byte,50>();
void portInit() {
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV8);
	SPI.setDataMode(SPI_MODE0);
}

void rfInit() {
	pinMode(NIRQ_PIN, INPUT);
	pinMode(nFFS_PIN, INPUT);
  
	writeCmd(0x80E7); //EL,EF,868band,12.0pF
    //if (MODE) {
	writeCmd(0x8299); //er,!ebb,ET,ES,EX,!eb,!ew,DC // receive
    //} else {
    //  writeCmd(0x8239); //!er,!ebb,ET,ES,EX,!eb,!ew,DC
    //}
	writeCmd(0xA640); //frequency select
	writeCmd(0xC647); //4.8kbps
	writeCmd(0x94A0); //VDI,FAST,134kHz,0dBm,-103dBm
	writeCmd(0xC2AC); //AL,!ml,DIG,DQD4
	writeCmd(0xCA81); //FIFO8,SYNC,!ff,DR
	writeCmd(0xCED4); //SYNC=2DD4
	writeCmd(0xC483); //@PWR,NO RSTRIC,!st,!fi,OE,EN
	writeCmd(0x9850); //!mp,90kHz,MAX OUT
	writeCmd(0xCC17); //OB1, COB0, LPX, Iddy, CDDITCBW0
	writeCmd(0xE000); //NOT USED
	writeCmd(0xC800); //NOT USED
	writeCmd(0xC040); //1.66MHz,2.2V
	//attachInterrupt(0, rxISR,FALLING);
	attachInterrupt(1, rxISR,RISING);
}

void rfSend(unsigned char data){
	while(digitalRead(NIRQ_PIN) == HIGH);
	writeCmd(0xB800 + data);
}
boolean packetAvailable() {
	return packet_received; 
}
boolean rfAvailable() {
    //Serial.print("REMAIN: ");
    //Serial.println(recv_buffer.remain());
	return recv_buffer.remain();
}
  
void rxISR() {
    
	unsigned int data;
	if (mode == RX) {
      //Serial.println("DATA");
		switch (state) {
			case STATE_LENGTH:
			for(int i=0;i<16;i++) {
				if ( (writeCmd(0x0000)&0x8000) ) {
					remaining = writeCmd(0xB000)&0x00FF;
					recv_buffer.push(remaining);
					state = READ_DATA;
				}
			}
			break;
			case READ_DATA:
			for(int i=0;i<16;i++) {
				if ( (writeCmd(0x0000)&0x8000) ) {
					recv_buffer.push(writeCmd(0xB000)&0x00FF);
					remaining--;
				}
			}
			if (remaining <= 0) {
				packet_received = true;
				state = STATE_LENGTH;
				FIFOReset();
			}
			break;
          
		}
	}
    
}
  
byte rfRecv() {
	return recv_buffer.pop();
}

void FIFOReset() {
	writeCmd(0xCA81);
	writeCmd(0xCA83);
}


void sendPacket(byte * buf, byte length) {
	changeMode(TX);
	byte crc = 0;
  
	writeCmd(0x0000);
	rfSend(0xAA); // PREAMBLE
	rfSend(0xAA);
	rfSend(0xAA);
	rfSend(0x2D); // SYNC
	rfSend(0xD4);

	rfSend(length+1);
	crc = crc8(crc, length+1);
      
	for(int i=0; i<length; i++) {
		rfSend(buf[i]);
		crc = crc8(crc, buf[i]);
	}
	rfSend(crc);
      
	rfSend(0xAA); // DUMMY BYTES
	rfSend(0xAA);
	rfSend(0xAA);
      
      /* Back to receiver mode */
	changeMode(RX);
	delay(10);
	status();
      
}
  
  
void recvPacket() {
	byte crc = 0;
	int data = 0;
	int length = rfRecv();
	if (length == -1 && length < 0) return;
	crc = crc8(crc, length);
	Serial.print("PACKET START: ");
	Serial.print("LENGTH: ");
	Serial.println(length,DEC);
	for (int i=0; i<length-1; i++) {
		data = rfRecv()&0x00ff;
		crc = crc8(crc, data);
		Serial.print("DATA[");
		Serial.print(i);
		Serial.print("]: ");
		Serial.println((char)data);
	}
	Serial.print("CRC: ");
	byte recvCRC = rfRecv();
	Serial.println(recvCRC,DEC);
	Serial.print("CRC(calc): ");
	Serial.println(crc,DEC);
	if (crc == recvCRC) {
		Serial.println("PACKET VALID");
	} else {
		Serial.println("PACKET INVALID");
	}
	Serial.print("PACKET END: ");
  
	packet_received = false; 
}
  
  
unsigned int writeCmd(unsigned int cmd) {
	digitalWrite(CS_PIN,LOW);
	uint16_t reply = SPI.transfer(cmd >> 8) << 8;
	reply |= SPI.transfer(cmd);
	digitalWrite(CS_PIN,HIGH);

	return reply;
}

void changeMode(int _mode) {
	mode = _mode;
	if (_mode == TX) {
		writeCmd(0x8239); //!er,!ebb,ET,ES,EX,!eb,!ew,DC
	} else { /* mode == RX */
		writeCmd(0x8299); //er,!ebb,ET,ES,EX,!eb,!ew,DC
	}
}

unsigned char crc8(unsigned char crc, unsigned char data) {
	crc = crc ^ data;
	for (int i = 0; i < 8; i++) {
		if (crc & 0x01) {
			crc = (crc >> 1) ^ 0x8C;
		} else {
			crc >>= 1;
		}
	}
	return crc;
}

unsigned int status() {
	return writeCmd(0x0000);
}
