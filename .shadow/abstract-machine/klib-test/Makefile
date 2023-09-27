NAME := klib-test
SRCS := test/string-test.c
export MODULE  := TEST
export AM_HOME := $(PWD)/../../abstract-machine
ifeq ($(ARCH),)
export ARCH := native
endif

include $(AM_HOME)/Makefile
