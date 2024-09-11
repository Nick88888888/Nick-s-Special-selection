//#define 14 14//設定幫浦的腳位
//#define 15 15
//#define water_level 0//設定水位感測器腳位
//#define water_valve_A 12//設定水閥腳位
//#define water_valve_B 13
void setup() {
  pinMode(14,OUTPUT);//設定幫浦的腳位為輸出腳
  pinMode(15,OUTPUT);//設定幫浦的腳位為輸出腳
//  pinMode(pump_speed,OUTPUT);//設定幫浦速度的腳位為輸出腳
//  pinMode(water_level,INPUT);//水位感測器的腳位為輸入腳
//  pinMode(water_valve_A,OUTPUT);//設定水閥的腳位為輸出腳
//  pinMode(water_valve_B,OUTPUT);//設定水閥的腳位為輸出腳
  pinMode(0,INPUT);
  Serial.begin(115200);//鮑率設定9600
}
int water_value=0;//宣告水位高度變數
void loop() {
   water_value = analogRead(0);//水位感測器讀取到值存入water_value
   if(water_value<1000){//判斷水位高度
      pump_run();
   }else{
      pump_stop();
   }
  Serial.println(water_value);
    pump_run();
}
int pump_run(){//建立一個幫浦運做的函式
    digitalWrite(14,HIGH);//把幫浦A變為高電壓
    digitalWrite(15,LOW);//把幫浦B變為低電壓
    delay(20);
    digitalWrite(14,LOW);//把幫浦A變為低電壓
    digitalWrite(15,LOW);//把幫浦B變為低電壓
    delay(20);
}
int pump_stop(){//建立一個幫浦停止的函式
    digitalWrite(14,LOW);//把幫浦A變為低電壓
    digitalWrite(15,LOW);//把幫浦B變為低電壓
   
}
