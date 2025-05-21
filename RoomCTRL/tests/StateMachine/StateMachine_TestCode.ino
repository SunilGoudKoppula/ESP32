// Define GPIO pins for each button
#define BTN_MODE 32
#define BTN_UP 33
#define BTN_DOWN 25
#define BTN_HOME 26

// Define available control modes in the state machine
enum ControlMode {
  MODE_HOME,
  MODE_TEMP_CONTROL,
  MODE_LIGHT_CONTROL,
  MODE_FAN_CONTROL
};

// Initialize default values for state and control parameters
ControlMode currentMode = MODE_HOME;
int tempSetpoint = 25;
int brightness = 128;
int fanSpeed = 100;

// Track previous button states to detect rising/falling edges
bool lastStates[4] = { HIGH, HIGH, HIGH, HIGH };

// Function to increase a value depending on the current mode
void handleIncrease() {
  switch (currentMode) {
    case MODE_TEMP_CONTROL:
      tempSetpoint++;  // Increase temperature setpoint
      break;
    case MODE_LIGHT_CONTROL:
      brightness = min(255, brightness + 10);  // Cap brightness at 255
      break;
    case MODE_FAN_CONTROL:
      fanSpeed = min(255, fanSpeed + 10);  // Cap fan speed at 255
      break;
    default: break;
  }
  Serial.println("UP Button Pressed");
}

// Function to decrease a value depending on the current mode
void handleDecrease() {
  switch (currentMode) {
    case MODE_TEMP_CONTROL:
      tempSetpoint--;  // Decrease temperature setpoint
      break;
    case MODE_LIGHT_CONTROL:
      brightness = max(0, brightness - 10);  // Min brightness is 0
      break;
    case MODE_FAN_CONTROL:
      fanSpeed = max(0, fanSpeed - 10);  // Min fan speed is 0
      break;
    default: break;
  }
  Serial.println("DOWN Button Pressed");
}

// Print the current state and associated control value
void printCurrentState() {
  Serial.print("Current Mode: ");
  switch (currentMode) {
    case MODE_HOME:
      Serial.println("HOME");
      break;
    case MODE_TEMP_CONTROL:
      Serial.print("TEMP_CONTROL (Setpoint = ");
      Serial.print(tempSetpoint);
      Serial.println(")");
      break;
    case MODE_LIGHT_CONTROL:
      Serial.print("LIGHT_CONTROL (Brightness = ");
      Serial.print(brightness);
      Serial.println(")");
      break;
    case MODE_FAN_CONTROL:
      Serial.print("FAN_CONTROL (Speed = ");
      Serial.print(fanSpeed);
      Serial.println(")");
      break;
  }
}

// Polls button states and updates the state machine accordingly
void buttonTask() {
  // Read all button states
  bool states[4] = {
    digitalRead(BTN_MODE),
    digitalRead(BTN_UP),
    digitalRead(BTN_DOWN),
    digitalRead(BTN_HOME)
  };

  // Check for button press (falling edge)
  for (int i = 0; i < 4; i++) {
    if (lastStates[i] == HIGH && states[i] == LOW) {
      switch (i) {
        case 0:  // MODE button
          currentMode = static_cast<ControlMode>((currentMode + 1) % 4);
          Serial.println("Mode Button Pressed");
          break;
        case 1:  // UP button
          handleIncrease();
          break;
        case 2:  // DOWN button
          handleDecrease();
          break;
        case 3:  // HOME button
          currentMode = MODE_HOME;
          Serial.println("HOME Button Pressed");
          break;
      }
      printCurrentState();  // Show updated state
    }
    lastStates[i] = states[i];  // Update last known state
  }
  delay(100);  // Simple debounce
}

void setup() {
  Serial.begin(115200);

  // Configure buttons as input with internal pull-up resistors
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_HOME, INPUT_PULLUP);

  Serial.println("State Machine Test Started");
  printCurrentState();
}

void loop() {
  buttonTask();  // Continuously monitor button inputs
}
