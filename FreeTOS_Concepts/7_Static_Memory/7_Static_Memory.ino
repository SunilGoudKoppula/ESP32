#include <Arduino.h>

// Task control block and stack memory for static task
StaticTask_t xTaskBuffer;       // Stores task state and control info
StackType_t xStack[1000];       // Stack memory for the task (1000 words, not bytes)

// Task function to be run by the static task
void StaticTask(void *pvParameters) {
  while (1) {
    // Print message from the static task
    Serial.println("Static Task Running");
    // Delay for 1 second
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);

  // Create a statically allocated task
  // StaticTask: function to execute
  // "Static": task name
  // 1000: stack size (in words, not bytes)
  // NULL: parameters passed to the task (none)
  // 1: task priority
  // xStack: pre-allocated stack memory
  // &xTaskBuffer: pre-allocated task control block
  xTaskCreateStatic(StaticTask, "Static", 1000, NULL, 1, xStack, &xTaskBuffer);
}

void loop() {
  // Empty loop – the static task is managed by FreeRTOS
}
