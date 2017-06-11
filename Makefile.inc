# put common definitions in here
CC=gcc
INC_DIR=$(shell pwd)
PRJCFLAGS=-Wall -g -I$(INC_DIR)
LD=gcc
LDFLAGS=-ldl 
AR=ar
ARFLAGS=
RANLIB=ranlib
RM=rm
ECHO=echo
SHELL=/bin/sh

.SILENT :

