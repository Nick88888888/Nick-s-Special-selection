#include <Wire.h> // 包含Wire库，用於I2C通訊
#include "Adafruit_TCS34725.h" // 包含Adafruit_TCS34725库，用於TCS34725感應器

#define TCS34725_INTEGRATIONTIME TCS34725_INTEGRATIONTIME_50MS // 設定整合時間
#define TCS34725_GAIN TCS34725_GAIN_4X // 設定增益

int color1[3];
int color2[3];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME, TCS34725_GAIN); // 建立TCS34725物件
void setup() {
  for (int i = 2; i <= 7; i++) //設定馬達
  {
    pinMode(i, OUTPUT);
  }
  for (int i = 54; i <= 61; i++)
  {
    pinMode(i, INPUT);
  }
  Serial.begin(9600);

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  Serial.begin(9600); // 初始化串行通訊，鮑特率9600

  if (tcs.begin()) { // 如果感應器初始化成功
    Serial.println("TCS34725 found"); // 在串行監視器中列印感應器已找到的訊息
  } else {
    Serial.println("No TCS34725 found ... check your connections"); // 在串行監視器中列印感應器未找到的訊息
    while (1); // 如果感應器未找到，停止程式
  }
}
int speed1 = 80;
int judge(){
  int sum=0;
  for(int k=56;k<=59;k++)
  {
    if(analogRead(k)<=200)
      sum++;
  }
  return sum;
}
void loop() {
  get_value();
  Serial.println(analogRead(57));
   /* Serial.println(color1[0]);
    if(color1[0]<140 ){
    stop1();
    delay(5000);
    }*/
  
 /*if(analogRead(55)<=200){
   while(analogRead(58)>200);
    big_right(170);
 }
 else if(analogRead(60)<=200){
    while(analogRead(57)>200){
      big_left(170);
    }
 }
 else if(analogRead(56)<200 && analogRead(59)<200)
 {
  straight(speed1); 
 }
 else if (analogRead(60) <= 200)
  {
    while (analogRead(58) >= 200)

    {
      big_left(170);
    }
  }
  else if (analogRead(55) <= 200)
  {
    while (analogRead(57) >= 200)
    {
      big_right(170);
    }

  }
  else if (analogRead(56) <= 200)
  {
    right(200);
  }
  else if (analogRead(59) <= 200)
  {
    left(200);
  }
  else
  {
    straight(speed1);
  }

  // get_value();
  */
}
