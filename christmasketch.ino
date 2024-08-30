#define BUZZER_PIN 10     // Define the pin for the buzzer
const int LED2 = 2;      // Define the pin for the red LED
const int LED4 = 4;      // Define the pin for the green LED
const int LED7 = 7;      // Define the pin for the blue LED
#define TRIGGER_PIN 9     // Define the trigger pin for the ultrasonic sensor
#define ECHO_PIN   8      // Define the echo pin for the ultrasonic sensor
#define thresholdDistance 30  // Distance threshold for triggering the song (in centimeters)

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  int distance = getUltrasonicDistance();

  if (distance < thresholdDistance) {
    playChristmasSong();
  }

  delay(1000); // Delay between distance checks
}

int getUltrasonicDistance() {
  // Trigger ultrasonic sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Read the echo pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Convert the duration to distance (in centimeters)
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

void playChristmasSong() {
  // Frequencies for "We Wish You a Merry Christmas" melody
  float frequencies[] = {293.66, 392.00, 392.00, 440.00, 415.30, 329.63, 329.63, 329.63, 440.00, 440.00, 493.88, 466.16, 369.99, 293.66, 293.66, 493.88, 493.88, 523.25, 466.16, 392.00, 329.63, 293.66, 293.66, 329.63, 440.00, 466.16, 392.00};
  float noteDurations[] = {1000, 1000, 130 , 130 , 130 , 130 , 1000, 1000, 1000, 1000, 130, 130, 130, 130, 1000, 1000, 1000, 1000, 130, 130, 130, 130, 130, 1000, 130, 130, 1000};

  for (int i = 0; i < sizeof(frequencies) / sizeof(frequencies[0]); i++) {
    int noteDuration = noteDurations[i];

    // Set the color of each LED to HIGH based on the note's duration
    analogWrite(LED7, i % 2 == 0 ? 255 : 0);  // Green LED
    analogWrite(LED4, i % 3 == 0 ? 255 : 0);  // White LED
    analogWrite(LED2, i % 4 == 0 ? 255 : 0);  // Red LED

    tone(BUZZER_PIN, frequencies[i], noteDuration);
    
    delay(noteDuration);

    // Turn off all LEDs and stop the buzzer after playing each note
    analogWrite(LED2, LOW);
    analogWrite(LED4, LOW);
    analogWrite(LED7, LOW);
    noTone(BUZZER_PIN);

    // Pause between notes
    delay(50);
  }
}
  
