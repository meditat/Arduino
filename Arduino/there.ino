/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/
#include<SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX



const float Kp =1;   // Kp value that you have to change
const int Kd =60 ;   // Kd value that you have to change
const int setPoint = 35;    // Middle point of sensor array
const int baseSpeed = 100;    // Base speed for your motors
const int maxSpeed = 200;   // Maximum speed for your motors
const byte dir1 = 13;   // Connect DIR1 of motor driver to pin 13
const byte dir2 = 12;   // Connect DIR2 of motor driver to pin 12
const byte pwm1 = 6;   // Connect PWM1 of motor driver to pin 11
const byte pwm2 = 5;   // Connect PWM2 of motor driver to pin 10
// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
//const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
float outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
  digitalWrite(pwm1,LOW);
  digitalWrite(pwm2,LOW);
Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
mySerial.begin(9600);

}
int k=0;
int lastError = 0;
int rightMotorSpeed;
int leftMotorSpeed;
int junction = 0;


 void func(int pm1, int pm2){
    sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = (0.0791*sensorValue)-0.0586;
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);
  int positionVal=outputValue;
  // print the results to the Serial Monitor:
   
  /*Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\toutput = ");
  Serial.print(outputValue);
  Serial.print("\tright motor = ");
  Serial.print(rightMotorSpeed);
  Serial.print("\tleft motor = ");
  Serial.println(leftMotorSpeed);*/
   if(positionVal == 255 ||positionVal ==0 ) {
    analogWrite(pwm1,0);
    analogWrite(pwm2,0);
    analogWrite(9,0);
    
  }

  // Else if line detected, calculate the motor speed and apply
  else {
    int error = positionVal - setPoint;   // Calculate the deviation from position to the set point
     Serial.print("\t error = ");
    Serial.println(error);
    int motorSpeed = (Kp * error + Kd * (error - lastError))*5;   // Applying formula of PID
    lastError = error;    // Store current error as previous error for next iteration use
Serial.print("Speed = ");
  Serial.print(motorSpeed);
    // Adjust the motor speed based on calculated value
    // You might need to interchange the + and - sign if your robot move in opposite direction
   // rightMotorSpeed = baseSpeed - motorSpeed;
    //leftMotorSpeed = baseSpeed + motorSpeed;

    // If the speed of motor exceed max speed, set the speed to max speed
    //if(rightMotorSpeed > maxSpeed) rightMotorSpeed = maxSpeed;
    //if(leftMotorSpeed > maxSpeed) leftMotorSpeed = maxSpeed;

    // If the speed of motor is negative, set it to 0
    //if(rightMotorSpeed < 0) rightMotorSpeed = 0;
    //if(leftMotorSpeed < 0) leftMotorSpeed = 0;
    if(motorSpeed<200||motorSpeed>(-200))
    {
    if(motorSpeed<0)
    { digitalWrite(8,HIGH);
    Serial.print("dir1 = ");
      k=motorSpeed*(-1);
      analogWrite(9,k-30);
      }
      else if(motorSpeed>0)
    { digitalWrite(8,LOW);
      motorSpeed=motorSpeed*(-1);
      Serial.print("dir2 = ");
      analogWrite(9,motorSpeed-30);
            analogWrite(9,30);

      }
      else if(motorSpeed==0)
    { digitalWrite(8,LOW);
      motorSpeed=motorSpeed*(-1);
      analogWrite(9,0);
      }
    }
 
    // Writing the motor speed value as output to hardware motor
    analogWrite(pwm1,pm1);
    analogWrite(pwm2,pm2);
     digitalWrite(12,HIGH); 
  }
    }


int i,j;
int distance(){
  if (mySerial.available()) {
  j=0;
  i=0;
  if(mySerial.available()){
    do{
      j = mySerial.read()-'0';
      if(j==49)break;
      i = i*10 + j;
      Serial.println(j);
      }while(j!= 49);
      Serial.println(i);
    }
  }
  return i;
 }
int count = 0;

void loop() {
  // read the analog in value:
int value = analogRead(A1)/1000;
int pwm = 100;
int dist = distance();
if(count == 0){
if(value<1){
if(dist < 3000*0.5){
  func(100,100);}
        else{
          if(pwm <20){
            pwm = 30;
            }
          pwm = pwm/2;
          func(pwm,pwm);
          }
          }else
          {
            count++;
            func(0,0);
            analogWrite(9,0);
            }
       }
       }
          


  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
