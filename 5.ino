#include <Servo.h>

#define trigPin 2
#define echoPin 10

Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(9);   // D9
  myServo.write(0);

  Serial.begin(9600);
}

void loop() {

  long duration;
  long distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if(duration == 0){
    Serial.println("No Object");
    return;
  }

  distance = duration * 0.0345 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance < 10){
    myServo.write(90);
  }
  else{
    myServo.write(0);
  }

  delay(200);
}