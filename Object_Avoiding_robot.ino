#include <AFMotor.h>
#include <Servo.h>

// Pin definitions for ultrasonic sensor
#define ECHO_PIN A4
#define TRIG_PIN A5

// Motor setup
AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_64KHZ);
AF_DCMotor motor4(4, MOTOR12_64KHZ);

// Servo object
Servo myServo;

// Distance variables
int distanceLeft = 0, distanceFront = 0, distanceRight = 0;
const int safeDistance = 20;  // Minimum safe distance in cm

//===============================================================================
//  Initialization
//===============================================================================
void setup() {
  Serial.begin(9600);
  Serial.println("Robot Starting...");

  myServo.attach(10);
  myServo.write(90); // Center position

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set motor speed (0-255)
  motor1.setSpeed(180);
  motor2.setSpeed(180);
  motor3.setSpeed(180);
  motor4.setSpeed(180);
}

//===============================================================================
//  Main Loop
//===============================================================================
void loop() {
  distanceFront = measureDistance();

  Serial.print("Front Distance = ");
  Serial.println(distanceFront);

  if (distanceFront > safeDistance) {
    moveForward();
  } else {
    stopMotors();
    scanAndAvoid();
  }
}

//===============================================================================
//  Measure Distance using Ultrasonic Sensor
//===============================================================================
int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration / 29 / 2; // Convert to cm
}

//===============================================================================
//  Motor Control Functions
//===============================================================================
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

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
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

//===============================================================================
//  Scan Environment using Servo + Sensor
//===============================================================================
void scanAndAvoid() {
  // Look Right
  myServo.write(0);
  delay(300);
  distanceRight = measureDistance();

  // Look Left
  myServo.write(170);
  delay(500);
  distanceLeft = measureDistance();

  // Return to center
  myServo.write(90);
  delay(300);

  compareDistances();
}

//===============================================================================
//  Compare Left and Right Distances and Act
//===============================================================================
void compareDistances() {
  if (distanceLeft > distanceRight) {
    Serial.println("Turning Left");
    turnLeft();
    delay(350);
  } else if (distanceRight > distanceLeft) {
    Serial.println("Turning Right");
    turnRight();
    delay(350);
  } else {
    Serial.println("Backing Up and Turning Left");
    moveBackward();
    delay(300);
    turnLeft();
    delay(500);
  }

  stopMotors();  // Optional: stop after maneuver
}
