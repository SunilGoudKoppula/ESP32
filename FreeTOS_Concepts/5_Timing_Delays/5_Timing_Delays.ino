#include <Arduino.h>

// Task function that runs periodically
void PeriodicTask(void *pvParameters) {
  while (1) {
    // Print a message to indicate the task is running
    Serial.println("Periodic Task Executing");

    // Delay the task for 2000 milliseconds (2 seconds)
    // This releases the CPU for other tasks
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // Start serial communication at 115200 baud
  Serial.begin(115200);

  // Create the periodic task
  // Task function: PeriodicTask
  // Name: "Periodic"
  // Stack size: 1000 words
  // Parameter: NULL (none)
  // Priority: 1 (normal priority)
  // Task handle: NULL (no handle needed)
  xTaskCreate(PeriodicTask, "Periodic", 1000, NULL, 1, NULL);
}

void loop() {
  // Empty – task is managed by FreeRTOS scheduler
}
