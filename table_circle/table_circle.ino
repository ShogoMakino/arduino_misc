#include <Servo.h>
Servo servo1;
Servo servo2;
const float pi=3.14159;

int servo1_origin=80;
int servo2_origin=80;
int amplitude = 60;
double cnt = 0;
int cnt2 = 0;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(9);
  servo2.attach(10);
  servo1.write(servo1_origin);
  servo2.write(servo2_origin);
}

void loop() {
  cnt += 0.08;
  if(cnt >= 2 * pi){ cnt -= 2 * pi; cnt2++;}
  servo1.write(servo1_origin + amplitude * sin(cnt));
  servo2.write(servo2_origin + amplitude * cos(cnt));
  // put your main code here, to run repeatedly:
  delay(10);
}
