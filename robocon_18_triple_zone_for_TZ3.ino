
//SoftwareSerial mySerial(14, 15); // RX, TX
const float Kp =2;   // Kp value that you have to change
const int Kd =30 ;   // Kd value that you have to change
const int setPoint = 35;    // Middle point of sensor array
const byte right_motor = 13;   // Connect front_dir1 of motor driver to pin 13
const byte right_PWM = 12;   // Connect PWM of motor driver to pin 12
const byte left_motor = 11;   // Connect front_dir2 of motor driver to pin 11
const byte left_PWM = 10;   // Connect PWM of motor driver to pin 10
int front_dir=9;
int front_PWM=8;

int i=0,j=0,m=0,k,n=0;
int sensor_reading = 0;                                // value read from the pot
float sensor_float = 0;
int sensor_output = 0;        // value output to the PWM (analog out)
int sensor_jxn=0,rept_jxn=0;
int positionVal=0;
int error=0,error1=0;
int motorSpeed=0;  
int lastError = 0;
int count=0,distance_comp=2000,distance=0;
int PWM=70;
int frwd_arr[6];
int back_arr[6];
int TZ1=0,TZ2=0;
void setup() {
   pinMode(22,INPUT);  // INPUT at 22 is go for pick the ball
   pinMode(24,INPUT);  // INPUT at 24 is go in zone 1
   pinMode(26,INPUT);  // INPUT at 26 is go in zone 2
   pinMode(28,INPUT);  // INPUT at 28 is go in zone 3
  pinMode(23,OUTPUT);  // pick      PIN 23 GIVING SIGNAL THAT the robot is in picking zone
  pinMode(25,OUTPUT);  // throw    PIN 25 GIVING SIGNAL THAT the robot is in throwing zone
  for(int PIN=8;PIN<=13;PIN++)
   {
    pinMode(PIN,OUTPUT);
   }
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    for(int a=0;a<6;a++)
   {
     frwd_arr[a]=0;
   }
   for(int a=0;a<6;a++)
   {
     back_arr[a]=0;
   }
  Serial.begin(9600);
 // while (!Serial) { ; }

//mySerial.begin(9600);
   delay(3000);
      while(analogRead(A0)/1000!=1)
       { 
        line_follow();
       }
       right_move1(); 
        while(1)
    {
        line_follow();
     if(analogRead(A0)/1000)
     {  
        left_move1(); 
        stop_all();
        delay(100);
        while(1)
     {
         back_follow();
         if(analogRead(A0)/1000)
         {  
          digitalWrite(23,HIGH); // GENRATING SIGNAL THAT IT IS READY FOR HOLDING THE BALL
              
          while(1)        // for pickup signal compeleted and going for throw
          {  
             stop_all();
             if(digitalRead(24)==1)
             {
               digitalWrite(23,LOW);
               TZ1=1; TZ2=0;
               throwing_zone_1();
             }
            else if(digitalRead(26)==1)
             {
               digitalWrite(23,LOW);
               TZ1=0; TZ2=1;
              throwing_zone_2();
             }
            
             else if(digitalRead(28)==1)
             {
               digitalWrite(23,LOW);
                TZ1=0; TZ2=0; 
               throwing_zone_3();
             }     
           } break;              
         }
       } break;
      }
    } 
}

void loop() {
}

void throwing_zone_1()
{   line_follow();
   gng_for_throw();        
}
void throwing_zone_2()
{   
   gng_zone_2();        
}
void throwing_zone_3()
{   
    gng_zone_3();        
}


void gng_for_ball_3()
{
  while(1)
{
   back_follow();
    rept_jxn = analogRead(A0)/1000;
      if(rept_jxn==1)
       { 
         rept_jxn=0;
        back_arr[n]=1; n++;  
        if(back_arr[0]==1 && back_arr[1]==0 && back_arr[2]==0 && back_arr[3]==0 && back_arr[4]==0 && back_arr[5]==0 )
        {  
          while(analogRead(A0)/1000)
          back_follow();
        }
        else if(back_arr[0]==1 && back_arr[1]==1 && back_arr[2]==0 && back_arr[3]==0 && back_arr[4]==0 && back_arr[5]==0 )
        {  
          while(analogRead(A0)/1000)
          back_follow();
        }
        else if(back_arr[0]==1 && back_arr[1]==1 && back_arr[2]==1 && back_arr[3]==0 && back_arr[4]==0 && back_arr[5]==0 )
        {  
          while(analogRead(A0)/1000)
          back_follow();
        }
       else if(back_arr[0]==1 && back_arr[1]==1 && back_arr[2]==1 && back_arr[3]==1 && back_arr[4]==0 && back_arr[5]==0 )
        {  
          while(analogRead(A0)/1000)
          back_follow();
        }
       else if(back_arr[0]==1 && back_arr[1]==1 && back_arr[2]==1 && back_arr[3]==1 && back_arr[4]==1 && back_arr[5]==0 )
        {  
          while(analogRead(A0)/1000)
          back_follow();
        }
         else if(back_arr[0]==1 && back_arr[1]==1 && back_arr[2]==1 && back_arr[3]==1 && back_arr[4]==1 && back_arr[5]==1 )
        { 
          for(int a=0;a<6;a++)
         {
           back_arr[a]=0;
         }n=0;
         digitalWrite(23,HIGH);
           while(1)        // wating for signal   and      picking the ballllll
          {
             stop_all();
             if(digitalRead(24)==1)
             {  digitalWrite(23,LOW);
                gng_zone_1();              
             }
             else if(digitalRead(26)==1)
             {digitalWrite(23,LOW);
               gng_for_throw();
              }
              else if(digitalRead(28)==1)
              {
                digitalWrite(23,LOW); break;
              }    
             }break;
           }     
      }
}
gng_for_throw_3();
}




void gng_for_throw_3()
{
  while(1)
  {
    line_follow();
   sensor_jxn = analogRead(A0)/1000;
  if(sensor_jxn==1)
    {
      frwd_arr[m]=1; m++; 
      
      if(frwd_arr[0]==1 && frwd_arr[1]==0 && frwd_arr[2]==0 && frwd_arr[3]==0 && frwd_arr[4]==0  && frwd_arr[5]==0 )   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==0 && frwd_arr[3]==0 && frwd_arr[4]==0  && frwd_arr[5]==0 )   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 && frwd_arr[3]==0 && frwd_arr[4]==0  && frwd_arr[5]==0 )   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 && frwd_arr[3]==1 && frwd_arr[4]==0  && frwd_arr[5]==0 )   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 && frwd_arr[3]==1 && frwd_arr[4]==1  && frwd_arr[5]==0 )   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 && frwd_arr[3]==1 && frwd_arr[4]==1  && frwd_arr[5]==1)
      {
        for(int a=0;a<6;a++)
      {
         frwd_arr[a]=0;
      }m=0;
        digitalWrite(25,HIGH);
        while(digitalRead(22)==0)    // wating for signal    &&&&&&&&&& throwing continously
          {
          stop_all(); 
          } 
         digitalWrite(25,LOW);  
          break;
     }             
  }
}
gng_for_ball_3();
}



void  gng_zone_3()
{
  TZ1=0; TZ2=0;
  while(analogRead(A0)/1000!=1)
  {line_follow();}
  right_move1();
  while(1)
  {
  line_follow();
   sensor_jxn = analogRead(A0)/1000;
  if(sensor_jxn==1)
    {
      frwd_arr[m]=1; m++;    
      if(frwd_arr[0]==1 && frwd_arr[1]==0 && frwd_arr[2]==0  && frwd_arr[3]==0 && frwd_arr[4]==0  && frwd_arr[5]==0 )  
      {
        while(analogRead(A0)/1000)
        left_move1();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==0 && frwd_arr[3]==0 && frwd_arr[4]==0  && frwd_arr[5]==0 )   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 && frwd_arr[3]==0 && frwd_arr[4]==0  && frwd_arr[5]==0)   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 && frwd_arr[3]==1 && frwd_arr[4]==0  && frwd_arr[5]==0 )   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 && frwd_arr[3]==1 && frwd_arr[4]==1  && frwd_arr[5]==0 )   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 && frwd_arr[3]==1 && frwd_arr[4]==1  && frwd_arr[5]==1 )   
      {
        for(int a=0;a<6;a++)
      {
         frwd_arr[a]=0;
      }  m=0;
      digitalWrite(25,HIGH);
         while(digitalRead(22)==0)    // wating for signal  &&&&&&&&&&   throwing continously
         {
          stop_all();
         }  
          digitalWrite(25,LOW);  
      break;
      }
 } }  
 gng_for_ball_3(); 
}

void gng_zone_2()
{
  TZ1=0; TZ2=1;
  while(analogRead(A0)/1000!=1)
  {line_follow();}
  delay(100);
  right_move1();
  while(1)
  {
  line_follow();
   sensor_jxn = analogRead(A0)/1000;
  if(sensor_jxn==1)
    {
      frwd_arr[m]=1; m++;    
      if(frwd_arr[0]==1 && frwd_arr[1]==0 && frwd_arr[2]==0  )  
      {
        while(analogRead(A0)/1000)
        left_move1();
      }
      if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==0  )   
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 )   
      {
        for(int a=0;a<6;a++)
      {
         frwd_arr[a]=0;
      }  m=0;
      digitalWrite(25,HIGH);
         while(digitalRead(22)==0)    // wating for signal  &&&&&&&&&&   throwing continously
         {
          stop_all();
         }  
          digitalWrite(25,LOW);   
      break;
      }
 } }  
 gng_for_ball(); 
}




void gng_zone_1()
{
  TZ1=1; TZ2=0; 
  while(analogRead(A0)/1000!=1)
  {line_follow();}
  delay(100);
  left_move1();
  while(1)
  {
  line_follow();
   sensor_jxn = analogRead(A0)/1000;
  if(sensor_jxn==1)
    {
      frwd_arr[m]=1; m++;    
      if(frwd_arr[0]==1 && frwd_arr[1]==0 && frwd_arr[2]==0  )  
      {
        while(analogRead(A0)/1000)
        right_move1();
      }
      if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==0  )  
      {
        while(analogRead(A0)/1000)
        line_follow();
      }
      if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1 )  
      {
        for(int a=0;a<6;a++)
      {
         frwd_arr[a]=0;
      }  m=0;
      digitalWrite(25,HIGH);
         while(digitalRead(22)==0)    // wating for signal  &&&&&&&&&&   throwing continously
         {
          stop_all();
         }  
          digitalWrite(25,LOW);  
      
      break;
      }
 } }  
 gng_for_ball(); 
}




void gng_for_throw()
{
  while(1)
  {
    line_follow();
   sensor_jxn = analogRead(A0)/1000;
  if(sensor_jxn==1)
    {
      frwd_arr[m]=1; m++; 
      
      if(frwd_arr[0]==1 && frwd_arr[1]==0 && frwd_arr[2]==0  )  
      {
         while(analogRead(A0)/1000)
            line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==0 )  
      {
         while(analogRead(A0)/1000)
            line_follow();
      }
      else if(frwd_arr[0]==1 && frwd_arr[1]==1 && frwd_arr[2]==1)
      {
        for(int a=0;a<6;a++)
      {
         frwd_arr[a]=0;
      }   m=0;
            digitalWrite(25,HIGH);
            
        while(digitalRead(22)==0)    // wating for signal    &&&&&&&&&& throwing continously
          {
          stop_all();           
          digitalWrite(25,LOW);
          }     
          break;
     }             
  }
}
gng_for_ball();
}


void  gng_for_ball()
{
  while(1)
{
   back_follow();
    rept_jxn = analogRead(A0)/1000;
      if(rept_jxn==1)
       { 
         rept_jxn=0;
        back_arr[n]=1; n++;  
        if(back_arr[0]==1 && back_arr[1]==0 && back_arr[2]==0)
        {  
          while(analogRead(A0)/1000)
          back_follow();
        }
        else if(back_arr[0]==1 && back_arr[1]==1 && back_arr[2]==0)
        { 
          while(analogRead(A0)/1000)
          back_follow();
        }
         else if(back_arr[0]==1 && back_arr[1]==1 && back_arr[2]==1)
        { 
          for(int a=0;a<6;a++)
          {
           back_arr[a]=0;
          }n=0;
          digitalWrite(23,HIGH);
          
           while(1)        // wating for signal   and      picking the ballllll
          {
             stop_all();
             if(digitalRead(24)==1)
             {
               if(TZ1==1 && TZ2==0 )
              {
               digitalWrite(23,LOW);
                break;
              }
              else if(TZ1==0 && TZ2==1 )
              {
                digitalWrite(23,LOW);
                gng_zone_1();
              }              
             }
             else if(digitalRead(26)==1)
             {
               digitalWrite(23,LOW);
              if(TZ1==1 && TZ2==0 )
              {
                gng_zone_2();
              }
              else if(TZ1==0 && TZ2==1 )
              {
                break;
              }    
             }
              else if(digitalRead(28)==1)
             {
               digitalWrite(23,LOW);
              if(TZ1==1 && TZ2==0 )
              {
                gng_zone_3();
              }
              else if(TZ1==0 && TZ2==1 )
              {
                gng_for_throw_3();
              }   
             }
           }
         break;
      }
    }
}
gng_for_throw();
}

 void stop_all()
 {
      analogWrite(right_PWM,0);
      analogWrite(left_PWM,0);
      analogWrite(front_PWM,0);
 }
 void forword_move()
 {
   analogWrite(right_PWM,PWM);
   analogWrite(left_PWM,PWM);
   digitalWrite(left_motor,HIGH); 
   digitalWrite(right_motor,HIGH); 
 }
  void backword_move()
 {
   analogWrite(right_PWM,PWM);
   analogWrite(left_PWM,PWM);
   digitalWrite(left_motor,LOW); 
   digitalWrite(right_motor,LOW);  
 }
 void right_move()
 {
   analogWrite(right_PWM,40);
   analogWrite(left_PWM,40);
   
   analogWrite(front_PWM,100);
   digitalWrite(left_motor,HIGH); 
   digitalWrite(right_motor,LOW); 
   digitalWrite(front_dir,LOW);
 }
 void right_move1()
 {
   while(1)
   {
    sensor_reading = analogRead(A1);
    sensor_float = (0.0791*sensor_reading)-0.0586;
    sensor_output=sensor_float;
    while((sensor_output<75)&& count==0 )
    {
       right_move();
       sensor_reading = analogRead(A1);
       sensor_float = (0.0791*sensor_reading)-0.0586;
       sensor_output=sensor_float;
    }
    if(sensor_output>76)
    {
      count=1;
    }
    right_move();
    if(sensor_output>=35 && sensor_output<=45)
     {
      break;
     }
   }
   count=0;
 }
 void left_move()
 {
   analogWrite(right_PWM,40);
   analogWrite(left_PWM,40);
   analogWrite(front_PWM,120);
   digitalWrite(left_motor,LOW); 
   digitalWrite(right_motor,HIGH); 
   digitalWrite(front_dir,HIGH);
 }
 void left_move1()
 {
   while(1)
   {
    sensor_reading = analogRead(A1);
    sensor_float = (0.0791*sensor_reading)-0.0586;
    sensor_output=sensor_float;
    while((sensor_output<75) && count==0 )
    {
       left_move();
       sensor_reading = analogRead(A1);
       sensor_float = (0.0791*sensor_reading)-0.0586;
       sensor_output=sensor_float;
    }
    if(sensor_output>76)
    {
      count=1;
    }
    left_move();
    if(sensor_output>45 && sensor_output<=55)
     {
       Serial.print("sensor output         "); Serial.println( sensor_output);
      stop_all();
      break;
     }
   }
   count=0;
 }

 void line_follow(){
            sensor_reading = analogRead(A1);      
            sensor_float = (0.0791*sensor_reading)-0.0586;  
            sensor_output = sensor_float;
            positionVal = sensor_output;                    
 if(positionVal >= 75 ) 
     {
        stop_all();
     }
  else {
    pid_control();     
    if(motorSpeed<240 && motorSpeed>(-240))
    {
     if(motorSpeed<0)
    {
      digitalWrite(front_dir,HIGH);
      motorSpeed= motorSpeed*(-1);
      while(1)
      {
       sensor_reading = analogRead(A1);      
       sensor_float = (0.0791*sensor_reading)-0.0586;  
       sensor_output = sensor_float;
       positionVal = sensor_output;  
        if(positionVal<35)       //right side
           analogWrite(front_PWM,60);
        else
        break;
      }
      analogWrite(front_PWM,0);
     }
      else if(motorSpeed>0)
      {
      digitalWrite(front_dir,LOW);
      analogWrite(front_PWM,60);
      while(1)
      {
        sensor_reading = analogRead(A1);      
         sensor_float = (0.0791*sensor_reading)-0.0586;  
         sensor_output = sensor_float;
         positionVal = sensor_output;  
        if(positionVal>35)
        analogWrite(front_PWM,60);
        else
        break;
      }
      analogWrite(front_PWM,0);
     }
     }
      else
    {
      digitalWrite(front_dir,LOW);
      analogWrite(front_PWM,0);
      }
    } 
    forword_move();
  /* distance =distance_encoder();
    Serial.print("distance             ");  Serial.println(distance);
    if(distance>=3200)//&&distance<=2900
    { 
      Serial.print("condition true");
      if(distance>=distance_comp)
       {
        if(PWM>65)
        {
          PWM=PWM-15;
          distance_comp=distance_comp+100;
        }
        else 
        PWM=65;
       }
    }*/
  }
 
void back_follow(){
            sensor_reading = analogRead(A1);      
            sensor_float = (0.0791*sensor_reading)-0.0586;  
            sensor_output = sensor_float;
            positionVal = sensor_output;  
   digitalWrite(left_motor,LOW); 
   digitalWrite(right_motor,LOW);  
       if(positionVal==35)
     {  
       backword_move();
     }
                              
     if(positionVal<35)
    {    
      analogWrite(right_PWM,(PWM)+15);
      analogWrite(left_PWM,(PWM)-15);
    }
      else if(positionVal>35)
      {
        analogWrite(right_PWM,(PWM)-15);
        analogWrite(left_PWM,(PWM)+15);
      }
  }

   void pid_control()
 {
           for(int c=1;c<=20;c++)
           {
            sensor_reading = analogRead(A1);      
            sensor_float = (0.0791*sensor_reading)-0.0586;  
            sensor_output = sensor_float;
            positionVal = sensor_output; 
            error = positionVal - setPoint;
            error1=error+error1;
            }
            error1=error1/20;
            motorSpeed = (Kp * error1 + Kd * (error1 - lastError))*3;
            lastError = error1;
            
 }
/*int distance_encoder(){
  if(mySerial.available()){
    i=0;
    j=0;
    do{
      j = mySerial.read()-'0';
      if(j==-46)break;
      i = i*10 + j;
       Serial.print(j);
      }while(j!= -46);
     Serial.println("");

  }
  return i;
 }*/
