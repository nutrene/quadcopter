const int left_x_pin = A1, left_y_pin = A0;
int left_x = 0, left_y = 0;

const int right_x_pin = A3, right_y_pin = A2;
int right_x = 0, right_y = 0;

void setup()
{
    Serial.begin(9600);
}
void loop()
{  
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
    delay(50);
}
