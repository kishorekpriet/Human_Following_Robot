#include <Servo.h>
#include <AFMotor.h>

#define LEFT_IR A0
#define RIGHT_IR A3
#define TRIG_PIN A1
#define ECHO_PIN A2

AF_DCMotor Motor1(1, MOTOR12_1KHZ);
AF_DCMotor Motor2(2, MOTOR12_1KHZ);
AF_DCMotor Motor3(3, MOTOR34_1KHZ);
AF_DCMotor Motor4(4, MOTOR34_1KHZ);

Servo myservo;
int pos = 0;
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  myservo.attach(10);

  for (pos = 90; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(15);
  }

  pinMode(RIGHT_IR, INPUT);
  pinMode(LEFT_IR, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  distance = readDistance();
  int Right_Value = digitalRead(RIGHT_IR);
  int Left_Value = digitalRead(LEFT_IR);

  Serial.print("R= ");
  Serial.print(Right_Value);
  Serial.print(" L= ");
  Serial.print(Left_Value);
  Serial.print(" D= ");
  Serial.println(distance);

  if ((Right_Value == 1) && (distance >= 10 && distance <= 30) && (Left_Value == 1)) {
    moveForward();
  } else if ((Right_Value == 0) && (Left_Value == 1)) {
    turnRight();
  } else if ((Right_Value == 1) && (Left_Value == 0)) {
    turnLeft();
  } else if ((Right_Value == 1) && (Left_Value == 1)) {
    stopMotors();
  } else if (distance > 5 && distance < 10) {
    stopMotors();
  } else if (distance < 5) {
    moveBackward();
  }
  delay(50);
}

long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(ECHO_PIN, HIGH);
  return duration / 29 / 2;
}

void moveForward() {
  Motor1.setSpeed(120);
  Motor1.run(FORWARD);
  Motor2.setSpeed(120);
  Motor2.run(FORWARD);
  Motor3.setSpeed(120);
  Motor3.run(FORWARD);
  Motor4.setSpeed(120);
  Motor4.run(FORWARD);
}

void moveBackward() {
  Motor1.setSpeed(120);
  Motor1.run(BACKWARD);
  Motor2.setSpeed(120);
  Motor2.run(BACKWARD);
  Motor3.setSpeed(120);
  Motor3.run(BACKWARD);
  Motor4.setSpeed(120);
  Motor4.run(BACKWARD);
}

void turnRight() {
  Motor1.setSpeed(200);
  Motor1.run(FORWARD);
  Motor2.setSpeed(200);
  Motor2.run(FORWARD);
  Motor3.setSpeed(100);
  Motor3.run(BACKWARD);
  Motor4.setSpeed(100);
  Motor4.run(BACKWARD);
}

void turnLeft() {
  Motor1.setSpeed(100);
  Motor1.run(BACKWARD);
  Motor2.setSpeed(100);
  Motor2.run(BACKWARD);
  Motor3.setSpeed(200);
  Motor3.run(FORWARD);
  Motor4.setSpeed(200);
  Motor4.run(FORWARD);
}

void stopMotors() {
  Motor1.setSpeed(0);
  Motor1.run(RELEASE);
  Motor2.setSpeed(0);
  Motor2.run(RELEASE);
  Motor3.setSpeed(0);
  Motor3.run(RELEASE);
  Motor4.setSpeed(0);
  Motor4.run(RELEASE);
}
