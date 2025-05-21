# State Machine Test (ESP32)

This project demonstrates a simple **state machine** implementation on the ESP32 using four physical buttons to navigate between modes and adjust parameters like temperature, brightness, and fan speed.

## 📋 Features

- Four control modes:
  - **HOME**: Idle state
  - **TEMP_CONTROL**: Adjust temperature setpoint
  - **LIGHT_CONTROL**: Adjust brightness
  - **FAN_CONTROL**: Adjust fan speed
- Button-based UI (with debouncing)
- Serial monitor prints current state and value changes

## 🔧 Hardware Setup

| Button | Pin Number |
|--------|------------|
| MODE   | 32         |
| UP     | 33         |
| DOWN   | 25         |
| HOME   | 26         |

Use pull-up resistors or configure internal pull-ups as done in the code.

## 🚀 Controls

| Button  | Action                          |
|---------|---------------------------------|
| MODE    | Cycle to next mode              |
| UP      | Increase value (based on mode)  |
| DOWN    | Decrease value (based on mode)  |
| HOME    | Return to HOME mode             |

## 🧠 State Machine Logic

- Starts in `HOME` mode.
- Pressing `MODE` cycles through: TEMP → LIGHT → FAN → HOME.
- Pressing `UP`/`DOWN` changes the setting based on the current mode.
- `HOME` button resets mode to `HOME`.

## 🖨 Output (via Serial Monitor)
