int LFcolor,z=0,RFcolor,LBcolor,RBcolor,Lcount=0,Rcount=0,speed = 250 ;
long RTime,Fcm,LTime,Bcm;

void stop1()
{
  analogWrite(10,speed);
  analogWrite(11,speed);
  digitalWrite(2,0);
  digitalWrite(3,0);
  digitalWrite(4,0);
  digitalWrite(5,0);
}
void detect()
{
  digitalWrite(6,0);  
  delayMicroseconds(2);
  digitalWrite(6,1);
  delayMicroseconds(10);
  digitalWrite(6,0);
  

  RTime = pulseIn(7,1);
  Fcm = RTime/58;

  digitalWrite(8,0);
  delayMicroseconds(2);
  digitalWrite(8,1);
  delayMicroseconds(10);
  digitalWrite(8,0);
  LTime = pulseIn(9,1);
  Bcm = LTime/58;
  
}
void right()
{
  analogWrite(10,speed);
  analogWrite(11,speed);
  digitalWrite(2,0);
  digitalWrite(3,1);
  digitalWrite(4,1);
  digitalWrite(5,0);
}
void left()
{
  analogWrite(10,speed);
  analogWrite(11,speed);
  digitalWrite(2,1);
  digitalWrite(3,0);
  digitalWrite(4,0);
  digitalWrite(5,1);
  
}
void back()
{
  analogWrite(10,250);
  analogWrite(11,250);
  digitalWrite(2,0);
  digitalWrite(3,1);
  digitalWrite(4,0);
  digitalWrite(5,1);
}
void go()
{
  analogWrite(10,speed);
  analogWrite(11,speed);
  digitalWrite(2,1);
  digitalWrite(3,0);
  digitalWrite(4,1);
  digitalWrite(5,0);
}
void S1()//戰略
{
      RFcolor = digitalRead(17);
      LFcolor = digitalRead(14);
      RBcolor = digitalRead(16);
      LBcolor = digitalRead(15);
      if(RFcolor ==1 || LFcolor==1)
      {
            
            back();
            delay(1000);
            left();
            delay(1000);
          }
      else if(RBcolor ==1 || LBcolor==1)
      {
         
            go();
            delay(1000);
            right();
            delay(1000);
      }
      else
      {
         if(Fcm<=30)
           {  
           
              go();
           }
           else if(Bcm<=30)
           {
     
               back();
               
               
           }
           else
           {         
            left();
           }
      }
}

void S2()//隨機亂跑
{
 
  RFcolor = digitalRead(17);
      LFcolor = digitalRead(14);
     if(RFcolor ==1 ||   LFcolor ==1)
      {
            back();
            delay(1000);
            left();
            delay(1000);
          }
      else
      {
          int x = random(0,2);
          if(x==0)
          {
            int j = random(1000,3000);
            right();
            delay(j);
            int y = random(1000,3000);
            go();
            delay(y);
          }
          else
          {
            int j = random(1000,3000);
            left();
            delay(j);
            int y = random(1000,3000);
            go();
            delay(y);            
          }
      }
}
void S3()
{
      RFcolor = digitalRead(17);
      LFcolor = digitalRead(14);
      if(RFcolor ==1 || LFcolor==1)
      {
            
            back();
            delay(1000);
            left();
            delay(1000);
          }
      else
      {
           detect();
           if(Fcm<=30)
           {  
           
              go();
           }
           else if(Bcm<=10)
           {
     
               left();
               delay(2000);
               
               
           }
           else
           {         
            left();
           }
      }
}
void S4()
{
   go();   
}
void setup() {
 for(int i=2;i<=5;i++)//馬達
 pinMode(i,1);
 pinMode(10,1);//pwm
 pinMode(11,1);
 pinMode(8,1);//超音波
 pinMode(9,0);
 pinMode(6,1);//超音波
 pinMode(7,0);
 pinMode(14,0);//紅外線
 pinMode(15,0);
 pinMode(16,0);
 pinMode(17,0);

 pinMode(A4,INPUT_PULLUP);
 pinMode(A5,INPUT_PULLUP);
 Serial.begin(9600);
 
    RBcolor = digitalRead(16);
    LBcolor = digitalRead(15);
 while(RBcolor == 0 && LBcolor ==0) 
   {
    Serial.print(RBcolor);
    Serial.print(",");
    Serial.println(LBcolor);
    RBcolor = digitalRead(16);
    LBcolor = digitalRead(15);
    back();
   }
  go();
  delay(1000);
  stop1();
   
  
}

void loop() 
{
  detect();
  int x = digitalRead(A4)+digitalRead(A5)*2 + 1;//連通是0
  RFcolor = digitalRead(17);
  LFcolor = digitalRead(14);
  Serial.println(x);
  switch(x)
  {
    case 1:
     S1();
     break;
     case 2:
     S2();
     break;
     case 3:
     S3();
     break;
     case 4:
     S4();
     break;
     
  }
   
}
