# Firmware for the Bazingalabs Roger
This is the firmware for the Bazingalabs Roger board  
The board uses a RF12B from Hoperf (http://www.hoperf.com)  
The board has a XBee compatible footprint and should fit into any existing   
XBee sockets like for example an Arduino FIO or XBee explorer.  
![Bazingalabs Roger](http://store.bazingalabs.com/spree/products/39/small/ROGER.jpg?1349897475 "Bazingalabs Roger]" =150x150)

## Documentation
For a complete command reference see the wiki  
https://github.com/bazingalabs/rogerfirmware/wiki  

For documentation on the RF12B library check the wiki https://github.com/bazingalabs/RF12B/wiki

## Features
The modules is available in three flavours  

- 434MHz
- 868MHz
- 915MHz

Easy configuration  

The module act as a wireless serial connection and work right out of the box  
 
## Configure the module
To set certain parameters of the module like base frequency, channel, panid or id use the following steps:

1. Insert your Roger module into a Proger.
2. Open up a serial console (like the one from the Arduino IDE)
3. Enter +++
4. You should now see a welcome message and a command list
5. Execute the commands as displayed in the command list e.g. channel 2 to set the channel to 2


## Development setup
To get ready for development follow the following steps

## Prerequisits
* Arduino ide http://arduino.cc/en/Main/Software
* RF12B Library https://github.com/bazingalabs/RF12B
* Modified Messenger library https://github.com/bazingalabs/Messenger

Follow the necessary steps on the websites linked

## Install steps 
1. Go to your arduino projects directory
2. Clone the repository
<code>git clone git@github.com:bazingalabs/rogerfirmware.git</code>
3. Open rogerfimware.ino inside Arduino IDE
4. Now you can hack all you like

