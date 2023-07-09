#include <Arduino.h>

#define YELLOWPIN 6
#define BLUEPIN 2
#define MOTEN 5
#define MOTO1 4
#define MOTO2 3

volatile long degrees;

void StopMotor();
void MoveMotor(int speed);
void CountDegrees();
void MoveToPosition(int position);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(YELLOWPIN, INPUT);
  pinMode(BLUEPIN, INPUT);
  pinMode(MOTEN, OUTPUT);
  pinMode(MOTO1, OUTPUT);
  pinMode(MOTO2, OUTPUT);

  degrees = 0;

  attachInterrupt(digitalPinToInterrupt(BLUEPIN), CountDegrees, CHANGE);  
}

void loop() {
  static long deg = 0;

  if (degrees != deg) {
    Serial.println(degrees);
    deg = degrees;
  }
  MoveToPosition(180);
}

void MoveToPosition(int position) {
  while (degrees != position) {
    if (degrees < position) {
      MoveMotor(100);
    } else {
      MoveMotor(-100);
    }
  }
  StopMotor();
}


void CountDegrees() {
  if (digitalRead(YELLOWPIN) == digitalRead(BLUEPIN)) {
    degrees++;
  } else {
    degrees--;
  }
  if (degrees > 360) {
    degrees -= 360;
  } else if (degrees < 0) {
    degrees += 360;
  }
}

void MoveMotor(int speed) {
  if (speed > 100) speed = 100;
  if (speed < -100) speed = -100;

  analogWrite(MOTEN, int(abs(speed)*2.55));

  if (speed > 0) {
    digitalWrite(MOTO1, HIGH);
    digitalWrite(MOTO2, LOW);
  } else {
    digitalWrite(MOTO1, LOW);
    digitalWrite(MOTO2, HIGH);
  }
}

void StopMotor() {
  digitalWrite(MOTO1, LOW);
  digitalWrite(MOTO2, LOW);
}
