const int LDR_PIN = A0;  // LDR connected to analog pin A0
const int BUZZER_PIN = 8;  // Buzzer connected to digital pin 8

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(LDR_PIN);  // Read the LDR sensor value
  Serial.println(lightLevel);  // Print the light level for debugging

  if (lightLevel > 800) {  // Adjust the threshold value as needed
    digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer
    delay(5000);  // Buzzer stays on for 5 seconds (adjust as needed)
    digitalWrite(BUZZER_PIN, LOW);  // Turn off the buzzer
  }

  delay(1000);  // Delay between readings
}
