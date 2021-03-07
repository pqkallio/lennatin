IDIR = ./src
COVDIR = coverage
CC = avr-gcc
COV = lcov
HTMLGEN = genhtml
AVRDUDE = avrdude
OBJ_COPY = avr-objcopy
_DEPS = ringbuffer.h \
		morse.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
EXEC = lennatin
HEX = $(EXEC).hex

src = $(wildcard src/*.c) $(wildcard src/**/*.c)

obj = $(src:.c=.o)

CFLAGS = -Wall -Wsign-compare -Wextra -Wpedantic -g -I$(IDIR)
AVROBJFLAGS = -Os -DF_CPU=16000000UL
AVREXECFLAGS = -mmcu=atmega328p
OBJCOPYFLAGS = -O ihex -R .eeprom
AVRDUDEFLAGS = -F -V -c arduino -p ATMEGA328P -b 115200

src/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(AVROBJFLAGS) $(AVREXECFLAGS)

$(EXEC): $(obj) $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) $(AVREXECFLAGS)

hex: $(EXEC)
	$(OBJ_COPY) $(OBJCOPYFLAGS) $(EXEC) $(HEX)

.PHONY: upload clean

upload: $(HEX)
	$(AVRDUDE) $(AVRDUDEFLAGS) -P $(device) -U flash:w:$(HEX)

clean:
	rm -f $(obj) $(EXEC) $(HEX)
