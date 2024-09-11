//It need to download "Adafruit TCS34725"

#include <Wire.h> // 包含Wire库，用於I2C通訊
#include "Adafruit_TCS34725.h" // 包含Adafruit_TCS34725库，用於TCS34725感應器

#define TCS34725_INTEGRATIONTIME TCS34725_INTEGRATIONTIME_50MS // 設定整合時間
#define TCS34725_GAIN TCS34725_GAIN_4X // 設定增益

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME, TCS34725_GAIN); // 建立TCS34725物件

void setup() {
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

void loop() { 
   for(int i=0;i<=2;i++){
     digitalWrite(8,LOW);
     digitalWrite(9,HIGH);
     delay(10);  
     if (tcs.begin()) { // 如果感應器初始化成功
      Serial.println("TCS34725 found"); // 在串行監視器中列印感應器已找到的訊息 
     
      uint16_t clear, red, green, blue; // 定義變數用於儲存顏色資料
      tcs.getRawData(&red, &green, &blue, &clear); // 從感應器獲取原始資料
      // 列印顏色資料到串行監視器
      Serial.print("Clear: "); Serial.print(clear);
      Serial.print(" Red: "); Serial.print(red);
      Serial.print(" Green: "); Serial.print(green);
      Serial.print(" Blue: "); Serial.println(blue);
      
     } else {
      Serial.println("No TCS34725 found1 ... check your connections"); // 在串行監視器中列印感應器未找到的訊息
     
     }
   }
    for(int i=0;i<=2;i++){
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      delay(10); 
      if (tcs.begin()) { // 如果感應器初始化成功
      Serial.println("TCS34725 found2"); // 在串行監視器中列印感應器已找到的訊 
      uint16_t clear, red, green, blue; // 定義變數用於儲存顏色資料
      tcs.getRawData(&red, &green, &blue, &clear); // 從感應器獲取原始資料
      // 列印顏色資料到串行監視器
      Serial.print("Clear: "); Serial.print(clear);
      Serial.print(" Red: "); Serial.print(red);
      Serial.print(" Green: "); Serial.print(green);
      Serial.print(" Blue: "); Serial.println(blue);
      } else {
        Serial.println("No TCS34725 found2 ... check your connections"); // 在串行監視器中列印感應器未找到的訊息
       
      }
    }
 
}
