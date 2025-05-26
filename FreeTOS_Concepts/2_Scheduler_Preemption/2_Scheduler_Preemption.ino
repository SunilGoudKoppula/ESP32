#include <Arduino.h>

// Task with higher priority
void HighPriorityTask(void *pvParameters) {
  while (1) {
    // Print message from high-priority task
    Serial.println("High Priority Task Running");
    // Delay for 1 second
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task with lower priority
void LowPriorityTask(void *pvParameters) {
  while (1) {
    // Print message from low-priority task
    Serial.println("Low Priority Task Running");
    // Delay for 1 second
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Create high-priority task with priority 2
  xTaskCreate(HighPriorityTask, "High", 1000, NULL, 2, NULL);

  // Create low-priority task with priority 1
  xTaskCreate(LowPriorityTask, "Low", 1000, NULL, 1, NULL);
}

void loop() {
  // Empty loop since FreeRTOS handles the task scheduling
}
