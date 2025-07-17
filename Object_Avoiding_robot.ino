#include <AFMotor.h>
#include <Servo.h>

#define ECHO_PIN A4
#define TRIG_PIN A5

Servo myservo;

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_64KHZ);
AF_DCMotor motor4(4, MOTOR12_64KHZ);

const int THRESHOLD_DISTANCE = 20; // Distance threshold in cm
long distance_F, distance_L, distance_R;

void setup() {
  Serial.begin(9600);
  Serial.println("System Initialized");

  myservo.attach(10);
  myservo.write(90); // Face forward

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set initial speed
  setMotorSpeed(180);
}

void loop() {
  distance_F = getDistance();
  Serial.print("Front Distance: ");
  Serial.println(distance_F);

  if (distance_F > THRESHOLD_DISTANCE) {
    moveForward();
  } else {
    stopMotors();
    scanSidesAndReact();
  }
}

//================= Motor Helpers ===================
void setMotorSpeed(int speed) {
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
}

void moveForward() {
  Serial.println("Moving Forward");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void stopMotors() {
  Serial.println("Stopping");
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

//================= Distance Sensor ===================
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000); // 25ms timeout (~4m)
  if (duration == 0) return 999; // No echo received
  return duration / 58.2; // Convert to cm
}

//================= Scanning ===================
void scanSidesAndReact() {
  Serial.println("Scanning...");

  myservo.write(20); // Look right
  delay(500);
  distance_R = getDistance();
  Serial.print("Right: ");
  Serial.println(distance_R);

  myservo.write(160); // Look left
  delay(500);
  distance_L = getDistance();
  Serial.print("Left: ");
  Serial.println(distance_L);

  myservo.write(90); // Center
  delay(300);

  decideDirection();
}

//================= Decision Making ===================
void decideDirection() {
  if (distance_L > distance_R && distance_L > THRESHOLD_DISTANCE) {
    Serial.println("Turning Left");
    turnLeft();
  } else if (distance_R > distance_L && distance_R > THRESHOLD_DISTANCE) {
    Serial.println("Turning Right");
    turnRight();
  } else {
    Serial.println("Reversing");
    moveBackward();
    delay(500);
    turnLeft(); // Default to left
  }
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(400);
  stopMotors();
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(400);
  stopMotors();
}
