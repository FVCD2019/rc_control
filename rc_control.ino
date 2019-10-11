#include <stdio.h>
#include <math.h>
#include <Servo.h>
/*
 #Steps:
 1.Connect the M1_PWM & M2_PWM to UNO digital 5 & 6
 2.Connect the M1_EN & M2_EN to UNO digital 4 & 7
 3.Connect +5V & GND to UNO 5V & GND
 
 # Function for current sense and diagnosis,if you want to use
 please connect the IS pins to Arduino
 Connect LA_IS & RA_IS to UNO digital 2
 Connect LB_IS & RB_IS to UNO digital 3
 */
//#define DEBUG
#define DEF_SPEED 100 
#define DEF_STEER 92 
#define throttle2_speed 6     //M2 Speed Control
#define throttle2_di 7     //M2 Direction Control
#define steer_pin 9

Servo servo;
int steer_val = DEF_STEER;
int speed_val = DEF_SPEED;

void stop(void)                    //Stop
{ 
  digitalWrite(throttle2_speed,0);   
  digitalWrite(throttle2_di,LOW);    
}   

void move(int speed, int steer)
{
 if(speed < 0){
  speed = speed*(-1);
  analogWrite (throttle2_speed,speed);    
  digitalWrite(throttle2_di,LOW);
 }
 else{
  analogWrite (throttle2_speed,speed);    0,
  digitalWrite(throttle2_di,HIGH);
 }
 
 if(steer < 20)
  steer = 20;
 else if(steer > 165)
  steer = 165;
 
 servo.write(steer);
 
}

/*
void current_sense()                  // current sense and diagnosis
{
  int val1=digitalRead(2);
  int val2=digitalRead(3);
  if(val1==HIGH || val2==HIGH){
    counter++;
    if(counter==3){
      counter=0;
      Serial.println("Warning");
    }  
  } 
}
*/

void setup(void) 
{ 
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT); 
  Serial.begin(19200);      //Set Baud Rate
  //Serial.println("Run keyboard control");
  analogWrite (throttle2_speed,0); 
  digitalWrite(throttle2_speed,HIGH);
  servo.attach(steer_pin);
  servo.write(steer_val);
  //pinMode(2,INPUT);
  //pinMode(3,INPUT);
} 

void loop(void) 
{
  if(Serial.available()){
   //ex : 200,150,
    speed_val = Serial.parseInt();
    steer_val = Serial.parseInt();
    int buf = Serial.read();
    move(speed_val, steer_val);
    Serial.println(speed_val);
    Serial.println(steer_val);
  }
}
