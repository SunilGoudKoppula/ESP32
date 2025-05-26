#include <Arduino.h>

// Declare a handle for the software timer
TimerHandle_t timer;

// Callback function that is called when the timer expires
void TimerCallback(TimerHandle_t xTimer) {
  // Print message to the Serial Monitor
  Serial.println("Timer Callback Executed");
}

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Create a periodic software timer
  // "Timer" is the name (for debugging, optional)
  // pdMS_TO_TICKS(2000) sets the timer period to 2000 ms (2 seconds)
  // pdTRUE means it's an auto-reload (periodic) timer
  // (void *)0 is the timer ID (can be used to identify the timer if needed)
  // TimerCallback is the function that will be called when the timer expires
  timer = xTimerCreate("Timer", pdMS_TO_TICKS(2000), pdTRUE, (void *)0, TimerCallback);

  // Start the timer immediately (0 ticks wait)
  xTimerStart(timer, 0);
}

void loop() {
  // Empty loop – the timer runs in the background managed by FreeRTOS
}
