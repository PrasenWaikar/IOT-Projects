const int triggerPin = 4; // Ultrasonic sensor trigger pin
const int echoPin = 2;   // Ultrasonic sensor echo pin
const int buzzerPin = 11; // Buzzer pin
const int thresholdDistance = 20; // Threshold distance in cm

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  long duration, distance;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;
  
  if (distance < thresholdDistance) {
    // Buzz the buzzer
    digitalWrite(buzzerPin, HIGH);
    delay(1000); // Buzz for 1 second
    digitalWrite(buzzerPin, LOW);
  }
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(100); // Delay between readings
}
