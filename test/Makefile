IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -I../interfaces

LIBS=-lm

DEPS = \
	$(wildcard $(IDIR)/LMS7002M/*.h) \
	$(wildcard ../interfaces/*.h)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: access_test.exe

access_test.exe: access_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.exe *.o
