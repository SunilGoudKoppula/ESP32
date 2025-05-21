# 📟 ESP32 I2C LCD Display Test

This simple test sketch initializes a 16x2 LCD using the I2C protocol with an **ESP32** board. It displays two lines of text confirming successful communication and readiness.

---

## 🧰 Hardware Requirements

- ESP32 board
- 16x2 I2C LCD (commonly uses PCF8574 I2C backpack)
- Jumper wires
- Breadboard (optional)

---

## 🔌 I2C Wiring for ESP32

| LCD Pin | ESP32 Pin |
|---------|-----------|
| VCC     | 3.3V or 5V |
| GND     | GND       |
| SDA     | GPIO21    |
| SCL     | GPIO22    |

> **Note:** I2C pins may vary by board. Adjust if needed.

---

## 🧪 How to Use

1. Connect your LCD to the ESP32 via I2C as shown above.
2. Install the **LiquidCrystal_I2C** library via:
   - Arduino IDE → **Tools > Manage Libraries**
   - Search and install: `"LiquidCrystal I2C by Frank de Brabander"`
3. Upload the sketch `lcd_test.ino` to your ESP32.
4. Open the Serial Monitor or just look at the LCD screen.

---

## 🔍 I2C Address Check

If the LCD does not display text:
- Run the **I2C scanner** sketch to detect the actual I2C address.
- Update `LiquidCrystal_I2C lcd(0x27, 16, 2);` with the correct address (e.g., `0x3F`).

---

## 📁 Files

- `lcd_test.ino` – Main Arduino sketch
- `README.md` – Documentation

---

## 📜 License

This project is released under the [MIT License](LICENSE).

---

## 🤝 Contributing

Pull requests and enhancements welcome!
