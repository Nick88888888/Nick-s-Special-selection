#define S0_R 57
#define S1_R 56
#define S2_R 55
#define S3_R 54
#define sensorOut_R 58
//設定左邊顏色感應器腳位
#define S0_L 60
#define S1_L 59
#define S2_L 61
#define S3_L 62
#define sensorOut_L 63
long int redFrequency_R= 0;
long int greenFrequency_R = 0;
long int blueFrequency_R = 0;
long int redFrequency_L= 0;
long int greenFrequency_L = 0;
long int blueFrequency_L = 0;
void setup() {
  for(int i =54;i<=57;i++)
 {
  pinMode(i,OUTPUT);
 }
  for(int i =59;i<=62;i++)
 {
  pinMode(i,OUTPUT);
 }
  pinMode(sensorOut_R,INPUT);//接收顏色數值
 digitalWrite(S0_R,HIGH);//影響輸出值大小
 digitalWrite(S1_R,HIGH);
 
 pinMode(sensorOut_L,INPUT);//接收顏色數值
 digitalWrite(S0_L,HIGH);//影響輸出值大小
 digitalWrite(S1_L,HIGH);
 Serial.begin(9600);

 pinMode(8,OUTPUT);//LED左
 pinMode(9,OUTPUT);//LED右

}

void loop() {
  int a=0,b=0,c=0;
//  Serial.print("右=");
  // 設定光電二極體讀取濾過的紅色值
  digitalWrite(S2_R,LOW);
  digitalWrite(S3_R,LOW);
  
  // 讀取輸出頻率
  redFrequency_R= pulseIn(sensorOut_R, LOW);
  
   // 列出紅色值

 
  
  // 設定光電二極體讀取濾過的綠色值
  digitalWrite(S2_R,HIGH);
  digitalWrite(S3_R,HIGH);
  
  // 讀取輸出頻率
  greenFrequency_R = pulseIn(sensorOut_R, LOW);
  
  // 列出綠色值 

 
 
  // 設定光電二極體讀取濾過的藍色值
  digitalWrite(S2_R,LOW);
  digitalWrite(S3_R,HIGH);
  
  // 讀取輸出頻率
  blueFrequency_R = pulseIn(sensorOut_R, LOW);
// // 列出紅色值
//  Serial.print("右=");
//  Serial.print("R = ");
//  Serial.print(redFrequency_R);
//  // 列出綠色值 
//  Serial.print(" G = ");
//  Serial.print(greenFrequency_R);
//  // 列出藍色值，並換行
//  Serial.print(" B = ");
//  Serial.println(blueFrequency_R);
 


  
  // 設定光電二極體讀取濾過的紅色值
  digitalWrite(S2_L,LOW);
  digitalWrite(S3_L,LOW);
  
  // 讀取輸出頻率
  redFrequency_L= pulseIn(sensorOut_L, LOW);

  
  // 設定光電二極體讀取濾過的綠色值
  digitalWrite(S2_L,HIGH);
  digitalWrite(S3_L,HIGH); 
  // 讀取輸出頻率
  greenFrequency_L = pulseIn(sensorOut_L, LOW);
 
  // 設定光電二極體讀取濾過的藍色值
  digitalWrite(S2_L,LOW);
  digitalWrite(S3_L,HIGH);
  
  // 讀取輸出頻率
  blueFrequency_L = pulseIn(sensorOut_L, LOW);
//  Serial.print("左=");
//  // 列出紅色值
//  Serial.print("R = ");
//  Serial.print(redFrequency_L);
//  // 列出綠色值 
//  Serial.print(" G = ");
//  Serial.print(greenFrequency_L);
//  // 列出藍色值，並換行
//  Serial.print(" B = ");
//  Serial.println(blueFrequency_L);
// 

  long int R_white=0,R_black=0,R_green=0,L_white=0,L_black=0,L_green=0;
  R_white = sq(7-redFrequency_R)+sq(5-blueFrequency_R);
  R_black= sq(17-redFrequency_R)+sq(13-blueFrequency_R);
  R_green = sq(41-redFrequency_R)+sq(22-blueFrequency_R);
  L_white = sq(9-redFrequency_L)+sq(8-blueFrequency_L);
  L_black= sq(22-redFrequency_L)+sq(16-blueFrequency_L);
  L_green = sq(41-redFrequency_L)+sq(25-blueFrequency_L);
  Serial.print("R=");
  Serial.print(R_white);
  Serial.print(",");
  Serial.print(R_black);
  Serial.print(",");
  Serial.print(R_green);
  Serial.print("\t");
  Serial.print("L=");
  Serial.print(L_white);
  Serial.print(",");
  Serial.print(L_black);
  Serial.print(",");
  Serial.println(L_green);
  
  delay(500);
}
