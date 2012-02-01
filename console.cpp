#include "console.h"

Actioner actioner;
Console console;

void Console::begin() {
	actioner.def = invalid; // Default command , it may be usage 
	actioner.addCommand("channel",channel);
	actioner.addCommand("read",read);
	actioner.addCommand("write",write);
	actioner.addCommand("delay",indelay);
	actioner.addCommand("pwm",pwm);
	actioner.addCommand("anread",anread);
	actioner.addCommand("echo",echo);
	actioner.addCommand("pulse",pulse);
	actioner.addCommand("quit",quit);
	actioner.addCommand("exit",quit); // Alias
}