#include <Servo.h>
#include <NewPing.h>

// Define constants
const int IN1 = 8;
const int IN2 = 9;
const int SERVO_PIN_DIR = 10;
const int SERVO_PIN_SPEED = 11;
const int SERVO_MIN_ANGLE = 55;
const int SERVO_MAX_ANGLE = 135;
const int R_S = 7;
const int L_S = 6;
const int TRIGGER_PIN = 5;
const int ECHO_PIN = 3;
const int MAX_DISTANCE = 400;

Servo servo_dir;
Servo servo_speed;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Define variables
int speed = 0;
float distance;

void forward() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
}

void backwards() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
}

void stopMotor() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
}

void autoParking() {
  int parcat = 0;
  while (parcat == 0) {
    forward();
    distance = sonar.ping_cm();
    if (distance < 20) {
      stopMotor();
      parcat = 1;
    }
  }
  delay(100);
  servo_dir.write(SERVO_MAX_ANGLE);
  forward();
  delay(210);
  stopMotor();
  servo_dir.write(SERVO_MIN_ANGLE);
  backwards();
  delay(1500);
  stopMotor();
}

void setup() {
  // Initialize motor control pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(R_S, INPUT);
  pinMode(L_S, INPUT);

  // Attach servo to pin 10 and 11
  servo_dir.attach(SERVO_PIN_DIR);
  servo_speed.attach(SERVO_PIN_SPEED);
  digitalWrite(13, HIGH);

  Serial.begin(9600);
  // bluetoothSerial.begin(9600);
}

void loop() {
  // Check if there is any data available on the Bluetooth module
  if (Serial.available()) {
    char command = Serial.read();
    stopMotor();
    servo_dir.write(95);
    servo_speed.write(speed);
    // Check the command received
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        backwards();
        break;
      case 'S':
        stopMotor();
        break;
      case 'L':
        servo_dir.write(SERVO_MAX_ANGLE);
        break;
      case 'R':
        servo_dir.write(SERVO_MIN_ANGLE);
        break;
      case 'G':
        servo_dir.write(SERVO_MAX_ANGLE);
        forward();
        break;
      case 'I':
        servo_dir.write(SERVO_MIN_ANGLE);
        forward();
        break;
      case 'H':
        servo_dir.write(SERVO_MAX_ANGLE);
        backwards();
        break;
      case 'J':
        servo_dir.write(SERVO_MIN_ANGLE);
        backwards();
        break;
      case '0':
        speed = 0;
        break;
      case '1':
        speed = 18;
        break;
      case '2':
        speed = 36;
        break;
      case '3':
        speed = 54;
        break;
      case '4':
        speed = 72;
        break;
      case '5':
        speed = 90;
        break;
      case '6':
        speed = 108;
        break;
      case '7':
        speed = 126;
        break;
      case '8':
        speed = 144;
        break;
      case '9':
        speed = 162;
        break;
      case 'q':
        speed = 180;
        break;
      case 'W':
        autoParking();
        break;
      default:
        break;
    }
  }
}