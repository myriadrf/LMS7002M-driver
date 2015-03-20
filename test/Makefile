CC=gcc
CFLAGS= \
	-D_GNU_SOURCE \
	-std=c99 \
	-I$(CURDIR)/../include \
	-I$(CURDIR)/../interfaces

LMS7_SOURCES := $(wildcard $(CURDIR)/../src/LMS7002M_*.c)
LMS7_HEADERS := $(wildcard $(CURDIR)/../include/LMS7002M/*.h)

INTERFACE_HDRS = \
	$(wildcard $(CURDIR)/../interfaces/*.h)

LIBS=-lm

%.o: %.c $(INTERFACE_HDRS) $(LMS7_HEADERS) $(LMS7_SOURCES)
	$(CC) -c -o $@ $< $(CFLAGS)

all: access_test.exe

access_test.exe: access_test.o $(LMS7_OBJECTS)
	$(CC) -o $@ $(LMS7_SOURCES) $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.exe *.o
