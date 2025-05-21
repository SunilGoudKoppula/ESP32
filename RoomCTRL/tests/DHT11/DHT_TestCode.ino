#include "DHT.h"  // Include the DHT sensor library

#define DHTPIN 2       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // Define the sensor type as DHT11

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

// Function to read temperature in Fahrenheit
int readTemperature() {
  float temperature = dht.readTemperature();  // Read temperature in Celsius
  if (!isnan(temperature)) {
    return round((temperature * 1.8) + 32);  // Convert to Fahrenheit and round
  } else {
    return 0;  // Return 0 if the reading failed
  }
}

// Function to read humidity
int readHumidity() {
  float humidity = dht.readHumidity();  // Read humidity percentage
  if (!isnan(humidity)) {
    return round(humidity);  // Return rounded humidity value
  } else {
    return 0;  // Return 0 if the reading failed
  }
}

void setup() {
  Serial.begin(9600);  // Start the serial communication
  dht.begin();         // Initialize the DHT sensor
}

void loop() {
  delay(2000);  // Wait 2 seconds between readings

  // Print temperature
  Serial.print("Temperature: ");
  Serial.print(readTemperature());
  Serial.println(" F");

  // Print humidity
  Serial.print("Humidity: ");
  Serial.print(readHumidity());
  Serial.println(" %");
}
