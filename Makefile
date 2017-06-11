include Makefile.inc
export
#CFLAGS=-Wall
#ARCH := $(shell getconf LONG_BIT)
#CPP_FLAGS_32 := -m32 -Wall -I$(INC_DIR) #...  Some 32 specific compiler flags ...
#CPP_FLAGS_64 := -Wall -I$(INC_DIR)
#CPP_FLAGS_ARM_32 := -Wall -I$(INC_DIR)
#CPP_FLAGS_ARM_64 := -Wall -I$(INC_DIR)
#CPP_FLAGS := $(CPP_FLAGS_$(ARCH))  #... all the other flags ...
#addr-info: $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) -o addr-info $(LDFLAGS)

SRCS = 	$(wildcard samples/*.c)
 	#$(wildcard samples/android/*.c)\
	$(wildcard samples/x86/*.c)\
	$(wildcard samples/x86-64/*.c)\
 	$(wildcard samples/arm-32/*.c)\
 	$(wildcard samples/arm-64/*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
OBJECTS = $(patsubst %.c,%.o,$(SRCS))
SUBDIRS=samples/x86 samples/x86-64 samples/arm-32 samples/arm-64 samples/android
#all:samples
#samples: $(PROGS)
%.o:
	@echo $@
%: %.c
	$(CC) $(PRJCFLAGS) -o $@ $< $(LDFLAGS)
#clean:
#	rm -f *~ *.o addr-info
#clean:
#	rm -f $(PROGS) $(OBJECTS)
all:
	echo $(PRJCFLAGS)
	@for i in $(SUBDIRS); do \
	echo "make all in $$i"; \
	(cd $$i; $(MAKE) $(MFLAGS) $(MYMAKEFLAGS) all); done

clean:
	@for i in $(SUBDIRS); do \
        echo "Clearing in $$i"; \
        (cd $$i; $(MAKE) $(MFLAGS) $(MYMAKEFLAGS) clean); done


print-labels:
	@echo $(PRJCFLAGS)
show-src:
	@echo $(SRCS)
show-progs:
	@echo $(PROGS)
show-objects:
	@echo About to make distribution files
	@echo $(OBJECTS)

.PHONY: all install clean test
