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
TESTER = tester

src = $(wildcard src/*.c) $(wildcard src/**/*.c)

test_files = $(wildcard test/*.c)
test = $(test_files) $(filter-out src/main.c, $(src))

obj = $(src:.c=.o)
test_files_obj = $(test_files:.c=.o)
test_obj = $(test:.c=.o)
coverage_files = $(wildcard *.gcda) $(wildcard *.gcno) \
				$(wildcard src/*.gcda) $(wildcard src/*.gcno) $(wildcard src/**/*.gcda) $(wildcard src/**/*.gcno) \
				$(wildcard test/*.gcda) $(wildcard test/*.gcno) $(wildcard test/**/*.gcda) $(wildcard test/**/*.gcno)
cov_info = coverage.info
html_cov_path = $(COVDIR)/html

CFLAGS = -Wall -Wsign-compare -Wextra -Wpedantic -g -I$(IDIR) --coverage
AVROBJFLAGS = -Os -DF_CPU=16000000UL
AVREXECFLAGS = -mmcu=atmega328p
OBJCOPYFLAGS = -O ihex -R .eeprom
AVRDUDEFLAGS = -F -V -c arduino -p ATMEGA328P -b 115200
TESTFLAGS = -lcunit -I.
COVFLAGS = --capture --directory . --output-file $(COVDIR)/$(cov_info)
HTMLGENFLAGS = $(COVDIR)/$(cov_info) --output-directory $(html_cov_path)

src/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(AVROBJFLAGS) $(AVREXECFLAGS)

test/%.o: test/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(TESTFLAGS)

$(EXEC): $(obj) $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) $(AVREXECFLAGS)

$(TESTER): $(test_obj) $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) $(TESTFLAGS)

hex: $(EXEC)
	$(OBJ_COPY) $(OBJCOPYFLAGS) $(EXEC) $(HEX)

.PHONY: build upload clean coverage

upload: $(HEX)
	$(AVRDUDE) $(AVRDUDEFLAGS) -P $(device) -U flash:w:$(HEX)

clean:
	rm -f $(obj) $(test_files_obj) $(EXEC) $(TESTER) $(HEX) $(coverage_files)

coverage: $(TESTER)
	./$(TESTER)
	$(COV) $(COVFLAGS)
	$(HTMLGEN) $(HTMLGENFLAGS)
