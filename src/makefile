exeFile = main.o
runFile = main.c

std:
	$(stdInit)
	$(comp)
	$(run)
	$(remove)

build:
	$(stdInit)
	$(comp)

SHELL := /bin/bash

time:
	$(stdInit)
	$(comp)
	time ../build/$(exeFile)

define stdInit
endef

define comp
	gcc -o ../build/$(exeFile) $(runFile) -O2 -std=c99 -lm -lraylib -lGL -lm -pthread -ldl
endef

define run
	../build/$(exeFile)
endef

define remove
	rm ../build/$(exeFile)
endef
