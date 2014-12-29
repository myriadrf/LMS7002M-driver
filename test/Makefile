IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c99

LIBS=-lm

DEPS=$(wildcard $(IDIR)/LMS7002M/*.h)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: spidev_test.exe gpio_test.exe

spidev_test.exe: spidev_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

gpio_test.exe: gpio_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.exe *.o
