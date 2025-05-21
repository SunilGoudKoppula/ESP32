#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD I2C address to 0x27 or 0x3F for a 16x2 LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address, columns, rows

void setup() {
  lcd.init();        // Initialize the LCD
  lcd.backlight();   // Turn on the backlight

  // Display messages
  lcd.setCursor(0, 0);       // First line
  lcd.print("LCD Test OK!");
  
  lcd.setCursor(0, 1);       // Second line
  lcd.print("ESP32 Ready :)");
}

void loop() {
  // No repeated actions needed in loop
}
