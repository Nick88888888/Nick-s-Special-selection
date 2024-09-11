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

int speed1=90;
// 儲存由光電二極體讀取的值
long int redFrequency_R= 0;
long int greenFrequency_R = 0;
long int blueFrequency_R = 0;
long int redFrequency_L= 0;
long int greenFrequency_L = 0;
long int blueFrequency_L = 0;
int R_avenge_red[5],R_avenge_blue[5],R_avenge_green[5];//設定右邊的移動平均變數
int L_avenge_red[5],L_avenge_blue[5],L_avenge_green[5];//設定右邊的移動平均變數
int count=0;
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
 digitalWrite(S0_R,HIGH);//影響輸出值大小
 digitalWrite(S1_R,HIGH);
 
 pinMode(sensorOut_L,INPUT);//接收顏色數值
 digitalWrite(S0_L,HIGH);//影響輸出值大小
 digitalWrite(S1_L,HIGH);
 Serial.begin(9600);

 pinMode(8,OUTPUT);//LED左
 pinMode(9,OUTPUT);//LED右
}
long int R_error_past=0,L_error_past=0; 
void loop() {
  int output=0,L_output=0,R_output=0; 
  digitalWrite(8,LOW);
  digitalWrite(9,LOW); 
  get_value();
  long int R_error=0,L_error=0;
  long int R_white=0,R_black=0,R_green=0,L_white=0,L_black=0,L_green=0;
  R_white = sq(7-redFrequency_R)+sq(5-blueFrequency_R);
  R_black= sq(17-redFrequency_R)+sq(13-blueFrequency_R);
  R_green = sq(41-redFrequency_R)+sq(22-blueFrequency_R);
  L_white = sq(9-redFrequency_L)+sq(8-blueFrequency_L);
  L_black= sq(20-redFrequency_L)+sq(16-blueFrequency_L);
  L_green = sq(57-redFrequency_L)+sq(31-blueFrequency_L);
 
 /* Serial.print(w);
  Serial.print(",");
  Serial.print(q);
  Serial.print(",");
  Serial.println(r);
  if(w<q && w<r){
    Serial.println("白");
  }
  if(q<w && q<r){
    Serial.println("黑");
  }
  if(r<w && r<q){
    Serial.println("綠");
  }*/
//  Serial.print("R=");
//  Serial.print(R_white);
//  Serial.print(",");
//  Serial.print(R_black);
//  Serial.print(",");
//  Serial.print(R_green);
//  Serial.print("\t");
//  Serial.print("L=");
//  Serial.print(L_white);
//  Serial.print(",");
//  Serial.print(L_black);
//  Serial.print(",");
//  Serial.println(L_green);
  

    if( (R_green< R_black&& R_green< R_white && R_green<50 ) || (L_green < L_black && L_green < L_white && L_green<50) ){
//      back(speed1);
      
      stop1();
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      delay(1000);
    }
 
    
    else if( L_black <L_white){
     
       left(200);
       Serial.println("右轉");
    }
    else if(R_black <R_white)
    {
        right(200);
        Serial.println("左轉");
     
    }
    else{
       Serial.println("直走");
       straight(speed1);
    }
    delay(10);

 
  
}
