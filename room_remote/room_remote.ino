
#include <IRremote.h>
#include <Servo.h>

#define SERVO_NUM 2
#define CODE_NUM 2
#define STATE_NUM 3
#define RECV_PIN 2
#define LED_PWM_PIN 3
int servo_pin[SERVO_NUM] = {9, 10};
unsigned long ir_code[SERVO_NUM][CODE_NUM] = {{0x8F71BE4, 0x8F71EE1}, {0x8F71FE0, 0x8F71AE5}};
int angle[SERVO_NUM][STATE_NUM] = {{70, 110, 90}, {75, 115, 95}};

IRrecv irrecv(RECV_PIN);
decode_results results;
Servo servo[SERVO_NUM];

void setup()
{
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  Serial.println("Enabling Servo");
  for(int i = 0; i < SERVO_NUM; i++){
    servo[i].attach(servo_pin[i]);
    servo[i].write(angle[i][2]);
  }
  delay(1000);
  for(int i = 0; i < SERVO_NUM; i++){
    servo[i].detach();
  }
  Serial.println("Enabled Servo");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    for(int i = 0; i < SERVO_NUM; i++){
      for(int j = 0; j < CODE_NUM; j++){
        if(results.value == ir_code[i][j]){
          move_servo(i, j);
        }
      }
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

void move_servo(int servo_id, int angle_id){
  servo[servo_id].attach(servo_pin[servo_id]);
  servo[servo_id].write(angle[servo_id][angle_id]);
  delay(1000);
  servo[servo_id].write(angle[servo_id][2]);
  delay(1000);
  servo[servo_id].detach();
}
