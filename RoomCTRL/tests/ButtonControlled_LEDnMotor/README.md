# 🔘 ESP32 Button-Controlled RGB LED and Motor System

This ESP32 sketch demonstrates reading **four buttons** to control an **RGB LED** and a **PWM motor output**.

---

## 🧰 Hardware Requirements

- ESP32 development board
- 4 push buttons
- RGB LED (common cathode preferred)
- Small DC motor with driver (or fan)
- Resistors (10kΩ for pull-up, if needed)
- Jumper wires and breadboard

---

## 🧭 Pin Configuration

| Function | GPIO Pin | Notes |
|----------|----------|-------|
| MODE Button | 32 | Sets RED LED |
| UP Button   | 33 | Sets GREEN LED |
| DOWN Button | 25 | Sets BLUE LED |
| HOME Button | 26 | Activates motor |
| RED LED     | 16 | PWM channel 0 |
| GREEN LED   | 17 | PWM channel 1 |
| BLUE LED    | 18 | PWM channel 2 |
| Motor (PWM) | 27 | PWM channel 3 |

---

## 🧪 Behavior

- Press **Button 1** → Red LED turns on
- Press **Button 2** → Green LED turns on
- Press **Button 3** → Blue LED turns on
- Press **Button 4** → Motor turns on (Fan ON)
- Release **Button 4** → Motor turns off

---

## 🧰 PWM Configuration

- 4 channels used (0–3)
- 5kHz frequency
- 8-bit resolution (0–255)

---

## 📁 Files

- `button_led_motor.ino` – Main Arduino sketch
- `README.md` – Documentation

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

## 🤝 Contributing

PRs for enhancements or alternative button handling logic (interrupts, debounce) are welcome!
