int speed1=200;//速度
int RedL=0, BlueL=0, GreenL=0,
    RedR=0, BlueR=0, GreenR=0;//左右
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
#define s0R 4       
#define s1R 5
#define s2R 6
#define s3R 7
#define outR 8  //右模塊引腳接線
#define s0L 9       
#define s1L 10
#define s2L 11
#define s3L 12
#define outL 13  //左模塊引腳接線


void straight()
{

   digitalWrite(motorL1,1);
   digitalWrite(motorL2,0);
   digitalWrite(motorR1,1);
   digitalWrite(motorR2,0);
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
void GetColorsL()
{
  digitalWrite(s2L,LOW);//S2L/S3L 級別定義我們使用哪一組光電二極管 LOW/LOW 代表紅色 LOW/HIGH 代表藍色，HIGH/HIGH 代表綠色                                           
  digitalWrite(s3L,LOW);                                           
  RedL = pulseIn(outL, digitalRead(outL) == HIGH ? LOW : HIGH);//這裡我們等到“out”變低，我們開始測量持續時間並在“out”再次為高時停止 
  delay(20);      
  digitalWrite(s3L,HIGH);//這裡我們選擇其他顏色（光電二極管組）並使用相同的技術測量其他顏色值                                         
  BlueL = pulseIn(outL, digitalRead(outL) == HIGH ? LOW : HIGH);
  delay(20);  
  digitalWrite(s2L,HIGH);    
  GreenL = pulseIn(outL, digitalRead(outL) == HIGH ? LOW : HIGH);
  delay(20);
}
void GetColorsR()
{
  digitalWrite(s2R,LOW);//S2R/S3R 級別定義我們使用哪一組光電二極管 LOW/LOW 代表紅色 LOW/HIGH 代表藍色，HIGH/HIGH 代表綠色                                           
  digitalWrite(s3R,LOW);                                           
  RedR = pulseIn(outR, digitalRead(outR) == HIGH ? LOW : HIGH);//這裡我們等到“out”變低，我們開始測量持續時間並在“out”再次為高時停止 
  delay(20);      
  digitalWrite(s3R,HIGH);//這裡我們選擇其他顏色（光電二極管組）並使用相同的技術測量其他顏色值                                         
  BlueR = pulseIn(outR, digitalRead(outR) == HIGH ? LOW : HIGH);
  delay(20);  
  digitalWrite(s2R,HIGH);    
  GreenR = pulseIn(outR, digitalRead(outR) == HIGH ? LOW : HIGH);
  delay(20);
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
  
   pinMode(s0R,OUTPUT);
   pinMode(s1R,OUTPUT);
   pinMode(s2R,OUTPUT);
   pinMode(s3R,OUTPUT);
   pinMode(outR,INPUT);//右光感引腳模式
   pinMode(s0L,OUTPUT);
   pinMode(s1L,OUTPUT);
   pinMode(s2L,OUTPUT);
   pinMode(s3L,OUTPUT);
   pinMode(outL,INPUT);//左光感引腳模式

   Serial.begin(9600);

   digitalWrite(s0L,HIGH);
   digitalWrite(s1L,HIGH); //將 S0L/S1L 置於 HIGH/HIGH 電平表示輸出頻率縮放為 100%（推薦)
   digitalWrite(s0R,HIGH);
   digitalWrite(s1R,HIGH);
}

void loop() 
{  
   GetColorsL();
   if( 12<Read)
    
      
}
