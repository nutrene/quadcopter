#include<Servo.h>

const int MIN = 1130, MAX = 1400;

Servo motor1, motor2, motor3, motor4;

void setup() {
  // PIN7=MOTOR1, PIN8=MOTOR2, PIN12=MOTOR3, PIN13=MOTOR4;
  motor1.attach(7);
  motor2.attach(8);
  motor3.attach(12);
  motor4.attach(13);
  //motor1.writeMicroseconds(1000);
  Serial.begin(9600);
}

void loop() {
  int motor1_speed, motor2_speed, motor3_speed, motor4_speed;
  // 0から1023の間で回転速度を決定する。
  motor1_speed = map(analogRead(A0), 0, 1023, MIN, MAX);
  motor2_speed = map(analogRead(A1), 0, 1023, MIN, MAX);
  motor3_speed = map(analogRead(A2), 0, 1023, MIN, MAX);
  motor4_speed = map(analogRead(A3), 0, 1023, MIN, MAX);
  
  Serial.print(motor1_speed, DEC);
  Serial.print("\t");
  Serial.print(motor2_speed, DEC);
  Serial.print("\t");
  Serial.print(motor3_speed, DEC);
  Serial.print("\t");
  Serial.print(motor4_speed, DEC);
  Serial.print("\t");
  Serial.write("\n");

  // 各ブラシレスモーターへ回転速度を伝達。
  motor1.writeMicroseconds(motor1_speed);
  motor2.writeMicroseconds(motor2_speed);
  motor3.writeMicroseconds(motor3_speed);
  motor4.writeMicroseconds(motor4_speed);
}
