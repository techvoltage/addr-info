CC=gcc
CFLAGS=-Wall
LDFLAGS=-ldl

#addr-info: $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) -o addr-info $(LDFLAGS)

SRCS = $(wildcard samples/*.c)

PROGS = $(patsubst %.c,%,$(SRCS))
OBJECTS = $(patsubst %.c,%.o,$(SRCS))

samples: $(PROGS)
all:samples
%.o:
	@echo $@
show-progs:
	@echo $(PROGS)
show-objects:
	@echo About to make distribution files
	@echo $(OBJECTS)
%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
.PHONY: all
.PHONY: clean
#clean:
#	rm -f *~ *.o addr-info
clean:
	rm -f $(PROGS) $(OBJECTS) #; make all

