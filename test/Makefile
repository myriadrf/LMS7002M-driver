IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

OBJ=spidev_test.o

LIBS=-lm

DEPS=$(wildcard $(IDIR)/LMS7002M/*.h)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

spidev_test.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.exe *.o
