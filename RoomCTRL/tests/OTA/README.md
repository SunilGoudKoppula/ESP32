# 🔄 ESP32 Over-The-Air (OTA) Update Example

This example enables **wireless code uploading** to your **ESP32** using **ArduinoOTA**. Upload once over USB, then update firmware remotely via Wi-Fi!

---

## 📡 Wi-Fi Setup

Edit the following in `esp32_ota.ino` before uploading:

```cpp
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
