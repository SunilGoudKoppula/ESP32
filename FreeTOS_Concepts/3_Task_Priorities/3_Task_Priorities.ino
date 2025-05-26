#include <Arduino.h>

// Task with lower priority (priority 1)
void Task1(void *pvParameters) {
  while (1) {
    // Print message from Task 1
    Serial.println("Task 1 (Priority 1)");
    // Delay for 1 second
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task with higher priority (priority 2)
void Task2(void *pvParameters) {
  while (1) {
    // Print message from Task 2
    Serial.println("Task 2 (Priority 2)");
    // Delay for 1 second
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);

  // Create Task1 with priority 1
  xTaskCreate(Task1, "Task1", 1000, NULL, 1, NULL);

  // Create Task2 with priority 2 (higher priority)
  xTaskCreate(Task2, "Task2", 1000, NULL, 2, NULL);
}

void loop() {
  // Empty – FreeRTOS handles all scheduling
}
