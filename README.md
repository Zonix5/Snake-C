# Autonomous snake game with A*

For ESP32-S3 microcontroller with Neopixel matrix

## Requirements
- Arduino IDE
- Add https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json in **Preferences**
- Install **esp32** from Espressif Systems in **Boards Manager**
- Install **Adafruit Neopixel** from Adafruit in **Library Manager**

## Setup
- Connect Neopixel **5V** to a Power GPIO
- Connect Neopixel **GND** to a GND GPIO
- Connect Neopixel **DIN** to GPIO 14

- Set your matrix size in **include\utils.h**, by modifying **SNAKE_LENGTH** and **SNAKE_WIDTH** to your corresponding matrix length and width (by default 16 by 16)

## Notes
- Tested with ESP32-S3-WROOM-1 N16R8 and Neopixel matrix 16*16.