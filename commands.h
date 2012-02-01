#ifndef COMMANDS_H
#define COMMANDS_H

#include "console.h"
//--------------------------------------------------------------------
// COMMANDS
//---------------------------------------------------------------------
extern int console_active;
extern int program_mode;
extern int last_pos;
extern int eeprom_source;
extern int eeprom_pos;
extern bool exitConsole;


int quit(char* a,char* b,char* c);
int read(char* A,char* b,char* c);
int echo(char* a,char* b,char* c);
int channel(char* a,char* b,char* c);

void usage();
int write(char* A,char* B,char* c);

int indelay(char* A,char* b,char* c);

int pwm(char* A,char* B,char* c);


int pulse(char* A,char* B,char* C);


int anread(char* A,char* b,char* c);

int invalid(char* a,char* b,char* c);

#endif