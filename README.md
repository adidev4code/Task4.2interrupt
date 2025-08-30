# Task 4.2C - Arduino Nano 33 IoT Multiple Interrupts

## 📌 Overview
In this task, we implement **multiple interrupt handling** on the Arduino Nano 33 IoT.  
Interrupts allow the microcontroller to react immediately to external events without relying on continuous polling inside the `loop()`.  
This makes embedded systems more **efficient, responsive, and event-driven**.  

We are using:  
1. A **push button** → toggles LED1 when pressed.  
2. An **ultrasonic sensor** → its Echo pin acts as a digital trigger, toggling LED2 when an object is detected.  

---

## 🛠️ Requirements

### Hardware
- Arduino Nano 33 IoT  
- Push button (with resistor)  
- Ultrasonic sensor (HC-SR04 or equivalent)  
- 2x LEDs with resistors (220Ω)  
- Breadboard and jumper wires  

### Software
- Arduino IDE or Arduino Web IDE  
- Serial Monitor (set to 9600 baud)  

---

## ⚡ Circuit Connections

### Push Button
- One leg → Pin D2  
- Other leg → GND  
- Use pull-down resistor for stable input  

### Ultrasonic Sensor
- VCC → 3.3V  
- GND → GND  
- TRIG → D6  
- ECHO → D5 (used as interrupt pin)  

### LEDs
- LED1 → Pin D8 (through 220Ω resistor to GND)  
- LED2 → Pin D9 (through 220Ω resistor to GND)  

---

## 📑 Implementation Approach

The task requires **two interrupts**:  

- **Interrupt 1 (Push button, D2):**  
  Fires when the button is pressed. Toggles LED1 and logs a message to Serial Monitor.  

- **Interrupt 2 (Ultrasonic Echo, D5):**  
  Fires whenever the Echo pin goes HIGH due to an object reflection. Toggles LED2 and logs a message.  

The `loop()` function is only responsible for sending periodic trigger pulses to the ultrasonic sensor.  
All event handling (button and sensor signals) is done via **interrupts**.  

---

## 🚀 Step-by-Step Procedure

### Step 1: Wiring
1. Connect push button between D2 and GND (with pull-down resistor).  
2. Connect ultrasonic sensor:  
   - TRIG → D6  
   - ECHO → D5  
   - VCC → 3.3V  
   - GND → GND  
3. Connect LEDs:  
   - LED1 → D8 → resistor → GND  
   - LED2 → D9 → resistor → GND  

### Step 2: Upload Code
1. Open Arduino IDE.  
2. Create a new file `Task4.2C.ino`.  
3. Copy the provided source code into this file.  
4. Select **Arduino Nano 33 IoT** as the board.  
5. Upload the sketch to the board.  

### Step 3: Test the Setup
1. Open Serial Monitor at 9600 baud.  
2. Press the button → LED1 should toggle, and a message will appear.  
3. Place your hand in front of the ultrasonic sensor → LED2 should toggle, and a message will appear.  

---

## 🎯 Learning Outcomes
By completing this task, you will:  
- Understand how to configure and use **attachInterrupt()** on the Nano 33 IoT.  
- Learn how to handle **multiple interrupt sources simultaneously**.  
- Appreciate the benefits of **event-driven programming** compared to polling loops.  

This makes your embedded system more **responsive, efficient, and professional**.
