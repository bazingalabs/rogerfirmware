
#ifndef UTILS_H
#define UTILS_H
#define RADIO 2
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "Messenger.h"
#include "RF12B.h"
	void printConsoleHelp();
	void PROGMEMprint(const prog_uchar str[]);
	extern Messenger console;
	extern bool consoleActive;
	extern int commandState;
	void handleConsole();
#endif