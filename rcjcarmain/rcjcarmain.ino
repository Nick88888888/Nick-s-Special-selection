int speed1 =200;//速度
#define speedfootR 2
#define speedfootL 3 //速度的腳位
#define motorL1 14
#define motorL2 15
#define motorR1 16
#define motorR2 17//定義馬達角位
#define infrared1 54
#define infrared2 55
#define infrared3 56
#define infrared4 57
#define infrared5 58//紅外線感應器的腳位定義
void straight()
{

   digitalWrite(motorL1,1);
   digitalWrite(motorL2,0);
   digitalWrite(motorR1,1);
   digitalWrite(motorR2,0);
   analogWrite(speedfootR,speed1);
   analogWrite(speedfootL,speed1);
}
void back()
{
   digitalWrite(motorL1,0);
   digitalWrite(motorL2,1);
   digitalWrite(motorR1,0);
   digitalWrite(motorR2,1);
   analogWrite(speedfootR,speed1);
   analogWrite(speedfootL,speed1);
}
void left()
{
   digitalWrite(motorL1,0);
   digitalWrite(motorL2,1);
   digitalWrite(motorR1,1);
   digitalWrite(motorR2,0);
   analogWrite(speedfootR,speed1);
   analogWrite(speedfootL,speed1);
}
void right()
{
   digitalWrite(motorL1,1);
   digitalWrite(motorL2,0);
   digitalWrite(motorR1,0);
   digitalWrite(motorR2,1);
   analogWrite(speedfootR,speed1);
   analogWrite(speedfootL,speed1);
}
void stop1()
{
  digitalWrite(motorL1,1);
  digitalWrite(motorL2,1);
  digitalWrite(motorR1,1);
  digitalWrite(motorR2,1);
  analogWrite(speedfootR,255);
  analogWrite(speedfootL,255);
}
//白==1  黑==0
void setup() 
{
  pinMode(speedfootR,OUTPUT);
   pinMode(speedfootL,OUTPUT);
   pinMode(motorL1,OUTPUT);
   pinMode(motorL2,OUTPUT);
   pinMode(motorR1,OUTPUT);
   pinMode(motorR2,OUTPUT);//馬達設定

   pinMode(infrared1,INPUT);
   pinMode(infrared2,INPUT);
   pinMode(infrared3,INPUT);
   pinMode(infrared4,INPUT);
   pinMode(infrared5,INPUT);//紅外線設定
  
}

void loop() 
{  
   if(digitalRead(infrared2)==0 && digitalRead(infrared4)==0)
   {
        if(digitalRead(infrared5)==1)
        {
            straight();
            while(digitalRead(infrared4)==0)
            {
            }
            right();
            while(digitalRead(infrared4)==1)
            {              
            }
            while(digitalRead(infrared4)==0)
            {              
            }
            left();
            delay(50);
        }
        else if(digitalRead(infrared5)==1)
        {
          straight();
            while(digitalRead(infrared2)==0)
            {
            }
            left();
            while(digitalRead(infrared2)==1)
            {              
            }
            while(digitalRead(infrared2)==0)
            {              
            }
            right();
            delay(50);
        }
   }
   else
   {
       if(digitalRead(infrared2)==0)//左邊感測器
       {
        straight();//直走
        delay(100);
        
        do
        {
        left();
        }while(digitalRead(infrared3)==1);//先做一次左轉如果右邊感測器看到白色繼續左轉直到看到黑色跳出去,do while =先做一次，然後如果裡面要判斷的值是對的就形成迴圈不對就會跳出去了
        right();//右轉修正
        delay(100);    
        
       }
       else if(digitalRead(infrared4)==0)//右邊感測器
       {
        straight();//直走
        delay(100);
        do
        {
          right();
          
        }while(digitalRead(infrared3)==1);//先做一次又轉如果左邊感測器看到白色繼續左轉直到看到黑色跳出去
        left();//左轉修正
        delay(100);
       }
       else
       {
        straight();
       }
   }
  
}
