# 🌡️ Arduino DHT11 Temperature and Humidity Monitor

This project reads **temperature** (in Fahrenheit) and **humidity** using a **DHT11 sensor** and an **Arduino** board, then prints the readings to the Serial Monitor.

---

## 🔧 Hardware Requirements

- Arduino Uno/Nano/compatible board
- DHT11 Sensor (3-pin or 4-pin)
- Jumper wires
- Breadboard
- (Optional) 10kΩ resistor for pull-up between VCC and DATA

---

## 🧰 Wiring

| DHT11 Pin | Arduino Pin |
|-----------|-------------|
| VCC       | 5V          |
| DATA      | D2          |
| GND       | GND         |

> **Note:** Use a 10kΩ pull-up resistor between **VCC** and **DATA** for reliable communication.

---

## 📲 Installation Steps

1. Connect components as shown above.
2. Install the **DHT sensor library**:
   - Arduino IDE → **Tools > Manage Libraries**
   - Search **"DHT sensor library"**
   - Install **Adafruit Unified Sensor** (if prompted)
3. Upload the code from `dht11_monitor.ino` to your Arduino.

---

## 🖥️ Output Example

Temperature: 73 F
Humidity: 45 %