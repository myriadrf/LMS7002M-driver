CC=gcc
CFLAGS= \
	-std=c99 \
	-I$(CURDIR)/../include \
	-I$(CURDIR)/../interfaces

LIBS=-lm

DEPS = \
	$(wildcard $(CURDIR)/../include/LMS7002M/*.h) \
	$(wildcard $(CURDIR)/../interfaces/*.h)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: access_test.exe

access_test.exe: access_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.exe *.o
