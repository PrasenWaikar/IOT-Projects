const int LDR_PIN = A0;   // LDR is connected to analog pin A0
const int MOTOR_PIN = 9;  // Motor control pin
int lightValue;           // Variable to store light intensity

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  lightValue = analogRead(LDR_PIN);  // Read the light intensity
  int motorSpeed = map(lightValue, 0, 1023, 0, 255);  // Map light intensity to motor speed
  analogWrite(MOTOR_PIN, motorSpeed);  // Set the motor speed

  // Print the light intensity and motor speed to the serial monitor
  Serial.print("Light Intensity: ");
  Serial.print(lightValue);
  Serial.print(", Motor Speed: ");
  Serial.println(motorSpeed);

  delay(100);  // Delay for stability
}
