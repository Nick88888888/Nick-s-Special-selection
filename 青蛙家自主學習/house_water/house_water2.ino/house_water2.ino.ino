#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
#include "DHT.h"
#define DHTPIN 9 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。
LiquidCrystal_I2C lcd(0x27, 16, 4); 


void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();  //初始化DHT
  // 初始化LCD
  lcd.init();
  lcd.backlight();
  pinMode(4,1);
  pinMode(5,1);
  pinMode(6,1);
  pinMode(7,1);
  pinMode(A0,INPUT_PULLUP);
  
}
void play(){
  lcd.clear();
 
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
   delay(20000);
   digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
       lcd.init();
       lcd.backlight();
}
int count=1,past,now;
void loop() {
   if(count>2){
    count=1;
  }
  now = digitalRead(A0) ;
  if(now!=past && digitalRead(A0)==LOW)  
    count+=1;
  past = now;
  if(count==2){
    play();
    count=1;
  }
  Serial.println(count);
  
  float h = dht.readHumidity();   //取得濕度
  float t = dht.readTemperature();  //取得溫度C
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  
  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("RH  :");  //Relative Humidity 相對濕度簡寫
  lcd.setCursor(7, 0);  
  lcd.print(h);
  lcd.setCursor(14, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);  //設定游標位置 (字,行)
  lcd.print("Temp:");
  lcd.setCursor(7, 1);  
  lcd.print(t);
  lcd.setCursor(13, 1);
  lcd.print((char)223); //用特殊字元顯示符號的"度"
  lcd.setCursor(14, 1);
  lcd.print("C");
  delay(300);
}
