// Pin Definitions
#define IR_SENSOR_PIN 2
#define BUZZER_PIN 8

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize IR sensor pin as input
  pinMode(IR_SENSOR_PIN, INPUT);

  // Initialize buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);

  // Initially, turn off the buzzer
  noTone(BUZZER_PIN);
}

void loop() {
  // Read the IR sensor value
  int sensorValue = digitalRead(IR_SENSOR_PIN);

  // If no motion is detected, sound the alarm
  if (sensorValue == HIGH) {
    Serial.println("No motion detected!");
    tone(BUZZER_PIN, 1000); // Sound the buzzer at 1kHz
  } else {
    // Turn off the buzzer if motion is detected
    noTone(BUZZER_PIN);
  }

  // Wait a short delay between readings
  delay(100);
}
