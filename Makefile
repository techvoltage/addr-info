CC=gcc
CFLAGS=-Wall
LDFLAGS=-ldl
ARCH := $(shell getconf LONG_BIT)
INC_DIR=.
CPP_FLAGS_32 := -m32 -Wall -I$(INC_DIR) #...  Some 32 specific compiler flags ...
CPP_FLAGS_64 := -Wall -I$(INC_DIR)
CPP_FLAGS_ARM_32 := -Wall -I$(INC_DIR)
CPP_FLAGS_ARM_64 := -Wall -I$(INC_DIR)




CPP_FLAGS := $(CPP_FLAGS_$(ARCH))  #... all the other flags ...

#addr-info: $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) -o addr-info $(LDFLAGS)

SRCS = 	$(wildcard samples/*.c)\
 	$(wildcard samples/android/*.c)\
	$(wildcard samples/x86/*.c)\
	$(wildcard samples/x86-64/*.c)\
 	$(wildcard samples/arm-32/*.c)\
 	$(wildcard samples/arm-64/*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
OBJECTS = $(patsubst %.c,%.o,$(SRCS))

samples: $(PROGS)
all:samples
%.o:
	@echo $@
show-src:
	@echo $(SRCS)
show-progs:
	@echo $(PROGS)
show-objects:
	@echo About to make distribution files
	@echo $(OBJECTS)
%: %.c
	$(CC) $(CPP_FLAGS) -o $@ $< $(LDFLAGS)
.PHONY: all install clean test
#clean:
#	rm -f *~ *.o addr-info
clean:
	rm -f $(PROGS) $(OBJECTS)

