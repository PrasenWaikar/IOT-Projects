// servo library include
#include <Servo.h>
//initialized servo
Servo servo;
// Defining pins for Clap Activated Robot
# define SAMPLE_WINDOW 100
int SoundSensor = A3;
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 9;
// Defining pins for Edge Avoidance Robot
const int enA = 1;
const int in1 = 10;
const int in2 = 11;
const int in3 = 12;
const int in4 = 13;
const int enB = 1;
const int IRR_S = A1; 
const int IRL_S = A2;
// Defining pins for Touchless DoorBell
const int buzzer = A2;
const int IRsensor = A1;
// Defining pins for Wall, Light & Hand Following Robots
const int m1 = 13;
const int m2 = 12;
const int n1 = 11;
const int n2 = 10;
const int enblem = 1;
const int enblen = 1;
const int LDR = A0;
// user function
int currentFunction = -1;

//setup code
void setup(){
  Serial.begin(9600);
  //clap robot
  pinMode(redPin, OUTPUT); //defining as an output pin
  pinMode(greenPin, OUTPUT);
  analogWrite(bluePin, 0);
  pinMode(SoundSensor, INPUT); //defining as an input pin

  //edge avoidance robot
  pinMode(enA, OUTPUT); //defining as an output pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode (enB, OUTPUT);
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);

  //touchless doorbell robot 
  servo.attach(3);
  pinMode(IRsensor,INPUT); //defining as an input pins
  digitalWrite(buzzer, HIGH);

  //wall, hand, light follower 
  pinMode(IRsensor, INPUT); //defining as an output pins
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(n1, OUTPUT);
  pinMode(n2, OUTPUT);
  pinMode(enblem, OUTPUT);
  pinMode(enblen, OUTPUT);
  delay(1000);
  Serial.println("Press 2 for Clap Robot ");
  Serial.println("Press 3 for Edge Avoidance Robot");
  Serial.println("Press 4 for Touchless Door Bell ");
  Serial.println("Press 5 for Light Follower Robot");
  Serial.println("Press 6 for Wall Follower Robot");
  Serial.println("Press 7 for Hand Follower Robot");
}

// main loop function
void loop(){
  if (Serial.available()>0){
  // Checking Availability Of Data In Serial COM Pins
  int userinput = Serial.read();
  switch(userinput){
    case '2': 
    // Clap Robot Activation Code
      currentFunction = 2;
      break;
    case '3':
    // Line Follower Robot Activation Code
      currentFunction = 3;
      break;
    case '4':
    // Touchless Doorbell Activation Code
      currentFunction = 4;
      break;
    case '5':
    // Light Follower Robot Activation Code
      currentFunction = 5;
      break;
    case '6':
    // Wall Follower Robot Activation Code
      currentFunction = 6;
      break;
    case '7':
    // Hand Follower Robot Activation Code
      currentFunction = 7;
      break;
    default:
      currentFunction = -1;
      break;
    }
  }
  // Clap Robot Activation Code
  if (currentFunction == 2){
    claprobot();
  // Edge Avoidance Robot Activation Code
  }else if (currentFunction == 3){
    edgeavoidance();
  // Touchless Doorbell Activation Code
  }else if (currentFunction == 4){
    touchlessbell();
  // Light Follower Robot Activation Code
  }else if (currentFunction == 5){
    lightfollower();
  // Wall Follower Robot Activation Code
  }else if (currentFunction == 6) {
    wallfollower();
  // Hand Follower Robot Activation Code
  }else if (currentFunction == 7){
    handfollower();
  }else{
  return;
  }
  // Checking Availability Of Data In Serial COM Pins
  if (Serial.available() > 0){
    int userInput = Serial.read();
    if(userInput != currentFunction){
      currentFunction = -1;
    }
  }
}

//function for clap activated robot
void claprobot(){
  if (currentFunction != 2){
    return;
  }
  unsigned long startMillis= millis();  
  int peakToPeak = 0;  
  unsigned int signalMax = 0;
  unsigned int signalMin = 1023;
  unsigned int c, y;
  int sample;

  while (millis() - startMillis < SAMPLE_WINDOW){
    // read data from the sound sensor
    sample = analogRead(SoundSensor);
    if (sample < 1024) {
    // if the sound sensor data is more than max signal
      if (sample > signalMax){
        signalMax = sample;  
      }
    // if sound sensor data is less than minimum signal
      else if (sample < signalMin){
        signalMin = sample;  
      }
    }
  }
  // calculate the peak range of sensor using maximum and minimum values
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  peakToPeak = peakToPeak+40;
  Serial.print("Clap Activated Robot. Sound Value: ");
  Serial.println(peakToPeak);
  analogWrite(redPin, 0);
  analogWrite(greenPin, 180);
  // if the signal peak is more than 200, turn on LED
  if(peakToPeak>200){
    analogWrite(redPin, 180);
    analogWrite(greenPin, 0);
    delay(2000);
  }
}

// function for edge avoidance robot
void edgeavoidance(){
  pinMode(IRR_S, INPUT);
  pinMode(IRL_S, INPUT);
  if (currentFunction!= 3) {
    return;
  }
  //Read data from both sensors
  int IRR_S_value = digitalRead(IRR_S);
  int IRL_S_value = digitalRead(IRL_S);
  Serial.print("Edge Avoidance. ");
  Serial.print("Sensor(L): ");
  Serial.print(IRL_S_value);
  Serial.print(" Sensor(R): ");
  Serial.println(IRR_S_value);
  // if both sensors detect ground
  if (IRR_S_value == 0 && IRL_S_value == 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // if only right sensor detects ground
    } else if (IRR_S_value == 1 && IRL_S_value == 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // if only left sensor detects ground
    } else if (IRR_S_value == 0 && IRL_S_value == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // if none of the sensors detect ground
    } else if (IRR_S_value == 1 && IRL_S_value == 1){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(2000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  delay(250);
}

//function for touchless doorbell
void touchlessbell(){
  pinMode(buzzer, OUTPUT);
  if (currentFunction!= 4){
    return;
  }
  // Detects the presence of obstacle on the IR
  int IRvalue = digitalRead(IRsensor); 
  Serial.print("Touchless Bell. IR Value:");
  Serial.println(IRvalue);
  // If presence detected then buzzer creates NOISE
  if (IRvalue == LOW){
    digitalWrite(buzzer, LOW);
    tone(2,444,100);
    delay(500);
    digitalWrite(buzzer, HIGH);
    servo.write(180);
    delay(500);
    Serial.println("Door Open");
  }
  /// If No Object Detected, Then No Sound Created 
  else{
    digitalWrite(buzzer, HIGH);
    servo.write (0);
    delay(500);
  }
  delay(250);
}

//function for light follower robot
void lightfollower(){
  if (currentFunction != 5){
    return;
  }
  int LDRdata = digitalRead(LDR);
  Serial.print("Light follower. LDR data: ");
  Serial.println(LDRdata);
  // If Sensor Senses Light, Then Move Forward
  if(LDRdata == 0){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(n1, HIGH);
  digitalWrite (n2, LOW);
  analogWrite(enblem, 255);
  analogWrite (enblen, 255);
  }
  /// If Sensor Doesn't Sense Any Light, Then No Movement 
  else if (LDRdata == 1){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(n1, LOW);
  digitalWrite (n2, LOW);
  }
  delay(250);
}

//function for wall follower robot
void wallfollower(){
  if (currentFunction != 6){
    return;
  }
  int IRdata = digitalRead(IRsensor);
  Serial.print("Wall Follower. IR data: ");
  Serial.println(IRdata); 
  // If Sensor Senses Wall, Then Move Forward
  if(IRdata == 0){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(n1, HIGH);
  digitalWrite(n2, LOW);
  analogWrite(enblem, 255);
  analogWrite(enblen, 255);
  }
  // If Sensor Doesn't Sense The Wall, Then No Movement
  else if(IRdata == 1){
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(n1, LOW);
  digitalWrite(n2, LOW);
  }
  delay(250);
}

//function for hand follower robot
void handfollower(){
  if (currentFunction != 7){
    return;
  }
  int IRdata = digitalRead(IRsensor);
  Serial.print("Hand Follower. IR data: ");
  Serial.println(IRdata); 
  // If Sensor Senses Object, Then Move Forward
  if(IRdata == 0){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(n1, HIGH);
  digitalWrite(n2, LOW);
  analogWrite(enblem, 255);
  analogWrite(enblen, 255);
  }
  // If Sensor Doesn't Sense The Object, Then No Movement
  else if(IRdata == 1){
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(n1, LOW);
  digitalWrite(n2, LOW);
  }
  delay(250);
}