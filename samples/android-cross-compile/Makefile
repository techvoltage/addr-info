include $(CLEAR_VARS)
LOCAL_PATH := $(call my-dir)
include $(BUILD_SHARED_LIBRARY)
include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.
#https://stackoverflow.com/questions/9460251/how-do-i-build-a-native-command-line-executable-to-run-on-android
#CFLAGS=-m32
SRCS = 	$(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
OBJECTS = $(patsubst %.c,%.o,$(SRCS))
#APP := selfROP-sample-1-android
APP := hello_world
ROOT := /home/jay/android-sdk-linux
NDK_PLATFORM_VER := 23
ANDROID_NDK_ROOT := $(ROOT)/android-ndk-r12b
ANDROID_NDK_HOST := linux-x86_64
ANDROID_SDK_ROOT := $(ROOT)
PREBUILD := $(ANDROID_NDK_ROOT)/toolchains/arm-linux-androideabi-4.9/prebuilt//$(ANDROID_NDK_HOST)
LOCAL_MODULE := libdl
LOCAL_SRC_FILES := *.c
LOCAL_CPPFLAGS := -std=gnu++0x -Wall -fPIE -pie         # whatever g++ flags you like
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog -fPIE -pie -ldl  # whatever ld flags you like
LOCAL_SHARED_LIBRARIES := libcutils libdl
BIN := $(PREBUILD)/bin/
LIB := $(ANDROID_NDK_ROOT)/platforms/android-$(NDK_PLATFORM_VER)/arch-arm/usr/lib
INCLUDE := $(ANDROID_NDK_ROOT)/platforms/android-$(NDK_PLATFORM_VER)/arch-arm/usr/include

CC := $(BIN)/arm-linux-androideabi-gcc
GDB_CLIENT := $(BIN)/arm-linux-androideabi-gdb

LIBCRT := $(LIB)/crtbegin_dynamic.o

LINKER := /system/bin/linker

DEBUG := -g

CFLAGS := $(DEBUG) -fno-short-enums -I$(INCLUDE)
CFLAGS += -Wl,-rpath-link=$(LIB),-dynamic-linker=$(LINKER) -L$(LIB)
CFLAGS += -nostdlib -lc -pie -fPIE

#all: $(APP)

#$(APP): $(APP).c
#	$(CC) -o $@ $< $(CFLAGS) $(LIBCRT)
INSTALL_DIR:=/sdcard/
SHELL=/bin/bash
abc=all 
test:
	@ echo $(SHELL)
	@if [ ! `$(ANDROID_SDK_ROOT)/platform-tools/adb shell id -u` ]; then \
		$(ANDROID_SDK_ROOT)/platform-tools/adb mkdir -p /data/sdcard/tmp; \
		$(INSTALL_DIR)=/sdcard; \
	else \
		echo hi; \
		export INSTALL_DIR=/data/local/tmp; \
	fi;
		@echo done
check:
	@ if [ ! `$(ANDROID_SDK_ROOT)/platform-tools/adb shell id -u` ]; then \
		$(ANDROID_SDK_ROOT)/platform-tools/adb mkdir -p /data/sdcard/tmp; \ 
		INSTALL_DIR=/data/sdcard/tmp; \ 
		@ echo rooted; \ 
	else \
		@ echo not rooted; \
		INSTALL_DIR = /data/local/tmp; \
	fi
#	if [ ! `$(ANDROID_SDK_ROOT)/platform-tools/adb shell id -u` ]; then
#	if [ -f ls ]; then \  
#		@echo rooted; \
#		$(ANDROID_SDK_ROOT)/platform-tools/adb mkdir -p /data/sdcard/tmp; \
#		INSTALL_DIR := /data/sdcard/tmp; \
#	else \
#		@echo not rooted; \
#		INSTALL_DIR := /data/local/tmp; \
#	fi
install: $(APP)
	$(ANDROID_SDK_ROOT)/platform-tools/adb push $(APP) $(INSTALL_DIR)/$(APP) 
	$(ANDROID_SDK_ROOT)/platform-tools/adb shell chmod 777 $(INSTALL_DIR)/$(APP)
	$(ANDROID_SDK_ROOT)/platform-tools/adb shell chmod +x $(INSTALL_DIR)/$(APP)

shell:
	$(ANDROID_SDK_ROOT)/platform-tools/adb shell

run:
	$(ANDROID_SDK_ROOT)/platform-tools/adb shell $(INSTALL_DIR)/$(APP)
	@#/data/local/tmp/selfROP-sample-1-android

debug-install:
	$(ANDROID_SDK_ROOT)/platform-tools/adb push $(PREBUILD)/../gdbserver $(INSTALL_DIR)/gdbserver
	$(ANDROID_SDK_ROOT)/platform-tools/adb shell chmod 777 $(INSTALL_DIR)/gdbserver

debug-go:
	$(ANDROID_SDK_ROOT)/platform-tools/adb forward tcp:1234: tcp:1234
	$(ANDROID_SDK_ROOT)/platform-tools/adb shell $(INSTALL_DIR)/gdbserver :1234 $(INSTALL_DIR)/$(APP)

debug:
	$(GDB_CLIENT) $(APP)

#override clean:
#	@rm -f $(APP).o $(APP)


all: $(PROGS)
	make test
	#make check
	make install
	make run
%.o:
	@echo $@
%: %.c
	$(CC) $(CPP_FLAGS) $(CFLAGS) $(PRJCFLAGS) -o $@ $< $(LDFLAGS)
clean:
	rm -f $(PROGS) $(OBJECTS)
.PHONY: all install clean test
