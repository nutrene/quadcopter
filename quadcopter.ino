#include<Servo.h>

const int MIN = 1130, MAX = 1400;
int counter = 0;
int left_x, left_y, right_x, right_y;
char buff[30];

Servo motor1, motor2, motor3, motor4;

int motor1_speed = 0, motor2_speed = 0, motor3_speed = 0, motor4_speed = 0;

void show(String a, String b, String c, String d){
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\t");
  Serial.println(d);
}

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
  if (Serial.available()) {
    buff[counter] = Serial.read();
    if (counter > 30 || buff[counter] == '\n') {
      buff[counter] = '\0';
      left_x=atoi(strtok(buff,","));
      left_y=atoi(strtok(NULL,","));
      right_x=atoi(strtok(NULL,","));
      right_y=atoi(strtok(NULL,","));
      counter = 0;
      show((String)left_x, (String)left_y, (String)right_x, (String)right_y);
    }else{
      counter++;
    }
  }
  
  // 0から1023の間で回転速度を決定する。
  motor1_speed = map(left_y, -472, 493, MIN, MAX);
  motor2_speed = map(left_y, -472, 493, MIN, MAX);
  motor3_speed = map(left_y, -472, 493, MIN, MAX);
  motor4_speed = map(left_y, -472, 493, MIN, MAX);

  // 各ブラシレスモーターへ回転速度を伝達。
  motor1.writeMicroseconds(motor1_speed);
  motor2.writeMicroseconds(motor2_speed);
  motor3.writeMicroseconds(motor3_speed);
  motor4.writeMicroseconds(motor4_speed);
}
