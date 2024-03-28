const int ledPin = 2;      // Pin for the LED
const int irSensorPin = A0; // Analog pin for the IR sensor
const int buzzerPin = 3;    // Pin for the buzzer

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(irSensorPin); // Read the IR sensor value
  int threshold = 500; // Set a threshold value (adjust as needed)

  if (sensorValue < threshold) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  } else {
    digitalWrite(ledPin, LOW); // Turn off the LED
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  }

  Serial.println(sensorValue); // Print sensor value for debugging
  delay(100); // Delay for stability
}
