/************************************************************************************
 *  添加而外開發版管理員網址
 *  https://dl.espressif.com/dl/package_esp32_index.json
 *  
 *  下載 Blynk Library (Version 1.0.1):
 *  https://github.com/blynkkk/blynk-library
 **********************************************************************************/
//設定BLYNK TEMPLATE ID 與裝置名稱
/*
#define BLYNK_TEMPLATE_ID "TMPLw-gJunRa"
#define BLYNK_DEVICE_NAME "SWBOT"
#define BLYNK_AUTH_TOKEN "f_2d31yVN0elcwFNRJhRyIBlovLSUm7c";
*/
#define BLYNK_TEMPLATE_ID "TMPLXucau1n7"
#define BLYNK_DEVICE_NAME "SWBOT2"
#define BLYNK_AUTH_TOKEN "-qbvhQAx88-HHTrqEnqpg1UlVrTnQvu9";

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// 設定WIFI名稱與WIFI密碼
char ssid[] = "CHT 17";
char pass[] = "0911117489";

BlynkTimer timer;

#include <ESP32Servo.h>
WiFiServer server(80);
Servo myservo;
int pos = 0;
int servoPin = 13;
int SWBOT_state = 0;

//當裝置連接上BLYNL.CLOUD時會用這個function跟SERVER要求最新狀態
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0);
}

//每當網站或行動裝置觸發Virtul pin時 程式便會執行BLYNK_WRITE這個function
BLYNK_WRITE(V0) {
  SWBOT_state = param.asInt();
  Serial.println(SWBOT_state);
  if(SWBOT_state)
  {
      myservo.write(0);
      delay(1000);
      myservo.write(90);
  }
  else
  {
      myservo.write(180); 
      delay(1000);
      myservo.write(90);
  }
}
//--------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  Blynk.virtualWrite(V0, SWBOT_state);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin);
}

void loop()
{
  Blynk.run();
  timer.run();
}
