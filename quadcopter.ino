#include<Servo.h>

const int MIN = 1130, MAX = 2000, ATTENUATION_CONSTANT = 2, EMERGENCY_STOP_NUM = 60;
int counter = 0;
int left_x, left_y, right_x, right_y;
char buff[30];

Servo motor1, motor2, motor3, motor4;

int motor1_speed = 0, motor2_speed = 0, motor3_speed = 0, motor4_speed = 0;
int emergency_allmotors_speed;
int emergency_stop_counter = -999999999999;

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
  motor1.attach(10);
  motor2.attach(11);
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

    // 左アナログスティックのY軸の入力を全てのモーターの回転速度に反映して垂直移動を行う。
    motor1_speed = map(left_y, -472, 493, MIN, MAX);
    motor2_speed = map(left_y, -472, 493, MIN, MAX);
    motor3_speed = map(left_y, -472, 493, MIN, MAX);
    motor4_speed = map(left_y, -472, 493, MIN, MAX);
    ///////////////////////////////////////////////////

    // 左アナログスティックのX軸の入力を全てのモーターに反映して回転運動を行う。
    if(left_x <= -130){
      left_x = max(-430, left_x); // left_xの最小値は-430に補正される。
      double r = abs(left_x) / 1500.0 + 137 / 150.0;
      motor1_speed *= r;
      motor3_speed *= r;
      motor2_speed *= 2 - r;
      motor4_speed *= 2 - r;
    }
    if(130 <= left_x){
      left_x = min(430, left_x); // left_xの最小値は+430に補正される。
      double r = left_x / 1500.0 + 137 / 150.0;
      motor2_speed *= r;
      motor4_speed *= r;
      motor1_speed *= 2 - r;
      motor3_speed *= 2 - r;
    }

    ///// 緊急停止用カウント変数のカウントを0に戻す。 /////
    emergency_stop_counter = 0;
    ///////////////////////////////////////////////
    
  }else{

    ///// 緊急停止用カウント変数にカウントする。 /////
    emergency_stop_counter++;
    Serial.print("Debug: ");
    Serial.println(emergency_stop_counter);

    ///// 通信失敗が定数EMERGENCY_STOP_NUM回続いた場合はモーターの回転を停止する。 /////
    if(emergency_stop_counter >= EMERGENCY_STOP_NUM){
      Serial.print("EMERGENCY STOPPING NOW.");
      Serial.print(emergency_stop_counter);
      Serial.print("\n");

      /*
      // emergency_allmotors_speedはホバリングが可能な回転数にするべきか。
      if(emergency_stop_counter == EMERGENCY_STOP_NUM){
        emergency_allmotors_speed = max(motor1_speed, max(motor2_speed, max(motor3_speed, motor4_speed)));
        motor1_speed = emergency_allmotors_speed;
        motor2_speed = emergency_allmotors_speed;
        motor3_speed = emergency_allmotors_speed;
        motor4_speed = emergency_allmotors_speed;
      }
      */

      motor1_speed = 0;
      motor2_speed = 0;
      motor3_speed = 0;
      motor4_speed = 0;
    }
    ///////////////////////////////////////////////////////////////////////
    
  }

  ///// 各ブラシレスモーターへ回転速度を送信する。 /////
  motor1.writeMicroseconds(motor1_speed);
  motor2.writeMicroseconds(motor2_speed);
  motor3.writeMicroseconds(motor3_speed);
  motor4.writeMicroseconds(motor4_speed);
  //////////////////////////////////////////////

  //delay(33);
}
