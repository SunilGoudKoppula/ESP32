#include <Arduino.h>

// Declare a handle for the queue
QueueHandle_t queue;

// Task that produces data and sends it to the queue
void ProducerTask(void *pvParameters) {
  int count = 0;  // Data to be sent

  while (1) {
    // Send the value of 'count' to the queue
    // portMAX_DELAY makes the task wait indefinitely if the queue is full
    xQueueSend(queue, &count, portMAX_DELAY);

    // Print the produced value
    Serial.println("Produced: " + String(count));

    count++;  // Increment count for next message

    // Delay for 1 second before producing the next item
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task that receives data from the queue
void ConsumerTask(void *pvParameters) {
  int received;  // Variable to store received data

  while (1) {
    // Try to receive data from the queue
    // portMAX_DELAY makes the task block until data is available
    if (xQueueReceive(queue, &received, portMAX_DELAY)) {
      // Print the received value
      Serial.println("Consumed: " + String(received));
    }
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Create a queue that can hold up to 5 integers
  // Each item in the queue is of type int
  queue = xQueueCreate(5, sizeof(int));

  // Create the producer task
  xTaskCreate(ProducerTask, "Producer", 1000, NULL, 1, NULL);

  // Create the consumer task
  xTaskCreate(ConsumerTask, "Consumer", 1000, NULL, 1, NULL);
}

void loop() {
  // Empty – the FreeRTOS scheduler runs the tasks
}
