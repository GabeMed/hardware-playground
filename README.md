# hardware-playground

Small Arduino exercises for learning embedded basics (digital output,
analog input, digital input with a pull-up, serial output), built and
uploaded from the command line with `arduino-cli` rather than the Arduino
IDE. Each exercise is one sketch in its own folder, written for an
**Arduino Uno** (`arduino:avr:uno`).

## Exercises

| Folder | What it does | Wiring | Serial |
|---|---|---|---|
| [`ex01-led-blink`](ex01-led-blink/ex01-led-blink.ino) | Blinks the on-board LED 5 times (100 ms on, 100 ms off), then waits 5 s, forever. | None: uses `LED_BUILTIN` (pin 13 on the Uno). | none |
| [`ex02-red-green-blink`](ex02-red-green-blink/ex02-red-green-blink.ino) | Alternates two LEDs: red blinks 3 times, 3 s pause, green blinks 3 times, 3 s pause. A `blinkLed(pin, times, intervalMs)` helper does the blinking. | Red LED on D13, green LED on D12, each through a series resistor (for example 220 ohm) to GND. | none |
| [`ex03-ldr-read`](ex03-ldr-read/ex03-ldr-read.ino) | Reads a light-dependent resistor on A0 every 500 ms and prints the raw 10-bit ADC value (0 to 1023). | LDR and a fixed resistor (for example 10 kohm) as a voltage divider between 5 V and GND, midpoint to A0. | 9600 baud, one number per line |
| [`ex04-button-read`](ex04-button-read/ex04-button-read.ino) | Toggles an on/off state each time a push button is pressed and prints the new state. Detects the HIGH-to-LOW edge; polling every 50 ms also acts as a simple debounce. | Push button between D2 and GND. The internal pull-up is enabled (`INPUT_PULLUP`), so no external resistor is needed. | 9600 baud, `Turned ON` / `Turned OFF` |

In ex03, which way the reading moves with light depends on how the divider
is wired: with the LDR on the 5 V side, more light gives a higher value.

## Build and upload

Install `arduino-cli` and the AVR core first. The full walkthrough, from
installation to serial monitor, is in [`arduino-cli-guide.md`](arduino-cli-guide.md).

With `make` (a thin wrapper around `arduino-cli`):

```sh
make setup                                              # once: install the arduino:avr core
make compile                                            # compile every exercise
arduino-cli board list                                  # find the port
make upload EX=ex04-button-read PORT=/dev/cu.usbserial-1140
make monitor PORT=/dev/cu.usbserial-1140                # 9600 baud
```

Or directly:

```sh
arduino-cli compile --fqbn arduino:avr:uno ex03-ldr-read
arduino-cli upload  --fqbn arduino:avr:uno --port /dev/cu.usbserial-1140 ex03-ldr-read
```

The `.ino` file name must match its folder name. `arduino-cli` requires it.

Program sizes on the Uno (from `make compile`, arduino:avr 1.8.8):

| Sketch | Flash | RAM |
|---|---|---|
| ex01-led-blink | 954 B (2%) | 9 B |
| ex02-red-green-blink | 1062 B (3%) | 9 B |
| ex03-ldr-read | 1892 B (5%) | 188 B |
| ex04-button-read | 3200 B (9%) | 221 B |

## CI

`.github/workflows/ci.yml` installs `arduino-cli` and runs `make compile` on
every pull request, so a sketch that stops compiling fails the build. There
is no simulation or hardware test: these sketches only toggle pins and print
to serial.

## Repository notes

`ex01-led-blink/build/` holds compiler output from an earlier Arduino IDE
build (the files are named after an older sketch, `FastLedProject`). It is
not needed to build anything. `.gitattributes` marks it as generated so
GitHub leaves it out of the language statistics, and `.gitignore` keeps new
build output out of the repository.
