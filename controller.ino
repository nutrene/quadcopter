const int left_x_pin = A1, left_y_pin = A0;
int left_x = 0, left_y = 0;

const int right_x_pin = A3, right_y_pin = A2;
int right_x = 0, right_y = 0;

////////// 調整器用 //////////
                  // M1   M2   M4
double weight[3] = {1.0, 1.0, 1.0};
int pos = 0;
bool ispush = false;
/////////////////////////////

void setup()
{
    Serial.begin(9600);
    
    ////////// 調整器用 //////////
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    ////////////////////////////
}

void loop(){
    ////////// 調整器用 //////////
    // -ボタン
    if(digitalRead(5) == HIGH && !ispush){
      weight[pos] -= 0.01;
      ispush = true;
    }
    // +ボタン
    if(digitalRead(7) == HIGH && !ispush){
      weight[pos] += 0.01;
      ispush = true;
    }
    // シフトボタン
    if(digitalRead(6) == HIGH && !ispush){
      pos = (pos + 1) % 3;
      ispush = true;
    }
    // スイッチから離した時の処理
    if(digitalRead(5) == LOW && digitalRead(6) == LOW && digitalRead(7) == LOW){
      ispush = false;
    }
    //////////////////////////////

    left_x = analogRead(left_x_pin)-512;
    left_y = analogRead(left_y_pin)-512;
    right_x = analogRead(right_x_pin)-512;
    right_y = analogRead(right_y_pin)-512;

    String string_left_x = (String)left_x + ',';
    String string_left_y = (String)left_y + ',';
    String string_right_x = (String)right_x + ',';
    String string_right_y = (String)right_y;

    
    Serial.print(string_left_x);
    Serial.print(string_left_y);
    Serial.print(string_right_x);
    Serial.println(string_right_y);

    ////////// 調整器用出力 //////////
    Serial.print((pos == 0 ? "@" : "") + (String)weight[0] + ',');
    Serial.print((pos == 1 ? "@" : "") + (String)weight[1] + ',');
    Serial.println((pos == 2 ? "@" : "") + (String)weight[2]);
    ///////////////////////////////
    
    delay(50);
}
