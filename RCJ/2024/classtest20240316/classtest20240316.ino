//設定右邊顏色感應器腳位
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
int sensor_error=11;

int speed1=80;
// 儲存由光電二極體讀取的值
int redFrequency_R= 0;
int greenFrequency_R = 0;
int blueFrequency_R = 0;
int redFrequency_L= 0;
int greenFrequency_L = 0;
int blueFrequency_L = 0;
void setup() {
 for(int i=2;i<=7;i++)
 {
  pinMode(i,1);
 }
 for(int i =54;i<=57;i++)
 {
  pinMode(i,OUTPUT);
 }
  for(int i =59;i<=62;i++)
 {
  pinMode(i,OUTPUT);
 }
 pinMode(sensorOut_R,INPUT);//接收顏色數值
 digitalWrite(S0_R,LOW);//影響輸出值大小
 digitalWrite(S1_R,HIGH);
 
 pinMode(sensorOut_L,INPUT);//接收顏色數值
 digitalWrite(S0_L,LOW);//影響輸出值大小
 digitalWrite(S1_L,HIGH);
 Serial.begin(9600);

 pinMode(8,OUTPUT);//LED左
 pinMode(9,OUTPUT);//LED右
}

void loop() {
  int output=0,L_output=0,R_output=0; 
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  get_value();
//  if(redFrequency_R>150 && redFrequency_R<200 && greenFrequency_R>50 && greenFrequency_R<122 
//  && redFrequency_L>180 && redFrequency_L<350 && greenFrequency_L>50 && greenFrequency_L<150){
//    stop1();
//    digitalWrite(8,HIGH);
//    digitalWrite(9,HIGH);
//    delay(1000);
//  }
//  else if(redFrequency_R>150 && redFrequency_R<200 && greenFrequency_R>50 && greenFrequency_R<122 )
//  {
//    
//     stop1();
//     digitalWrite(9,HIGH);
//     delay(1000);
//  }
//  else if(redFrequency_L>180 && redFrequency_L<350 && greenFrequency_L>50 && greenFrequency_L<150)
//  {
//    
//     stop1();
//     digitalWrite(8,HIGH);
//     delay(1000);
//  }
//  else if(redFrequency_L>100){
//   
//     left(140);
//   
//  }
//  else if(redFrequency_R>80 )
//  {
//    
//      right(140);
//
//   
//  }
//  else{
//     straight(speed1);
//  }
//  




//  output = redFrequency_L+sensor_error-redFrequency_R;
//  L_output = output*3;
//  R_output = output*3;
//  digitalWrite(3,0);
//  digitalWrite(4,1);
//  digitalWrite(5,0);
//  digitalWrite(6,1);
//  if(R_output-90<0){
//      digitalWrite(3,0);
//      digitalWrite(4,0);
//  }
//  if(L_output+90<0){
//      digitalWrite(5,0);
//      digitalWrite(6,0);
//  }
//  if(output==0){
//     analogWrite(2,90); 
//     analogWrite(7,90);
//  }
//  else{
//    analogWrite(2,int(abs(R_output-90))); 
//    analogWrite(7,int(abs(L_output+90)));
//  }

  
}
