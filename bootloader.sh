#!/bin/bash

PORT="usb"

PART="atmega328p"

BAUD="57600"

PROG="usbasp"

avrdude -c$PROG -P$PORT -p$PART -b$BAUD -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0x07:m -U lock:w:0x3F:m -U flash:w:ATmegaBOOT_168_atmega328_pro_8MHz.hex:i -U lock:w:0x0F:m

#avrdude -P$PORT -p$PART -B$BAUD -U lock:w:0x0F:m