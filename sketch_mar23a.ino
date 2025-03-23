#include <Servo.h>

const int potPin = A0;  // 可變電阻
const int ledPin = 9;   // LED
const int ldrPin = A1;  // 光敏電阻
const int mercuryPin = 2; // 水銀開關
const int servoPin = 5;  // 伺服馬達

Servo myServo;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(mercuryPin, INPUT_PULLUP);  
  myServo.attach(servoPin);  
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int brightness = map(potValue, 0, 1023, 0, 255);
  analogWrite(ledPin, brightness);

  int ldrValue = analogRead(ldrPin);
  int mercuryState = digitalRead(mercuryPin); // 0 = 傾斜, 1 = 正常

  // 伺服馬達角度根據可變電阻調整
  int servoAngle = map(potValue, 0, 1023, 0, 180);

  // 若水銀開關傾斜，馬達擺動到特定位置
  if (mercuryState == 0) {
    myServo.write(180);
  } else {
    myServo.write(servoAngle);
  }

  Serial.print(brightness);
  Serial.print(",");
  Serial.print(ldrValue);
  Serial.print(",");
  Serial.print(mercuryState);
  Serial.print(",");
  Serial.println(servoAngle);

  delay(50);
}