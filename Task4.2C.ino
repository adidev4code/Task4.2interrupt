// Code:

// ------------------- Pin Definitions -------------------
const int buttonPin = 2;   // Push button
const int trigPin   = 6;   // Ultrasonic TRIG
const int echoPin   = 5;   // Ultrasonic ECHO
const int led1Pin   = 8;   // LED1 (button)
const int led2Pin   = 9;   // LED2 (ultrasonic)

// ------------------- Global State -------------------
volatile bool led1State = LOW;   // Stores LED1 toggle state

// ------------------- ISR: Button -------------------
void buttonISR() {
  led1State = !led1State;
  digitalWrite(led1Pin, led1State);
  Serial.println("Button interrupt: LED1 toggled");
}

// ------------------- Pin Setup -------------------
void setupPins() {
  pinMode(buttonPin, INPUT_PULLUP);   
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
}

// ------------------- Interrupt Setup -------------------
void setupInterrupts() {
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
}

// ------------------- Ultrasonic Measurement -------------------
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);  // microseconds
  long distance = duration * 0.034 / 2;           // convert to cm
  return distance;
}

// ------------------- Setup -------------------
void setup() {
  Serial.begin(9600);
  while (!Serial);   
  setupPins();
  setupInterrupts();
  Serial.println("System Ready - Waiting for interrupts...");
}

// ------------------- Main Loop -------------------
void loop() {
  long distance = measureDistance();

  if (distance > 0 && distance < 50) {   
    digitalWrite(led2Pin, HIGH);
    Serial.println("Ultrasonic: Object detected, LED2 ON");
  } else {
    digitalWrite(led2Pin, LOW);
  }

  delay(500);
}
