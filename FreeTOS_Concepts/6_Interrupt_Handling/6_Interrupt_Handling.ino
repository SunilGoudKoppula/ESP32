#include <Arduino.h>

// Define the button pin
#define BUTTON_PIN 1

// Handle for the task that will wait for the interrupt
TaskHandle_t TaskHandle = NULL;

// Interrupt Service Routine (ISR) for the button
void IRAM_ATTR handleInterrupt() {
  // Variable to check if a higher priority task should run after the ISR
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  // Notify the task from ISR that an interrupt occurred
  vTaskNotifyGiveFromISR(TaskHandle, &xHigherPriorityTaskWoken);

  // Yield to the higher-priority task if necessary
  portYIELD_FROM_ISR();
}

// Task that waits for notification from ISR
void InterruptTask(void *pvParameters) {
  // Configure the button pin as input with internal pull-up
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Attach an interrupt to the button pin, trigger on falling edge (button press)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, FALLING);

  while (1) {
    // Wait indefinitely for a notification from the ISR
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // ISR has notified the task – respond to the button press
    Serial.println("Button Pressed!");
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Create the task and store its handle for notifications
  xTaskCreate(InterruptTask, "Interrupt", 1000, NULL, 1, &TaskHandle);
}

void loop() {
  // Empty – task and ISR handle everything
}
