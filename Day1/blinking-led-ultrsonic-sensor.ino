#define trigPin 9
#define echoPin 10
#define ledPin 7

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  // Trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo time
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2; // cm lo distance

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Condition: distance < 20 cm ante LED ON
  if (distance < 20) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(200);
}