CC=gcc
CFLAGS=-Wall
LDFLAGS=-ldl
OBJECTS=addr-info.o

#addr-info: $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) -o addr-info $(LDFLAGS)

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

samples: $(PROGS)
all:samples
%: %.c
	$(CC) $(CFLAGS)  -o $@ $< $(LDFLAGS)
.PHONY: clean
clean:
	rm -f *~ *.o addr-info
