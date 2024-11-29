# ESP Paste Firmware

This repository contains firmware for the ESP32-S3 board that transforms it into a wireless clipboard device. The board receives text over BLE (Bluetooth Low Energy) and emulates a USB HID (keyboard) to type out the clipboard contents when a designated button is pressed.

## Features
- **BLE Receiver**: Accepts text sent via BLE.
- **USB HID Emulation**: Types out the received text as a USB keyboard.
- **Push-to-Type**: Only types the text when the button on the ESP32-S3 is pressed.

## Requirements

### Hardware
- ESP32-S3 development board
- A button connected to the board (if not built-in)
- USB connection to the target device (computer, tablet, etc.)

### Software
- [PlatformIO](https://platformio.org/) installed in your preferred IDE (e.g., VSCode)

## Setup

1. Clone this repository:
   ```bash
   git clone https://github.com/atomikpanda/esppaste_firmware
   cd esppaste_firmware
   ```

2. Open the project in your PlatformIO-enabled IDE.

3. Connect your ESP32-S3 board to your computer.

4. Upload the firmware to the ESP32-S3:
   ```bash
   pio run --target upload
   ```

5. Monitor the serial output for debugging (optional):
   ```bash
   pio device monitor
   ```

## Usage

1. **Send Text via BLE**:
   Use a BLE-capable device or script to send text to the ESP32-S3.

2. **Type the Text**:
   - Connect the ESP32-S3 to the target device via USB.
   - Press the designated button on the ESP32-S3 to emulate typing the received text.

## Customization

You can modify the following parameters in the code:
- **BLE Device Name**: Customize the name for the ESP32-S3 BLE advertisement.
- **HID Report Settings**: Adjust the HID keyboard settings to match your use case.

## Troubleshooting

- **BLE Connection Issues**: Ensure BLE is enabled on your computer and the ESP32-S3 is powered and discoverable.
- **USB HID Not Working**: Verify that the target device supports USB HID keyboards and the cable is functional.