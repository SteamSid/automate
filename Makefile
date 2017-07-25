SHELL=/bin/bash
shell=/bin/bash
CC=g++
CFLAGS=-std=c++17

all:

OBJFILES=$(shell find ./ -type f -name '*.o')

main:
	$(OBJFILES=$(shell find ./ -type f -name '*.o'))
	$(CC) $(CFLAGS) $(OBJFILES) -ldl main.cpp -o automate.out

clean-main:
	@rm automate.out -v

define rendr_mkfile

	$(CC) $(CFLAGS) -c $(1) -o $(patsubst %.cpp,%.o,$(1))

endef

VFILES=$(wildcard renderer/*.cpp)

rendr:
	$(foreach fil,$(VFILES),$(call rendr_mkfile,$(fil)))

clean-rendr:
	@rm $(patsubst %.cpp,%.o,$(VFILES)) -v

define drv_mkso

	$(CC) $(CFLAGS) -fPIC -shared $(shell cat ${patsubst %.cpp,%.linkr,$(1)}) $(1) -o $(patsubst %.cpp,%.so,$(1))

endef

VDRIVERS=$(wildcard renderer/drivers/*.cpp)

rendr-drivers:
	$(foreach drv,$(VDRIVERS),$(call drv_mkso,$(drv)))

clean-rendr-drivers:
	@rm $(patsubst %.cpp,%.so,$(VDRIVERS)) -v
