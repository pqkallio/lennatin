PROJDIR = $(realpath $(CURDIR)/..)
IDIR = $(PROJDIR)/src
COVDIR = coverage
CC = gcc
COV = lcov
HTMLGEN = genhtml
_DEPS = ringbuffer.h \
		morse.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
TESTER = tester

src = $(IDIR)/morse.c \
		$(IDIR)/ringbuffer.c

test_files = $(wildcard *.c)
test = $(test_files) $(src)

obj = $(src:.c=.o)
test_files_obj = $(test_files:.c=.o)
test_obj = $(test:.c=.o)
coverage_files = $(wildcard $(IDIR)/*.gcda) $(wildcard $(IDIR)/*.gcno) $(wildcard $(IDIR)/**/*.gcda) $(wildcard $(IDIR)/**/*.gcno) \
				$(wildcard *.gcda) $(wildcard *.gcno)
cov_info = coverage.info
html_cov_path = $(COVDIR)/html

CFLAGS = -Wall -Wsign-compare -Wextra -Wpedantic -g -I$(IDIR) --coverage
TESTFLAGS = -lcunit -I.
COVFLAGS = --capture --directory $(IDIR) --output-file $(COVDIR)/$(cov_info)
HTMLGENFLAGS = $(COVDIR)/$(cov_info) --output-directory $(html_cov_path)

src/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test/%.o: test/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(TESTFLAGS)

$(TESTER): $(test_obj) $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) $(TESTFLAGS)

.PHONY: coverage clean

coverage: $(TESTER)
	mkdir -p $(COVDIR)
	./$(TESTER)
	$(COV) $(COVFLAGS)
	$(HTMLGEN) $(HTMLGENFLAGS)

clean:
	rm -f $(obj) $(test_files_obj) $(TESTER) $(coverage_files)
