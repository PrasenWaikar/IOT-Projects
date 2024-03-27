int ir_Sensor = 2; // connect ir sensor module to Arduino pin 2
int ledPin = 8;    // connect LED to Arduino pin 8

void setup()
{
  Serial.begin(9600); // Start Serial Communication at 9600 Baud Rate

  pinMode(ir_Sensor, INPUT); // Declaring IR Sensor pin as a Input
  pinMode(ledPin, OUTPUT); // Declaring LED Pin as a Output
}

void loop()
{

  int sensorStatus = digitalRead(ir_Sensor);

  if (sensorStatus == 0)
  {
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("An Object is Detected.!"); // Print An Object is Detected.! on the serial monitor window
  }
  else
  {
    digitalWrite(ledPin, LOW); // Turn off LED
    Serial.println("No Objects were Detected.!"); // Print No Objects were Detected.! on the serial monitor window
  }

  delay(500);
}
