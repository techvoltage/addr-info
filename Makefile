CC=gcc
CFLAGS=-Wall
LDFLAGS=-ldl
OBJECTS=addr-info.o

addr-info: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o addr-info $(LDFLAGS)

all:addr-info

.PHONY: clean
clean:
	rm -f *~ *.o addr-info
