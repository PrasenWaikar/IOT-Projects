#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int IR_PIN = A1;
bool doorOpen = false;
Servo doorServo;
const int SERVO_PIN = 3;
const int BUZZER_PIN = 4;
const int LDR_PIN = A2;
const int RED_PIN = 6;
const int GREEN_PIN = 5;
const int BLUE_PIN = 9;
const int MOTOR_ENABLE_PIN_1 = 2;
const int MOTOR_ENABLE_PIN_2 = 3;
const int MOTOR_INPUT_PIN_1 = 10;
const int MOTOR_INPUT_PIN_2 = 11;
const int TEMPERATURE_THRESHOLD = 27;

void setup() {
 lcd.init();
 lcd.backlight();
 doorServo.attach(SERVO_PIN);
 doorServo.write(0);
 pinMode(IR_PIN, INPUT);
 pinMode(BUZZER_PIN, OUTPUT);
 pinMode(RED_PIN, OUTPUT);
 pinMode(GREEN_PIN, OUTPUT);
 pinMode(BLUE_PIN, OUTPUT);
 pinMode(MOTOR_ENABLE_PIN_1, OUTPUT);
 pinMode(MOTOR_ENABLE_PIN_2, OUTPUT);
 pinMode(MOTOR_INPUT_PIN_1, OUTPUT);
 pinMode(MOTOR_INPUT_PIN_2, OUTPUT);
 dht.begin();
 Serial.begin(9600);
}

void loop() {
 float temperature = dht.readTemperature();
 float humidity = dht.readHumidity();
 if (isnan(temperature) || isnan(humidity)) {
   Serial.println("Failed to read from DHT sensor!");
   return;
 }
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Temp: ");
 lcd.print(temperature);
 lcd.print(" C");
 lcd.setCursor(0, 1);
 lcd.print("Hum: ");
 lcd.print(humidity);
 lcd.print(" %");
 if (temperature > TEMPERATURE_THRESHOLD) {
   turnOnFan();
 } else {
   turnOffFan();
 }
 bool objectDetected = digitalRead(IR_PIN) == LOW;
 if (objectDetected && !doorOpen) {
   playDoorbell();
   openDoor();
   doorOpen = true;
 } else if (!objectDetected && doorOpen) {
   closeDoor();
   doorOpen = false;
 }
 int ldrValue = digitalRead(LDR_PIN);
 if (ldrValue == HIGH) {
   setRGBColor(255, 255, 255);
 } else {
   setRGBColor(0, 0, 0);
 }
 delay(100);
}

void turnOnFan() {
 digitalWrite(MOTOR_ENABLE_PIN_1, HIGH);
 digitalWrite(MOTOR_ENABLE_PIN_2, HIGH);
 digitalWrite(MOTOR_INPUT_PIN_1, HIGH);
 digitalWrite(MOTOR_INPUT_PIN_2, LOW);
}

void turnOffFan() {
 digitalWrite(MOTOR_ENABLE_PIN_1, LOW);
 digitalWrite(MOTOR_ENABLE_PIN_2, LOW);
 digitalWrite(MOTOR_INPUT_PIN_1, LOW);
 digitalWrite(MOTOR_INPUT_PIN_2, LOW);
}

void playDoorbell() {
 for (int i = 0; i < 3; i++) {
   tone(BUZZER_PIN, 1000, 200);
   delay(300);
 }
}

void openDoor() {
 doorServo.write(90);
}

void closeDoor() {
 doorServo.write(0);
}

void setRGBColor(int red, int green, int blue) {
 analogWrite(RED_PIN, red);
 analogWrite(GREEN_PIN, green);
 analogWrite(BLUE_PIN, blue);
}