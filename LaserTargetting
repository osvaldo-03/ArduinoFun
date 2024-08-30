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
  // The example below assumes that you need the servo to sweep across an area
  // more directly aligned with detected objects within a closer range
  angle = map(distance, 0, 100, 0, 180);
  servo.write(angle);                 // Position the servo according to the calculated angle

  // Keep the laser on to point at the object when within range
  if (distance > 10 && distance < 100) {
    digitalWrite(laserPin, HIGH);
  } else {
    digitalWrite(laserPin, LOW);
  }

  delay(100);  // Short delay before repeating the measurement
}
