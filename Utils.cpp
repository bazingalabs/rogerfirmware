#include "Utils.h"

const prog_uchar string_00[] PROGMEM = "Bazingalabs Roger Configuration\n";
const prog_uchar string_10[] PROGMEM = "Console Usage:\n";
const prog_uchar string_20[] PROGMEM = " channel <channel nr>[1-30] : Gets or sets channel on the current frequency\n";
const prog_uchar string_22[] PROGMEM = " baud <baudrate>[200-115200] : Gets or sets baudrate oof the chip\n";
const prog_uchar string_24[] PROGMEM = " panid <pan id>[0-254] : Gets or sets pan id of the module \n";

const prog_uchar string_30[] PROGMEM = "\n";
const prog_uchar string_50[] PROGMEM = "Debug methods:\n";
const prog_uchar string_60[] PROGMEM = " pin    <pin>        : makes it input and read target pin\n";
//const prog_uchar string_70[] PROGMEM = " write   <pin> <value>: makes it output and write value to desired pin\n";
//const prog_uchar string_80[] PROGMEM = " delay   <msecond>    : Waits specified miliseconds\n";
//const prog_uchar string_90[] PROGMEM = " pulse   <pin> <val> <msecond>: Square pulse\n";
//const prog_uchar string_100[] PROGMEM = " pwm     <pin> <value>: Arrages voltage value to given pin by PWM\n";
const prog_uchar string_110[] PROGMEM = " apin  <pin>	      : Reads from analog input \n";
//const prog_uchar string_120[] PROGMEM = " echo    <str>        : Show str to screen\n";
const prog_uchar string_130[] PROGMEM = " quit | exit          : Exit\n";


void PROGMEMprint(const prog_uchar str[])
{
  char c;
  if(!str) return;
  while((c = pgm_read_byte(str++)))
    Serial.print(c);
}

void printConsoleHelp() {
	PROGMEMprint(string_00);
	PROGMEMprint(string_10);
	PROGMEMprint(string_20);
	PROGMEMprint(string_22);
	PROGMEMprint(string_24);
	PROGMEMprint(string_30);
	//PROGMEMprint(string_40);
	PROGMEMprint(string_50);
	PROGMEMprint(string_60);
/*	PROGMEMprint(string_70);
	PROGMEMprint(string_80);
	PROGMEMprint(string_90);
	PROGMEMprint(string_100);*/
	PROGMEMprint(string_110);
//	PROGMEMprint(string_120);
	PROGMEMprint(string_130);
}

void handleConsole() {
	while ( console.available() ) {

		if (console.checkString("channel")) {
			if (console.available()) {
				int channel = console.readInt();
				RF12.setChannel(channel);
			} else {
				Serial.print("Channel: ");
				Serial.println(RF12.getChannel());	
			}
		}

		if (console.checkString("datarate")) {
			if (console.available()) {
				int datarate = console.readInt();
				RF12.setDatarate(datarate);
			} else {
				Serial.print("Datarate: ");
				Serial.println(RF12.getDatarate());	
			}
		}

		if (console.checkString("panid")) {
			if (console.available()) {
				int panid = console.readInt();
				RF12.setPanID(panid);
			} else {
				Serial.print("Pan ID: ");
				Serial.println(RF12.getPanID());	
			}
		}

		if (console.checkString("pin")) {
			int pin = console.readInt();
			if (console.available()) {
				int val = console.readInt();
				pinMode(pin,OUTPUT);
				digitalWrite(pin, val);
			} else {
				pinMode(pin,INPUT);
				Serial.print("Pin: ");
				Serial.print(pin);
				Serial.print(" value: ");
				Serial.println(digitalRead(pin));	
			}
		}

		if (console.checkString("apin")) {
			int pin = console.readInt();
			if (console.available()) {
				int val = console.readInt();
				pinMode(pin,OUTPUT);
				analogWrite(pin, val);
			} else {
				pinMode(pin,INPUT);
				Serial.print("Pin: ");
				Serial.print(pin);
				Serial.print(" value: ");
				Serial.println(analogRead(pin));	
			}
		}

		if (console.checkString("quit") || console.checkString("exit")) {
			Serial.println("Exit configuration");
			consoleActive = false;
			commandState = RADIO;
		}

		console.readChar();
	}
}