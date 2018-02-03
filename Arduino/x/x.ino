#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
const byte pwm1 = 6;   // Connect PWM1 of motor driver to pin 11
const byte pwm2 = 5; 
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
mySerial.begin(9600);
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

void loop() { 
  Serial.println(distance());
}
