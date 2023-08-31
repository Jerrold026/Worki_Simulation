// Define the pins for the pushbutton and LEDs
#define buttonPin 4    // Connect buttonPin to pin 4
#define ledPin1 18     // Connect ledPin1 to pin 18

// Define the variable to store the button state
int buttonState = 0;

// Variables for LED blinking
int ledsOn = 0;

void setup() {
  // Set the button and LED pins as inputs and outputs
  pinMode(buttonPin, INPUT);
  pinMode(ledPin1, OUTPUT);
}

void loop() {
  // Read the state of the button
  buttonState = digitalRead(buttonPin);

  // If button is pressed, toggle the LEDs and start blinking
  if (buttonState == HIGH) {
    ledsOn = (ledsOn == 0) ? 1 : 0;
  }

  // Control the LEDs based on the button state
  if (ledsOn == 1) {
    // Toggle the LEDs state
    digitalWrite(ledPin1, !digitalRead(ledPin1));
    delay(500); // Delay for 500 milliseconds
  } else {
    // Turn off the LEDs
    digitalWrite(ledPin1, LOW);
    delay(500); // Delay for 500 milliseconds
  }
}
