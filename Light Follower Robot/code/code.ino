// Define LDR pin
int ldrPin = A0;

// Define motor driver pins
int leftMotorPin1 = 2;
int leftMotorPin2 = 3;
int rightMotorPin1 = 4;
int rightMotorPin2 = 5;

// Define motor speed
int motorSpeed = 150;

void setup() {
  // Initialize motor driver pins as outputs
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
}

void loop() {
  // Read LDR value
  int ldrValue = analogRead(ldrPin);
  
  // Check if light is on the left side
  if (ldrValue < 500) {
    // Turn left
    analogWrite(leftMotorPin1, motorSpeed);
    analogWrite(leftMotorPin2, 0);
    analogWrite(rightMotorPin1, 0);
    analogWrite(rightMotorPin2, motorSpeed);
  }
  // Check if light is on the right side
  else if (ldrValue > 700) {
    // Turn right
    analogWrite(leftMotorPin1, 0);
    analogWrite(leftMotorPin2, motorSpeed);
    analogWrite(rightMotorPin1, motorSpeed);
    analogWrite(rightMotorPin2, 0);
  }
  // Light is in the center
  else {
    // Move forward
    analogWrite(leftMotorPin1, motorSpeed);
    analogWrite(leftMotorPin2, 0);
    analogWrite(rightMotorPin1, motorSpeed);
    analogWrite(rightMotorPin2, 0);
  }
}
