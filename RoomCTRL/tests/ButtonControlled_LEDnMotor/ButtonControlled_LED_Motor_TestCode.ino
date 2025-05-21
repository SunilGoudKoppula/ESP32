// Define GPIO pins for buttons
#define BTN1 32  // MODE button
#define BTN2 33  // UP button
#define BTN3 25  // DOWN button
#define BTN4 26  // HOME button (Fan ON/OFF)

// Define GPIO pins for RGB LED
#define LED_R 16
#define LED_G 17
#define LED_B 18

// Define GPIO pin for motor (PWM control)
#define MOTOR_PWM 27

void setup() {
  Serial.begin(115200);  // Start serial communication

  // Set button pins as input with internal pull-up resistors
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(BTN4, INPUT_PULLUP);

  // Configure PWM channels for RGB LEDs (8-bit resolution @ 5kHz)
  ledcSetup(0, 5000, 8); ledcAttachPin(LED_R, 0);
  ledcSetup(1, 5000, 8); ledcAttachPin(LED_G, 1);
  ledcSetup(2, 5000, 8); ledcAttachPin(LED_B, 2);

  // Configure PWM channel for motor control
  ledcSetup(3, 5000, 8); ledcAttachPin(MOTOR_PWM, 3);
}

void loop() {
  // Check each button and respond accordingly

  if (digitalRead(BTN1) == LOW) {
    Serial.println("Button 1 Pressed");
    ledcWrite(0, 255); // Set RED LED ON
  }

  if (digitalRead(BTN2) == LOW) {
    Serial.println("Button 2 Pressed");
    ledcWrite(1, 255); // Set GREEN LED ON
  }

  if (digitalRead(BTN3) == LOW) {
    Serial.println("Button 3 Pressed");
    ledcWrite(2, 255); // Set BLUE LED ON
  }

  if (digitalRead(BTN4) == LOW) {
    Serial.println("Button 4 Pressed - Fan ON");
    ledcWrite(3, 200); // Turn ON motor at ~78% duty cycle
  } else {
    ledcWrite(3, 0);   // Turn OFF motor
  }

  delay(100);  // Debounce delay
}
