#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);   // Servo signal wire connected to pin 9
}

void loop() {
  myServo.write(90);   // Rotate to 90 degrees
  delay(1000);

  myServo.write(0);    // Rotate back to 0 degrees
  delay(1000);
}