#include <Servo.h>
#include <NewPing.h>
Servo int_lid_Servo;
Servo lidServo;
Servo distributor;
#define trig 9
#define echo 10
#define max_dist 100

NewPing sonar(trig, echo, max_dist);

int wet_bin_angle = 0;
int dry_bin_angle = 90;
int metal_bin_angle = 180;

const int distributor_servo_pin  = 11;
const int int_lid_servo_pin = 6;
const int ext_lidServo_pin  = 3;

int wet_sensor_pin = 2; /// connect wet sensor pin
int metal_sensor = 7;
int approch_dist = 10;  /// set approching distance
int open_angle = 90;   // when metal detect
int close_angle = 0; // when no metal detecdt
int close_lid = 0; //when away from system close
int open_lid = 180; // when approch lid open

void setup() {
  // put your setup code here, to run once
  int_lid_Servo.attach(int_lid_servo_pin);
  lidServo.attach(ext_lidServo_pin);
  distributor.attach(distributor_servo_pin);
  pinMode(metal_sensor, INPUT_PULLUP);


}

void loop() {
  // put your main code here, to run repeatedly:

  bool is_wet = digitalRead(wet_sensor_pin);

  int dist = sonar.ping_cm();
  if (dist < approch_dist) {
    int_lid_Servo.write(close_angle);
    delay(1000);
    lidServo.write(open_lid);
  }
  else{
    lidServo.write(close_lid);

  bool is_metal = digitalRead(metal_sensor);
  if ( is_metal == LOW ) {
    int_lid_Servo.write(close_angle);
    delay(1000);
    distributor.write(metal_bin_angle);
    delay(1000);
    int_lid_Servo.write(open_angle);
    delay(1000);
  }
  else {


    if ( is_wet) {
    int_lid_Servo.write(close_angle);
    delay(1000);
    distributor.write(wet_bin_angle);
    delay(1000);
    int_lid_Servo.write(open_angle);
    delay(1000);
    }
    else if{
    int_lid_Servo.write(close_angle);
    delay(1000);
    distributor.write(dry_bin_angle);
    delay(1000);
    int_lid_Servo.write(open_angle);
    delay(1000);
    }
  }

  }
  
}