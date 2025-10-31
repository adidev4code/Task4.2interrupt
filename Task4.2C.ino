// Code:

// ------------------- Pin Definitions -------------------
const int buttonPin = 2;   // Push button
const int trigPin   = 6;   // Ultrasonic TRIG
const int echoPin   = 5;   // Ultrasonic ECHO
const int led1Pin   = 8;   // LED1 (button)
const int led2Pin   = 9;   // LED2 (ultrasonic)

// ------------------- Global State -------------------
volatile bool led1State = LOW;   // Stores LED1 toggle state
volatile unsigned long startTime = 0;
volatile unsigned long echoDuration = 0;
volatile bool measureComplete = false;

// ------------------- ISR: Button -------------------
void buttonISR() {
  led1State = !led1State;
  digitalWrite(led1Pin, led1State);
  Serial.println("Button interrupt: LED1 toggled");
}

// ------------------- ISR: Ultrasonic Echo -------------------
void echoISR() {
  if (digitalRead(echoPin) == HIGH) {
    startTime = micros();   // record rising edge time
  } else {
    echoDuration = micros() - startTime; // record pulse width
    measureComplete = true;
  }
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
  attachInterrupt(digitalPinToInterrupt(echoPin), echoISR, CHANGE);
}

// ------------------- Ultrasonic Measurement -------------------
long measureDistance() {
  // Trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Wait for ISR to complete one echo measurement
  if (measureComplete) {
    measureComplete = false;
    long distance = echoDuration * 0.034 / 2;  // convert to cm
    return distance;
  }
  return -1;  // no valid reading yet
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
    digitalWrite(led1Pin, LOW); // optional: turn off LED1 if object close
    Serial.println("Ultrasonic: Object detected, LED2 ON");
  } else if (distance > 0) {
    digitalWrite(led2Pin, LOW);
  }

  delay(500);
}
