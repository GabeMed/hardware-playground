# Arduino CLI Workflow

Full guide from installation to upload.

## 1. Install arduino-cli

### macOS (Homebrew)

```bash
brew install arduino-cli
```

### Linux

```bash
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
```

### Windows

```powershell
choco install arduino-cli
```

Verify the installation:

```bash
arduino-cli version
```

## 2. Initialize configuration

```bash
arduino-cli config init
```

This creates a default config file at `~/.arduino15/arduino-cli.yaml`.

## 3. Update the board index

```bash
arduino-cli core update-index
```

## 4. Install the board core

For Arduino Uno (AVR boards):

```bash
arduino-cli core install arduino:avr
```

Check what's installed:

```bash
arduino-cli core list
```

## 5. Create a new sketch (first time only)

```bash
arduino-cli sketch new MySketch
```

This creates a `MySketch/MySketch.ino` file. You can also just create the `.ino` file manually.

**Important:** The `.ino` filename must match its parent directory name. This repo uses one directory per exercise:

```
hardware-playground/
├── arduino-cli-guide.md
├── ex01-led-blink/
│   └── ex01-led-blink.ino
├── ex02-red-green-blink/
│   └── ex02-red-green-blink.ino
└── ...
```

## 6. Edit your code

Open and edit the `.ino` file inside the exercise directory you want to work on.

## 7. Compile

`cd` into the exercise directory first, then compile:

```bash
cd ex02-red-green-blink
arduino-cli compile --fqbn arduino:avr:uno .
```

- `--fqbn` specifies the board (Fully Qualified Board Name).
- `.` points to the current directory containing the sketch.

## 8. Find your board's port

Plug in your Arduino and run:

```bash
arduino-cli board list
```

Look for the USB port your Arduino is connected to (e.g. `/dev/cu.usbserial-1140`).

## 9. Upload

```bash
arduino-cli upload --fqbn arduino:avr:uno --port /dev/cu.usbserial-1140 .
```

Replace the `--port` value with whatever `board list` showed.

## 10. Monitor serial output (optional)

```bash
arduino-cli monitor --port /dev/cu.usbserial-1140 --config baudrate=9600
```

Press `Ctrl+C` to exit the monitor.

---

## Rebuild (clean + recompile)

If you want a full rebuild from scratch, use the `--clean` flag:

```bash
arduino-cli compile --fqbn arduino:avr:uno --clean .
```

This removes all cached build artifacts and recompiles everything.

You can also manually delete the build directory before compiling:

```bash
rm -rf build/ && arduino-cli compile --fqbn arduino:avr:uno .
```

---

## Quick iteration cycle

After initial setup, repeat these steps every time you change code:

```
Edit code -> Compile -> Upload
```

```bash
arduino-cli compile --fqbn arduino:avr:uno . && arduino-cli upload --fqbn arduino:avr:uno --port /dev/cu.usbserial-1140 .
```

For a clean rebuild + upload:

```bash
arduino-cli compile --fqbn arduino:avr:uno --clean . && arduino-cli upload --fqbn arduino:avr:uno --port /dev/cu.usbserial-1140 .
```

---

## Other useful commands

| Command | Description |
|---|---|
| `arduino-cli core list` | List installed board cores |
| `arduino-cli core search` | Search for available cores |
| `arduino-cli lib install "LibName"` | Install a library |
| `arduino-cli lib search keyword` | Search for libraries |
| `arduino-cli board listall` | List all supported board FQBNs |
| `arduino-cli compile --fqbn arduino:avr:uno --clean .` | Clean rebuild |
