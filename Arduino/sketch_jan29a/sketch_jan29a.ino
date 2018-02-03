#include<SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX


const float Kp =1;   // Kp value that you have to change
const int Kd =60 ;   // Kd value that you have to change
const int setPoint = 35;    // Middle point of sensor array
const int baseSpeed = 100;    // Base speed for your motors
const int maxSpeed = 200;   // Maximum speed for your motors
const byte dir1 = 13;   // Connect DIR1 of motor driver to pin 13
const byte dir2 = 12;   // Connect DIR2 of motor driver to pin 12
const byte pinR = 6;   // Connect PWM1 of motor driver to pin 11
const byte pinL = 5;   // Connect PWM2 of motor driver to pin 10
// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
//const int analogInPin = A1;  // Analog junction pin
//const int analogOutPin = 9; // Analog output pin that the LED is attached to
int sensorValue = 0,a=0,b=0;        // value read from the pot
float outputValue = 0;  
int k=0;
int lastError = 0;
int rightMotorSpeed;
int leftMotorSpeed;

int node  = 0;
int junction =  analogRead(A1/1000);
int timeMax = 0.6;
int timeMin = 0.4;
int i,j;
     
void setup() {
  // initialize serial communications at 9600 bps:
      for(byte i=10;i<=13;i++) {
        pinMode(i,OUTPUT);
        digitalWrite(pinR,LOW);
        digitalWrite(pinL,LOW);
        Serial.begin(9600);
    }
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(A1,INPUT);
}

void nodeStop(){
  analogWrite(6,0);
  analogWrite(9,0);
  analogWrite(5,0);
  }

void setPwm(int pwmL, int pwmR){
  analogWrite(pinR,pwmR);
  analogWrite(pinL,pwmL);
  digitalWrite(12,HIGH);
  sensorValue = analogRead(analogInPin);
  outputValue = (0.0791*sensorValue)-0.0586;
  int positionVal=outputValue;
     if(positionVal == 255) {
      analogWrite(pinR,0);
      analogWrite(pinL,0);
     }else {
        int error = positionVal - setPoint;  
        Serial.print("\t error = ");
        Serial.println(error);
        int motorSpeed = (Kp * error + Kd * (error - lastError))*5;  
        lastError = error; 
        Serial.print("Speed = ");
        Serial.print(motorSpeed);
    if(motorSpeed<200||motorSpeed>(-200))
    {if(motorSpeed<0){
        digitalWrite(8,HIGH);
        Serial.print("dir1 = ");
        k=motorSpeed*(-1);
        analogWrite(9,k-30);
      }else if(motorSpeed>0){
          digitalWrite(8,LOW);
          Serial.print("dir2 = ");
          analogWrite(9,motorSpeed-30);
      }else if(motorSpeed==0){
          digitalWrite(8,LOW);
          analogWrite(9,0);  
        }
      }else{
        analogWrite(9,0);
        analogWrite(11,0);
        analogWrite(10,0);
        }
     }
  }
  
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
void loop() {
  if(node  == 0){
  int pwm = 150;
    if(distance() < 4470*timeMax ){
      setPwm(pwm,pwm);
      }else if(junction){
      nodeStop();
      node++;
      }else if(distance()> 4470*timeMax  && node == 0){
         pwm = pwm/10;
         setPwm(pwm , pwm);
        }
  }
  if(node  == 1){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 2){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node == 3){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 4){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 5){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 6){
    if(junction){
      nodeStop();
      node++;
      }
  }
   if(node  == 7){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 8){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 9){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 10){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 11){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 12){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 13){
    if(junction){
      nodeStop();
      node++;
      }
  }
   if(node  == 14){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 15){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 16){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 17){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node  == 18){
    if(junction){
      nodeStop();
      node++;
      }
  }
  if(node == 19){
    if(junction){
      nodeStop();
      node++;
      }
  }
 
}
