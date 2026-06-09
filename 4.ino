#include <AFMotor.h>

// Create single motor object
AF_DCMotor motor(1);   // Motor connected to M1

void setup() {
  Serial.begin(9600);

  // Set motor speed (0–255)
  motor.setSpeed(200);
}

void loop() {

  Serial.println("FORWARD");
  motor.run(FORWARD);
  delay(2000);

  Serial.println("BACKWARD");
  motor.run(BACKWARD);
  delay(2000);

  Serial.println("STOP");
  motor.run(RELEASE);
  delay(2000);
}