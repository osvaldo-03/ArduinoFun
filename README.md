# Laser Targeting System with Ultrasonic Sensor

## Project Overview

This project is a laser targeting system I created for fun. It uses an ultrasonic sensor to detect the distance to an object and a laser diode mounted on a servo motor to point at whatever is detected. The system automatically adjusts the laser's position based on the distance to the target, making it a simple yet interesting project for practicing Arduino, sensors, and servo motor control.

## Components Used
- **Arduino Uno**: The microcontroller used to control the system.
- **Ultrasonic Sensor (HC-SR04)**: Used to detect the distance to objects.
- **Servo Motor**: Adjusts the position of the laser based on the detected distance.
- **Laser Diode**: Emits a laser beam to point at the detected object.
- **Breadboard and Jumper Wires**: For connecting the components.

## Circuit Diagram

![Circuit Diagram](images/circuit-diagram.png)  
*(Note: Include an image of your circuit diagram in the `images` folder.)*

## Code Explanation

The code operates by sending a pulse from the ultrasonic sensor to measure the distance to an object. The distance is then mapped to an angle, which adjusts the position of the servo motor. The laser diode is turned on when an object is detected within a specified range, and the servo motor points the laser at the detected object.

### Code Breakdown

```cpp
#include <Servo.h>

Servo servo;                   // Create a servo object
const int trigPin = 7;         // Pin connected to the ultrasonic sensor's trigger pin
const int echoPin = 8;         // Pin connected to the ultrasonic sensor's echo pin
const int laserPin = 10;       // Pin connected to the laser
long duration;                 // Variable to store the duration of the echo pulse
int distance;                  // Calculated distance based on the duration
int angle;                     // Servo angle corresponding to the distance

void setup() {
  pinMode(trigPin, OUTPUT);    // Set the TRIG pin as output
  pinMode(echoPin, INPUT);     // Set the ECHO pin as input
  pinMode(laserPin, OUTPUT);   // Set the laser pin as output
  servo.attach(9);             // Attach the servo to pin 9
  Serial.begin(9600);          // Start serial communication at 9600 baud rate
}

void loop() {
  digitalWrite(trigPin, LOW);  // Clear the TRIG pin
  delayMicroseconds(2);        // Short delay before sending a pulse
  digitalWrite(trigPin, HIGH); // Send a 10-microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  // Measure the length of the incoming pulse
  distance = duration * 0.034 / 2;    // Calculate the distance (in cm)

  // Adjust the mapping function as needed based on your physical setup
  angle = map(distance, 0, 100, 0, 180);  // Map distance to an angle for the servo
  servo.write(angle);                     // Position the servo according to the calculated angle

  // Keep the laser on to point at the object when within range
  if (distance > 10 && distance < 100) {
    digitalWrite(laserPin, HIGH);
  } else {
    digitalWrite(laserPin, LOW);
  }

  delay(100);  // Short delay before repeating the measurement
}


