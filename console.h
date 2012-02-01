#ifndef CONSOLE_H
#define CONSOLE_H

#include <Arduino.h>
#include <EEPROM.h>
#include "Utils.h"
//#include "VSPDE.h"
#include "commands.h"
#include <RF12B.h>
#include "MemoryFree.h"
#include <avr/pgmspace.h>

class Actioner
{
public:
	char commands[12][10];
	int(*funcs[12])(char*,char*,char*);
	int (*def)(char*,char*,char*);
	int count;
	int mode; // 0 console mode 1 programming mode
	Actioner()
	{
		count = 0;
		mode = 0;
	}
	
	void addCommand(char* s,int (*func)(char*,char*,char*))
	{
		funcs[count]= func;
		fstrcpy(s,commands[count]);
		//Information messages that shows which commands added
		//Serial.print("Command added:");
		//Serial.println(s);
		count++;
	}


	int getCommand(char* s)
	{
		int i; 
		for(i=0;i<count ;i++)
		{
			if (fstricmp(commands[i],s)) // Case intensitive
				return i;
		}
		return -1;
	}


	int action(char* s,char* a,char* b,char* c)
	{
		int cmd = getCommand(s);
		if (cmd >= 0)
			return funcs[cmd](a,b,c);
		else
			return def(a,b,c);
	}

	char command[20],param1[10],param2[10],param3[10];
	int run(char* s)
	{
		fstrcpy( fstrtok(s,' '),command);
		fstrcpy(fstrtok(NULL,' '),param1);
		fstrcpy(fstrtok(NULL,' '),param2);
		fstrcpy(fstrtok(NULL,' '),param3);
		return action(command,param1,param2,param3);
	}
};


extern Actioner actioner; 

class Console
{
public:
void begin();


int printUsage()
{

	usage();
	Serial.print("#");
	return 0;
}


void show()
{
 
  int i;
  char line[200],ch='a';
  for(i=0;ch!=13&&ch!=10&&i<200&&ch!=0;) // Read until Enter , line max 200 characters
    while ( ch!=13 && ch!=10 && ch!=0) // Windows & Arduino together
    {
		// Read from EEPROM or user input depend on state
		if (!Serial.available())  break;
			else
			ch=line[i++] = Serial.read();


		switch (ch)
		{
		case 9: //TAB
		printUsage();
		case 10: //Enter 
		case 13:
                i--;
                break;
		case 127: //BACKSPACE
		i-=2; // Two character one backspace one target char
        Serial.print((char)127);
		break;

		default:
		Serial.print(ch);
		}
    }
	line[i]=0;
	
	actioner.run(line);
	Serial.println("freeMem()=");
	Serial.println(freeMemory());
	Serial.println("");

	Serial.print("#");

		
}

Console()
{

}


};

extern Console console;

#endif
