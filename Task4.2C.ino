// Code:

// ------------------- Pin Definitions -------------------
const int buttonPin = 2;   // Push button input
const int trigPin   = 6;   // Ultrasonic TRIG
const int echoPin   = 5;   // Ultrasonic ECHO
const int led1Pin   = 8;   // LED1 controlled by button
const int led2Pin   = 9;   // LED2 controlled by ultrasonic

// ------------------- Global Variables -------------------
volatile bool led1State = LOW;   // Stores current state of LED1

// ------------------- Interrupt Service Routine -------------------
// This ISR triggers when button is pressed.
// It toggles LED1 ON/OFF and prints a message.
void buttonISR() {
  led1State = !led1State;
  digitalWrite(led1Pin, led1State);
  Serial.println("Button interrupt: LED1 toggled");
}

// ------------------- Pin Setup -------------------
// Configures all pins: button, ultrasonic, and LEDs.
// Initializes LED outputs as LOW (OFF).
void setupPins() {
  pinMode(buttonPin, INPUT_PULLUP);   // Button uses internal pull-up
  pinMode(trigPin, OUTPUT);           // Ultrasonic trigger pin
  pinMode(echoPin, INPUT);            // Ultrasonic echo pin
  pinMode(led1Pin, OUTPUT);           // LED1 output
  pinMode(led2Pin, OUTPUT);           // LED2 output

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
}

// ------------------- Interrupt Setup -------------------
// Attaches interrupt to button pin, triggers on FALLING edge.
void setupInterrupts() {
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
}

// ------------------- Ultrasonic Measurement -------------------
// Sends a trigger pulse and measures echo duration.
// Returns the calculated distance in centimeters.
long measureDistance() {
  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo pulse (timeout 30ms = ~5m max distance)
  long duration = pulseIn(echoPin, HIGH, 30000);

  // Convert time to distance in cm
  long distance = duration * 0.034 / 2;
  return distance;
}

// ------------------- Setup -------------------
// Initializes Serial, pins, and interrupts.
// Prints a ready message once setup is complete.
void setup() {
  Serial.begin(9600);
  while (!Serial);   // Wait for Serial Monitor to connect

  setupPins();
  setupInterrupts();

  Serial.println("System Ready - Waiting for interrupts...");
}

// ------------------- Main Loop -------------------
// Continuously measures distance using ultrasonic sensor.
// If object < 50cm, LED2 turns ON and logs event.
// Otherwise, LED2 remains OFF.
void loop() {
  long distance = measureDistance();

  if (distance > 0 && distance < 50) {   // Object detected
    digitalWrite(led2Pin, HIGH);
    Serial.println("Ultrasonic: Object detected, LED2 ON");
  } else {
    digitalWrite(led2Pin, LOW);
  }

  delay(500);   // Small delay before next measurement
}
