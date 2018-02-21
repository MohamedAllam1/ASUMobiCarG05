//Initialization of Variables
#include <Servo.h>
Servo Control_Servo;
int right_motor_in1=0;
int right_motor_in2=1;
int right_motor_PWM=2;
int left_motor_in1=3;
int left_motor_in2=4;
int left_motor_PWM=5;
int trig_pin_front =6;
int echo_pin_front =7;
int trig_pin_rear =8;
int echo_pin_rear =9;
int Servo_Pos=0;
int Speed =0;
char Data;
String Signal;

void setup() 
{
  pinMode (right_motor_in1,OUTPUT);
  pinMode (right_motor_in2,OUTPUT);
  pinMode (right_motor_PWM,OUTPUT);
  pinMode (left_motor_in1,OUTPUT);
  pinMode (left_motor_in2,OUTPUT);
  pinMode (left_motor_PWM,OUTPUT);
  pinMode (trig_pin_front,OUTPUT);
  pinMode (echo_pin_front,INPUT);
  pinMode (trig_pin_rear,OUTPUT);
  pinMode (echo_pin_rear,INPUT);
  Control_Servo.attach (8);
  Serial.begin (9600);
}

void loop() 
{
   //Signal Input from Bluetooth
  if (Serial.available())
  {
  delay(10);
  Data = Serial.read();
  Signal += Data;
  }
  
  //Print the recieved char
  if(Signal.length() > 0 )    
  {
    Serial.println(Signal);
  }

  //Initialization of Ultrasonics
  digitalWrite (trig_pin_front,LOW);  
  digitalWrite (trig_pin_rear,LOW);
  delayMicroseconds(10);
  digitalWrite (trig_pin_front,HIGH);
  digitalWrite (trig_pin_rear,HIGH);
  delayMicroseconds(2);
  int duration_front=pulseIn (echo_pin_front,HIGH);
  int duration_rear=pulseIn (echo_pin_rear,HIGH);
  float x_front = duration_front*0.034/2;
  float x_rear = duration_rear*0.034/2;
  float distance_front = constrain (x_front, 0 ,400);
  float distance_rear = constrain (x_rear, 0 ,400);
  
  // Easy Driving Mode
  if (Signal == "r")
  {
    Control_Servo.write(30);
  }
  if (Signal == "c")
  {
    Control_Servo.write(0);
  }
   if (Signal == "l")
  {
    Control_Servo.write(-30);
  }
  
  //Determination of Speed;
  if (Signal == "1")
  {
   Speed=50; 
    }
    if (Signal == "2")
  {
   Speed=255/2; 
    } 
    if (Signal == "3")
  {
   Speed=255; 
    } 
    if (Signal == "f")
  {
    analogWrite (right_motor_PWM , Speed);
    digitalWrite (right_motor_in1 , HIGH);
    digitalWrite (right_motor_in2 , LOW);
    analogWrite (left_motor_PWM , Speed);
    digitalWrite (left_motor_in1 , HIGH);
    digitalWrite (left_motor_in2 , LOW);
  }
    if (Signal == "b")
  {
    analogWrite (right_motor_PWM , Speed);
    digitalWrite (right_motor_in1 ,LOW);
    digitalWrite (right_motor_in2 , HIGH);
    analogWrite (left_motor_PWM , Speed);
    digitalWrite (left_motor_in1 , LOW);
    digitalWrite (left_motor_in2 , HIGH);
  }
  
  //Autonomus Driving & Obstacles Avoidance
  
  Signal="";
}
