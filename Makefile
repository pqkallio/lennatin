.PHONY: build upload

build:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o lennatin.o main.c
	avr-gcc -mmcu=atmega328p lennatin.o -o lennatin
	avr-objcopy -O ihex -R .eeprom lennatin lennatin.hex

upload:
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM1 -b 115200 -U flash:w:lennatin.hex
