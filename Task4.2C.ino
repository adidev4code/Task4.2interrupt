// Code:

const int buttonPin = 2;   // Push button input
const int trigPin   = 6;   // Ultrasonic TRIG
const int echoPin   = 5;   // Ultrasonic ECHO (interrupt)
const int led1Pin   = 8;   // LED1 (button control)
const int led2Pin   = 9;   // LED2 (ultrasonic control)

volatile bool led1State = LOW;
volatile bool led2State = LOW;

// ---- Interrupt Service Routines ----
void buttonISR() {
  led1State = !led1State;
  digitalWrite(led1Pin, led1State);
  Serial.println("Button interrupt: LED1 toggled");
}

void echoISR() {
  led2State = !led2State;
  digitalWrite(led2Pin, led2State);
  Serial.println("Ultrasonic interrupt: LED2 toggled");
}

// ---- Setup Functions ----
void setupPins() {
  pinMode(buttonPin, INPUT);     
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void setupInterrupts() {
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(echoPin), echoISR, RISING);
}

// ---- Utility Functions ----
void triggerUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

// ---- Main Program ----
void setup() {
  Serial.begin(9600);
  while (!Serial);

  setupPins();
  setupInterrupts();

  Serial.println("System Ready - Waiting for interrupts...");
}

void loop() {
  triggerUltrasonic();   // Send ultrasonic pulse
  delay(200);            // Short delay between triggers
}
