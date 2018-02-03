/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses`
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

const float Kp =1;   // Kp value that you have to change
const int Kd =60 ;   // Kd value that you have to change
const int setPoint = 35;    // Middle point of sensor array
const int baseSpeed = 100;    // Base speed for your motors
const int maxSpeed = 200;   // Maximum speed for your motors
const byte dir1 = 13;   // Connect DIR1 of motor driver to pin 13
const byte dir2 = 12;   // Connect DIR2 of motor driver to pin 12
const byte pwm1 = 11;   // Connect PWM1 of motor driver to pin 11
const byte pwm2 = 10;   // Connect PWM2 of motor driver to pin 10
// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
//const int analogInPin = A1;  // Analog junction pin
//const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0,a=0,b=0;        // value read from the pot
float outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  for(byte i=10;i<=13;i++) {
    pinMode(i,OUTPUT);
  digitalWrite(pwm1,LOW);
  digitalWrite(pwm2,LOW);
  Serial.begin(9600);
}
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(A1,INPUT);
}
int k=0;
int lastError = 0;
int rightMotorSpeed;
int leftMotorSpeed;
void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = (0.0791*sensorValue)-0.0586;
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);
  int positionVal=outputValue;
  // print the results to the Serial Monitor:
 //a=analogRead((A1)/1000);
  /*Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\toutput = ");
  Serial.print(outputValue);
  Serial.print("\tright motor = ");
  Serial.print(rightMotorSpeed);
  Serial.print("\tleft motor = ");
  Serial.println(leftMotorSpeed);*/
 
   if(positionVal == 255) {
    analogWrite(pwm1,0);
    analogWrite(pwm2,0);
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
      //motorSpeed=motorSpeed*(-1);
      Serial.print("dir2 = ");
      analogWrite(9,motorSpeed-30);
      }
      else if(motorSpeed==0)
    { digitalWrite(8,LOW);
      //motorSpeed=motorSpeed*(-1);
      analogWrite(9,0);
      }
      
      {
        
      }
    }
   /* else
    {
      analogWrite(9,0);
       analogWrite(11,0);
        analogWrite(10,0);

    }*/
    // Writing the motor speed value as output to hardware motor
    analogWrite(pwm1,40);
    analogWrite(pwm2,40);
    digitalWrite(12,HIGH);
    
  }
  }
 
  
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:

