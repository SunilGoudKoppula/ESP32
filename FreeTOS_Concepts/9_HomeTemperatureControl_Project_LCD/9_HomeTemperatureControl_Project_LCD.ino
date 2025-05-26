#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define hardware pins and constants
#define DHTPIN 4
#define DHTTYPE DHT22
#define FAN_PIN 16
#define BUTTON_PIN 0

// Create sensor and LCD objects
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD at I2C address 0x27 with 16 columns and 2 rows

// Declare queue and task handles
QueueHandle_t tempQueue;
TaskHandle_t modeTaskHandle;

// Control flags and thresholds
bool manualMode = false;            // Flag to indicate manual or auto mode
float tempThreshold = 28.0;         // Temperature threshold for fan activation in auto mode

// Interrupt Service Routine to toggle mode
void IRAM_ATTR handleButtonPress() {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  // Notify the ModeTask from the ISR
  vTaskNotifyGiveFromISR(modeTaskHandle, &xHigherPriorityTaskWoken);
  // Yield to higher-priority task if needed
  portYIELD_FROM_ISR();
}

// Task to read temperature from DHT22 sensor
void SensorTask(void *pvParameters) {
  float temp;
  while (1) {
    temp = dht.readTemperature();
    // Send temperature to queue if it's valid
    if (!isnan(temp)) {
      xQueueSend(tempQueue, &temp, 0);
    }
    // Wait 2 seconds before next read
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

// Task to control the fan based on temperature (auto mode only)
void FanControlTask(void *pvParameters) {
  float temp;
  while (1) {
    // Wait for new temperature reading
    if (xQueueReceive(tempQueue, &temp, portMAX_DELAY)) {
      // In auto mode, control the fan based on temperature threshold
      if (!manualMode) {
        digitalWrite(FAN_PIN, temp > tempThreshold ? HIGH : LOW);
      }
    }
  }
}

// Task to toggle between auto and manual mode via button press
void ModeTask(void *pvParameters) {
  // Setup button pin with internal pull-up
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // Attach interrupt for button press (falling edge)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);

  while (1) {
    // Wait indefinitely for button press notification
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // Toggle between manual and auto mode
    manualMode = !manualMode;
    Serial.println(manualMode ? "Manual Mode" : "Auto Mode");
  }
}

// Task to update LCD with temperature and mode status
void LCDTask(void *pvParameters) {
  float temp = 0.0;
  while (1) {
    // Peek at the most recent temperature in the queue without removing it
    if (uxQueueMessagesWaiting(tempQueue) > 0) {
      xQueuePeek(tempQueue, &temp, 0);
    }

    // Update LCD display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp, 1);
    lcd.print((char)223); // Degree symbol
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Mode: ");
    lcd.print(manualMode ? "Manual" : "Auto");

    // Refresh every second
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Setup function to initialize peripherals and tasks
void setup() {
  Serial.begin(115200);     // Start serial communication
  dht.begin();              // Initialize DHT sensor
  lcd.init();               // Initialize LCD
  lcd.backlight();          // Turn on LCD backlight
  pinMode(FAN_PIN, OUTPUT); // Set fan pin as output

  // Create a queue capable of holding 5 float values
  tempQueue = xQueueCreate(5, sizeof(float));

  // Create tasks with stack size and priority
  xTaskCreate(SensorTask, "Sensor", 2048, NULL, 1, NULL);
  xTaskCreate(FanControlTask, "Fan", 2048, NULL, 2, NULL);
  xTaskCreate(ModeTask, "Mode", 2048, NULL, 3, &modeTaskHandle);
  xTaskCreate(LCDTask, "LCD", 2048, NULL, 1, NULL);
}

// Empty loop – tasks are managed by FreeRTOS
void loop() {
  // Nothing needed here
}
