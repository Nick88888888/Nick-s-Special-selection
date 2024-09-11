#define S0 57
#define S1 56
#define S2 55
#define S3 54
#define sensorOut 58
int speed1=100;
// 儲存由光電二極體讀取的值
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
void setup() {
 for(int i=2;i<=7;i++)
 {
  pinMode(i,1);
 }
 for(int i =54;i<=57;i++)
 {
  pinMode(i,OUTPUT);
 }
 pinMode(sensorOut,INPUT);//接收顏色數值
 digitalWrite(S0,HIGH);//影響輸出值大小
 digitalWrite(S1,LOW);

 Serial.begin(9600);

}

void loop() {

  get_value();
  if(redFrequency<100)
  {
    straight(speed1);
    Serial.println("white");
  }
  else{
    stop1();
  }
}



void stop1(){
  analogWrite(2, 255);
  digitalWrite(3,1);
  digitalWrite(4,1);
  analogWrite(7, 255);
  digitalWrite(5,1);
  digitalWrite(6,1);
}
void back(int i){ 
  analogWrite(2, i);
  digitalWrite(3,1);
  digitalWrite(4,0);
  analogWrite(7, i);
  digitalWrite(5,1);
  digitalWrite(6,0);
}
void straight(int i){
  analogWrite(2,i);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i);
  digitalWrite(5,0);
  digitalWrite(6,1);
}
void left(int i){
  analogWrite(2,i);
  digitalWrite(3,1);
  digitalWrite(4,0);
  analogWrite(7,i);
  digitalWrite(5,0);
  digitalWrite(6,1);
}
void right(int i){
  analogWrite(2,i);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i);
  digitalWrite(5,1);
  digitalWrite(6,0);
}
void get_value(){
  // 設定光電二極體讀取濾過的紅色值
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // 讀取輸出頻率
  redFrequency = pulseIn(sensorOut, LOW);
  
   // 列出紅色值
  Serial.print("R = ");
  Serial.print(redFrequency);
  delay(100);
  
  // 設定光電二極體讀取濾過的綠色值
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // 讀取輸出頻率
  greenFrequency = pulseIn(sensorOut, LOW);
  
  // 列出綠色值 
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  delay(100);
 
  // 設定光電二極體讀取濾過的藍色值
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // 讀取輸出頻率
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // 列出藍色值，並換行
  Serial.print(" B = ");
  Serial.println(blueFrequency);
  delay(100);
}
