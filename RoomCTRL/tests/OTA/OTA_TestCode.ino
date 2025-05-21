#include <WiFi.h>
#include <ArduinoOTA.h>

// Replace with your Wi-Fi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

void setup() {
  Serial.begin(115200);  // Start serial communication

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // Display IP for OTA upload

  // OTA Configuration
  ArduinoOTA.setHostname("esp32-ota-demo");  // Optional custom hostname

  // Start OTA service
  ArduinoOTA.begin();
  Serial.println("OTA ready");
}

void loop() {
  ArduinoOTA.handle();  // Continuously check for OTA updates
}
