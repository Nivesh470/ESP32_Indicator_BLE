# Indicator Control over Mobile Phone using BLE

This project demonstrates how to control vehicle-like turn indicators using both push buttons and Bluetooth Low Energy (BLE) commands from a mobile phone. The system runs on an ESP32 board and uses logic generated from Simulink to manage indicator behavior such as LEFT, RIGHT, HAZARD, and OFF. The project supports both manual (physical button) and wireless (BLE) control.

## Features

- BLE-based control using mobile apps like nRF Connect
- Push-button input with long press detection
- LEFT, RIGHT, and HAZARD blink patterns
- Automatic OFF behavior when no input is detected
- Integrated Simulink state machine logic
- UART serial output for debugging

## Hardware Used

- ESP32 Dev Board (NodeMCU ESP32-S)
- 2 LEDs (for left and right indicators)
- 2 push buttons (for manual control)
- USB cable (for power and serial communication)

## BLE Commands

Use a BLE terminal app (like nRF Connect) to send the following commands as UTF-8 text:

- `LEFT` — Activate left indicator
- `RIGHT` — Activate right indicator
- `HAZARD` — Blink both indicators
- `OFF` — Turn off all indicators

The BLE characteristic UUID is: `abcdef01-1234-1234-1234-abcdefabcdef`  
Service UUID: `12345678-1234-1234-1234-1234567890ab`

## How to Use

1. Upload the code to the ESP32 using Arduino IDE.
2. Open Serial Monitor at 115200 baud for logs.
3. Connect buttons to GPIO 18 and 19 with pull-up.
4. Connect LEDs to GPIO 21 and 22.
5. Use push buttons or connect via BLE and send text commands.
6. Observe LED behavior and serial logs.

## Files

- `IndicatorControl.ino`: Main program
- `indicator_model.cpp`: Simulink logic (edited to fix LEFT/RIGHT/OFF issues)
- `indicator_model.h`: Header for Simulink logic
- `README.md`: This documentation file

## Demo and Logs

- [Demo Video ZIP (Google Drive)](https://drive.google.com/file/d/1Hw8fxD1VyQp39uL3ZQiOLN-bDocbgb9K/view?usp=drive_link)
- [UART Serial Log File](https://drive.google.com/file/d/1Vt2x70F4KN76Et_BjzfekBpymPJ12OGB/view?usp=drive_link)

## Author

Developed by: _Your Name_  
Course: Embedded Software Systems  
Tools used: Arduino IDE, Simulink, BLE


