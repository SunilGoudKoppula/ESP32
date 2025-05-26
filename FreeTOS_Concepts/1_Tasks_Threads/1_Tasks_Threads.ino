#include <Arduino.h>

// Task to blink the built-in LED
void TaskBlink(void *pvParameters) {
  // Set the LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);

  while (1) {
    // Turn the LED on
    digitalWrite(LED_BUILTIN, HIGH);
    // Wait for 1 second
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // Turn the LED off
    digitalWrite(LED_BUILTIN, LOW);
    // Wait for 1 second
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task to print a message to the Serial Monitor
void TaskPrint(void *pvParameters) {
  while (1) {
    // Print a message
    Serial.println("Hello from TaskPrint");
    // Wait for 2 seconds
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // Start the serial communication at 115200 baud rate
  Serial.begin(115200);

  // Create the Blink task with stack size 1000, priority 1
  xTaskCreate(TaskBlink, "Blink", 1000, NULL, 1, NULL);

  // Create the Print task with stack size 1000, priority 1
  xTaskCreate(TaskPrint, "Print", 1000, NULL, 1, NULL);
}

void loop() {
  // Empty loop since tasks are managed by the RTOS scheduler
}
