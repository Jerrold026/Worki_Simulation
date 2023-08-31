#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int buttonPin = 27; // The push button pin
const int segmentPins[7] = {15, 23, 4, 2, 19, 18, 5}; // Pins connected to the seven-segment display
const int countdownTime = 1000; // Time interval for countdown (milliseconds)

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with default SDA and SCL pins

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT); // Set the segment pins as outputs
  }
  lcd.begin(); 
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Press P-Button");
  lcd.setCursor(4, 1);
  lcd.print("to start");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { // Check if the button is pressed
    countdown();
  }
}

void countdown() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Are you ready");
  lcd.setCursor(3, 1);
  lcd.print("SPARTANS?");
  lcd.clear();
  
  for (int i = 9; i >= 1; i--) {
    displayMessage(i);
    delay(countdownTime);
  }
  
  // Add a small delay before displaying "GO!!!!" to stabilize the message
  delay(500);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("GO!!!!");
  displaySevenSegment(0); // Turn off the display after the countdown is finished
}

void displayMessage(int number) {
  lcd.clear();
  
  if (number >= 7 && number <= 9) {
    lcd.setCursor(1, 0);
    lcd.print("Are you ready");
    lcd.setCursor(3, 1);
    lcd.print("SPARTANS?");
  } else if (number >= 4 && number <= 6) {
    lcd.setCursor(4, 0);
    lcd.print("On your");
    lcd.setCursor(5, 1);
    lcd.print("marks");
  } else if (number == 3) {
    lcd.setCursor(5, 0);
    lcd.print("Ready");
  } else if (number == 2) {
    lcd.setCursor(4, 0);
    lcd.print("Get Set");
  } else if (number == 1) {
    lcd.setCursor(5, 0);
    lcd.print("GO!!!!");
  }

  displaySevenSegment(number);
}

void displaySevenSegment(int number) {
  // Define segment patterns for each number (0 to 9)
  byte segments[][7] = {
    {0, 0, 0, 0, 0, 0, 1}, // 0
    {1, 0, 0, 1, 1, 1, 1}, // 1
    {0, 0, 1, 0, 0, 1, 0}, // 2
    {0, 0, 0, 0, 1, 1, 0}, // 3
    {1, 0, 0, 1, 1, 0, 0}, // 4
    {0, 1, 0, 0, 1, 0, 0}, // 5
    {0, 1, 0, 0, 0, 0, 0}, // 6
    {0, 0, 0, 1, 1, 1, 1}, // 7
    {0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 0, 0, 1, 0, 0}  // 9
  };

  if (number >= 0 && number <= 9) {
    // Display the number on the seven-segment display
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], segments[number][i]);
    }
  } else {
    // Turn off all segments if the number is out of range
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], LOW);
    }
  }
}
