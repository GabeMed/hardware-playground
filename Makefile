# Compile or upload the exercises with arduino-cli (see arduino-cli-guide.md).
#
#   make setup                                   install the AVR core (once)
#   make compile                                 compile every exercise
#   make upload EX=ex03-ldr-read PORT=/dev/cu.usbserial-1140
#   make monitor PORT=/dev/cu.usbserial-1140

FQBN     ?= arduino:avr:uno
BAUD     ?= 9600
SKETCHES := $(patsubst %/,%,$(sort $(dir $(wildcard ex*/*.ino))))

.PHONY: all setup compile list upload monitor

all: compile

setup:
	arduino-cli core update-index
	arduino-cli core install arduino:avr

list:
	@printf '%s\n' $(SKETCHES)

compile:
	@set -e; for sketch in $(SKETCHES); do \
		echo "== $$sketch"; \
		arduino-cli compile --fqbn $(FQBN) --warnings all $$sketch; \
	done

upload:
	@test -n "$(EX)" || (echo "usage: make upload EX=<exercise dir> PORT=<port>"; exit 1)
	@test -n "$(PORT)" || (echo "PORT is not set; run: arduino-cli board list"; exit 1)
	arduino-cli compile --fqbn $(FQBN) $(EX)
	arduino-cli upload --fqbn $(FQBN) --port $(PORT) $(EX)

monitor:
	@test -n "$(PORT)" || (echo "PORT is not set; run: arduino-cli board list"; exit 1)
	arduino-cli monitor --port $(PORT) --config baudrate=$(BAUD)
