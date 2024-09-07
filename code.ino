#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ALCOHOL_SENSOR A0
#define SPEED_SENSOR A1
#define ALCOHOL_THRESHOLD 500  // Set threshold value for alcohol sensor
#define SPEED_THRESHOLD 80     // Set threshold value for speed sensor
#define MOTOR_PIN 13           

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Initialize LCD display

void setup() {
  lcd.init();               // Initialize LCD display
  lcd.backlight();          // Turn on backlight
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);       // Initialize serial communication
}

void loop() {
  int alcoholValue = analogRead(ALCOHOL_SENSOR);  // Read alcohol sensor value
  int speedValue = analogRead(SPEED_SENSOR);      // Read speed sensor value

  lcd.setCursor(0, 0);                            // Set cursor to first row
  lcd.print("Alcohol: ");                        
  lcd.print(alcoholValue);                        // Display alcohol sensor value
  lcd.print("  ");                                // Clear remaining characters
  lcd.setCursor(0, 1);                            // Set cursor to second row
  lcd.print("Speed: ");
  lcd.print(speedValue);                          // Display speed sensor value
  lcd.print("   ");                               // Clear remaining characters

  if (alcoholValue > ALCOHOL_THRESHOLD) {          // Check if alcohol value is above threshold
    digitalWrite(MOTOR_PIN, LOW);                 // Stop the DC motor
    Serial.println("Alcohol limit exceeded. Motor stopped.");  // Send message to serial monitor
  }

  if (speedValue > SPEED_THRESHOLD) {              // Check if speed value is above threshold
    digitalWrite(MOTOR_PIN, LOW);                  // Stop the DC motor
    Serial.println("Speed limit exceeded. Motor stopped.");   // Send message to serial monitor
  }
}
