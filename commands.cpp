#include "console.h"
//--------------------------------------------------------------------
// COMMANDS
//---------------------------------------------------------------------

const prog_uchar string_00[] PROGMEM = "Bazingalabs Roger Configuration\n";   // "String 0" etc are strings to store - change to suit.
const prog_uchar string_10[] PROGMEM = "Console Usage:\n";
const prog_uchar string_20[] PROGMEM = " channel <channel nr> : Changes the channel on the current frequency\n";
const prog_uchar string_30[] PROGMEM = "\n";
const prog_uchar string_40[] PROGMEM = "Console Usage:\n";
const prog_uchar string_50[] PROGMEM = "Debug methods:\n";
const prog_uchar string_60[] PROGMEM = " read    <pin>        : makes it input and read target pin\n";
const prog_uchar string_70[] PROGMEM = " write   <pin> <value>: makes it output and write value to desired pin\n";
const prog_uchar string_80[] PROGMEM = " delay   <msecond>    : Waits specified miliseconds\n";
const prog_uchar string_90[] PROGMEM = " pulse   <pin> <val> <msecond>: Square pulse\n";
const prog_uchar string_100[] PROGMEM = " pwm     <pin> <value>: Arrages voltage value to given pin by PWM\n";
const prog_uchar string_110[] PROGMEM = " anread  <pin>	      : Reads from analog input \n";
const prog_uchar string_120[] PROGMEM = " echo    <str>        : Show str to screen\n";
const prog_uchar string_130[] PROGMEM = " quit | exit          : Exit\n";
 
void PROGMEMprint(const prog_uchar str[])
{
  char c;
  if(!str) return;
  while((c = pgm_read_byte(str++)))
    Serial.print(c);
}

void usage() {
	PROGMEMprint(string_00);
	PROGMEMprint(string_10);
	PROGMEMprint(string_20);
	PROGMEMprint(string_30);
	PROGMEMprint(string_40);
	PROGMEMprint(string_50);
	PROGMEMprint(string_60);
	PROGMEMprint(string_70);
	PROGMEMprint(string_80);
	PROGMEMprint(string_90);
	PROGMEMprint(string_100);
	PROGMEMprint(string_110);
	PROGMEMprint(string_120);
	PROGMEMprint(string_130);
}


int quit(char* a,char* b,char* c)
{
	Serial.println("Leaving configure mode...");
	console_active = 0;
	exitConsole = true;
	return 0;
}

int channel(char* A,char* b,char* c)
{
	int a = fatoi(A);
	RF12.setChannel(a);
	Serial.println("");
	Serial.print("Channel: ");
	Serial.print(a);
	return 0;
}

int read(char* A,char* b,char* c)
{
	int a = fatoi(A);
	pinMode(a,INPUT);
	int dig=digitalRead(a);
	Serial.println("");
	Serial.print("Digital pin ");
	Serial.print(a);
	Serial.print(" :");
	Serial.println(dig);
	return dig;
}

int echo(char* a,char* b,char* c)
{
	Serial.println("");
	Serial.print(a);
	Serial.print(" ");
	Serial.print(b);
	Serial.print(" ");
	Serial.println(c);
	return 0;
}

int write(char* A,char* B,char* c)
{
	int a = fatoi(A);
	int b = fatoi(B);
	pinMode(a,OUTPUT);
	digitalWrite(a,b);
	Serial.println("");
	Serial.print("Write to pin ");
	Serial.print(a);
	Serial.print(" :");
	Serial.println(b);
	return 0;
}

int indelay(char* A,char* b,char* c)
{
	int a = fatoi(A);
	Serial.println("");
	Serial.print("Wait for ");
	Serial.print(a);
	Serial.println(" usec ");
	delay(a);
	return 0;
}

int pwm(char* A,char* B,char* c)
{
	int a = fatoi(A);
	int b = fatoi(B);
	pinMode(a,OUTPUT);
	analogWrite(a,b);
	Serial.println("");
	Serial.print("Write analog pin ");
	Serial.print(a);
	Serial.print(" :");
	Serial.println(b);
	return 0;
}


int pulse(char* A,char* B,char* C)
{
	int a = fatoi(A);
	int b = fatoi(B);
	int c = fatoi(C);
	pinMode(a,OUTPUT);
	digitalWrite(a,b);
	Serial.println("");
	Serial.print("Pulse pin ");
	Serial.print(a);
	Serial.print(" :");
	Serial.println(b);
	delay(c);
	digitalWrite(a,!b);
	return 0;
}


int anread(char* A,char* b,char* c)
{
	int a = fatoi(A);
	int an = analogRead(a);
	Serial.println("");
	Serial.print("Read from analog pin ");
	Serial.print(a);
	Serial.print(" :");
	Serial.println(an);
	return an;
}

int invalid(char* a,char* b,char* c)
{
		Serial.println("");
		Serial.print("Invalid Command");
        return 0;
}
