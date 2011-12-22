#ifndef RF12B_H
#define RF12B_H


#include "CircularBuffer.h"
#include "stdint.h"
#include <SPI.h>
#include "Arduino.h"



#define TX 1
#define RX 0
#define CS_PIN 10
#define NIRQ_PIN 2
#define nFFS_PIN 3
#define STATE_LENGTH 1
#define READ_DATA 2

void portInit();
void rfInit() ;

void rfSend(unsigned char data);
boolean packetAvailable() ;
boolean rfAvailable();
  
void rxISR() ;
  
byte rfRecv() ;

void FIFOReset();

void sendPacket(byte * buf, byte length) ;
  
  
void recvPacket() ;
  
  
unsigned int writeCmd(unsigned int cmd) ;

void changeMode(int _mode) ;

unsigned char crc8(unsigned char crc, unsigned char data);

unsigned int status() ;

#endif