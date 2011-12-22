#ifndef RF12B_H
#define RF12B_H


#include "CircularBuffer.h"
#include "stdint.h"
#include <SPI.h>
#include "Arduino.h"
#include "rf12b_def.h"


class RF12B {
	public:
		void portInit();
		void rfInit() ;
		void rfSend(unsigned char data);
		boolean packetAvailable();
		boolean rfAvailable();
	    void rxISR();
		byte rfRecv();
		void FIFOReset();
		void sendPacket(byte * buf, byte length);
		void recvPacket();
		unsigned int writeCmd(unsigned int cmd);
		void changeMode(int _mode);
		unsigned char crc8(unsigned char crc, unsigned char data);
		unsigned int status();
		static void callbackISR();
		static RF12B* Instance();
		
	private:
		RF12B();
	    RF12B (RF12B const&);
	    RF12B& operator=( RF12B const&) { return *this; }
		static RF12B* m_pInstance;
		int mode;
		boolean rfa;
		byte remaining;
		byte state;
		boolean packet_received;
		CircularBuffer<byte,50> recv_buffer;
};
void rxISRFunc();
#endif