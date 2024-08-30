int controlpin1 = 6 ;
int controlpin2 = 9;
int sensorPin = A0;

void setup() {
  Serial.begin(9600);

  pinMode(sensorPin, INPUT);
  pinMode(controlpin1, OUTPUT); 
  pinMode(controlpin2,OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  if (sensorValue <= 1) {
    analogWrite(controlpin1, 255);
    analogWrite(controlpin2, 255);

  } else {
   analogWrite(controlpin1, 0);
   analogWrite(controlpin2, 0);
  }
}
