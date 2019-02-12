// 調整器完成
#include<Servo.h>

const int MIN = 1130, MAX = 2000, ATTENUATION_CONSTANT = 2, EMERGENCY_STOP_NUM = 60;
int counter = 0, left_x, left_y, right_x, right_y, motor1_speed = MIN, motor2_speed = MIN, motor3_speed = MIN, motor4_speed = MIN;
int emergency_allmotors_speed, emergency_stop_counter = -999999999999;
double w1, w2, w4;
char buff[30];
Servo motor1, motor2, motor3, motor4;

void Debug_show(String number, String a, String b, String c, String d){
  Serial.print(number + ": ");
  Serial.print("\t");
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\t");
  Serial.print(d);
  Serial.println();
}

void show(String a, String b, String c, String d){
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\t");
  Serial.print(d);
}

void setup() {
  motor1.attach(10);
  motor2.attach(11);
  motor3.attach(12);
  motor4.attach(13);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    buff[counter] = Serial.read();
    if (counter > 60 || buff[counter] == '\n') {
      buff[counter] = '\0';
      left_x=atoi(strtok(buff,","));
      left_y=atoi(strtok(NULL,","));
      right_x=atoi(strtok(NULL,","));
      right_y=atoi(strtok(NULL,","));
      w1 = ((String)strtok(NULL,",")).toDouble();
      w2 = ((String)strtok(NULL,",")).toDouble();
      w4 = ((String)strtok(NULL,",")).toDouble();
      counter = 0;
      
      //show((String)left_x, (String)left_y, (String)right_x, (String)right_y);
      //Serial.print("\t");
      show((String)motor1_speed, (String)motor2_speed, (String)motor3_speed, (String)motor4_speed);
      Serial.println();
      //Serial.print("\t");
      //show((String)w1, (String)w2, (String)1.0, (String)w4);
      //Serial.print("\t");
      //Serial.println();
    }else{
      counter++;
    }
    
    motor1_speed = map(left_y, -472, 493, MIN, MAX);
    motor2_speed = map(left_y, -472, 493, MIN, MAX);
    motor3_speed = map(left_y, -472, 493, MIN, MAX);
    motor4_speed = map(left_y, -472, 493, MIN, MAX);

    // 回転運動
    if(left_x <= -130){
      left_x = max(-430, left_x);
      double r = abs(left_x) / 1500.0 + 137 / 150.0;
      motor1_speed *= r;
      motor3_speed *= r;
      motor2_speed *= 2 - r;
      motor4_speed *= 2 - r;
    }
    if(130 <= left_x){
      left_x = min(430, left_x);
      double r = left_x / 1500.0 + 137 / 150.0;
      motor2_speed *= r;
      motor4_speed *= r;
      motor1_speed *= 2 - r;
      motor3_speed *= 2 - r;
    }

    // 平行移動(前後)
    if(right_y <= -130){
      right_y = max(-430, right_y);
      double s = abs(right_y) / 1500.0 + 137 / 150.0;
      motor1_speed *= s;
      motor2_speed *= s;
      motor3_speed *= 2 - s;
      motor4_speed *= 2 - s;
    }
    if(130 <= right_y){
      right_y = min(430, right_y);
      double s = right_y / 1500.0 + 137 / 150.0;
      motor1_speed *= 2 - s;
      motor2_speed *= 2 - s;
      motor3_speed *= s;
      motor4_speed *= s;
    }

    // 平行移動(左右)
    if(right_x <= -130){
      right_x = max(-430, right_x);
      double s = abs(right_x) / 1500.0 + 137 / 150.0;
      motor1_speed *= 2 - s;
      motor2_speed *= s;
      motor3_speed *= s;
      motor4_speed *= 2 - s;
    }
    if(130 <= right_x){
      right_x = min(430, right_x);
      double s = right_x / 1500.0 + 137 / 150.0;
      motor1_speed *= s;
      motor2_speed *= 2 - s;
      motor3_speed *= 2 - s;
      motor4_speed *= s;
    }

    
    motor1_speed *= w1;
    motor2_speed *= w2;
    motor4_speed *= w4;
    
    emergency_stop_counter = 0;
    
  }else{
    emergency_stop_counter++;
    if(emergency_stop_counter >= EMERGENCY_STOP_NUM){
      motor1_speed = 0;
      motor2_speed = 0;
      motor3_speed = 0;
      motor4_speed = 0;
    }
  }
  //show((String)motor1_speed, (String)motor2_speed, (String)motor3_speed, (String)motor4_speed);
  //Serial.println();

  ///// 各ブラシレスモーターへ回転速度を送信する。 /////
  motor1.writeMicroseconds(motor1_speed);
  motor2.writeMicroseconds(motor2_speed);
  motor3.writeMicroseconds(motor3_speed);
  motor4.writeMicroseconds(motor4_speed);
}
