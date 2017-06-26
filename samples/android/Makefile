SRCS = 	$(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
OBJECTS = $(patsubst %.c,%.o,$(SRCS))
APP := selfROP-sample-1-android
#APP := hello_world
ROOT := /home/jay/android-sdk-linux
LOCAL_SRC_FILES := *.c
#LOCAL_CPPFLAGS := -std=gnu++0x -Wall -fPIE -pie         # whatever g++ flags you like
#LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog -fPIE -pie -ldl  # whatever ld flags you like
#LOCAL_SHARED_LIBRARIES := libcutils libdl
#INCLUDE := $(ANDROID_NDK_ROOT)/platforms/android-$(NDK_PLATFORM_VER)/arch-arm/usr/include

UNAME_M=$(shell uname -m)
CC := gcc

#DEBUG := -g

#CFLAGS := $(DEBUG) -fno-short-enums -I$(INCLUDE)
#CFLAGS += -Wl,-rpath-link=$(LIB),-dynamic-linker=$(LINKER) -L$(LIB)
#CFLAGS += -nostdlib -lc -pie -fPIE

all: $(PROGS)
%.o:
	@echo $@
%: %.c
	$(CC) $(CPP_FLAGS) $(CFLAGS) $(PRJCFLAGS) -o $@ $< $(LDFLAGS)
ifeq ($(filter arm%,$(UNAME_M)),)
	$(error Compile this sample on ARM)
endif

ifeq ($(filter genymotion%,$(UNAME_M)),)
	@echo compiling on genymotion emulator
	#$(error Compile this sample on ARM)
endif
clean:
	rm -f $(PROGS) $(OBJECTS)
.PHONY: all install clean test
