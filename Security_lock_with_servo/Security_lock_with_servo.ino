#include <Servo.h>

Servo servoMotor;
int switchPin = 2;
int switchState = HIGH;
int prevSwitchState = HIGH;
int angle = 0;

void setup() {
  servoMotor.attach(9);
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  switchState = digitalRead(switchPin);

  if (switchState != prevSwitchState) {
    if (switchState == LOW) {
      angle = 90;
    } else {
      angle = 0;
    }
    servoMotor.write(angle);
    prevSwitchState = switchState;
    delay(50); // Debounce delay
  }
}
