#include <Servo.h>

Servo radarServo;

const int trigPin = 8;
const int echoPin = 7;
const int servoPin = 9;

long duration;
int distance;

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return 400;  // No object detected
  }

  distance = duration * 0.034 / 2;

  if (distance > 400) {
    distance = 400;
  }

  return distance;
}

void scanAtAngle(int angle) {
  radarServo.write(angle);
  delay(50);

  int d = getDistance();

  // Format:
  // angle,distance
  Serial.print(angle);
  Serial.print(",");
  Serial.println(d);
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  radarServo.attach(servoPin);
  radarServo.write(90);

  delay(1000);
}

void loop() {

  // Scan left to right
  for (int angle = 0; angle <= 180; angle += 2) {
    scanAtAngle(angle);
  }

  // Scan right to left
  for (int angle = 180; angle >= 0; angle -= 2) {
    scanAtAngle(angle);
  }
}
