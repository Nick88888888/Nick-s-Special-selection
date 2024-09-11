/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#include <WiFi.h>
#include <WiFiClientSecure.h>
#define BLYNK_TEMPLATE_ID "TMPL6aIl7p6DS"
#define BLYNK_TEMPLATE_NAME "LED ESP32"



String Linetoken = "NF2FGkP1IBDLjsEHrelMd3IWvkuJHvlocdvZfyLEMKy";//LINE權杖密碼

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
WiFiClientSecure client1;
char host[] = "notify-api.line.me";


#include "BlynkEdgent.h"
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0);
}
int SWBOT_state = 0;
//每當網站或行動裝置觸發Virtul pin時 程式便會執行BLYNK_WRITE這個function
BLYNK_WRITE(V0) {
  SWBOT_state = param.asInt();
  Serial.println(SWBOT_state);
  if(SWBOT_state)
  {
      
      
     
      client1.setInsecure();
      String message = "換水";
      if(client1.connect(host,443))
      {
        int LEN = message.length();//計算訊息長度
        //傳遞網站
        String url = "/api/notify ";
        client1.println("POST " + url + "HTTP/1.1");
        client1.print("Host: ");
        client1.println(host);
        
        //資料表頭
        client1.println("Authorization: Bearer " + Linetoken);
        client1.println("Content-length: " + String(LEN + 8));
        //內容格式
        client1.println("Content-Type: application/x-www-form-urlencoded");
  
        //資料內容
        
        client1.println();
        client1.println("message=" + message);
  
        //等候回應
        delay(20);
        String response = client1.readString();
  
        //顯示傳遞結果
        Serial.println("回傳結果" + response);
  
        //斷開連線
        Serial.print("水=");
        Serial.println(analogRead(2));
        client1.stop();
        digitalWrite(3,HIGH);
        digitalWrite(14,LOW);
        delay(1000);
        Serial.println("okok");
        digitalWrite(3,LOW); 
        delay(1000);  
        digitalWrite(12,1);
         delay(10000);     
        Serial.println("結束");
       
        digitalWrite(12,0);
        digitalWrite(14,LOW); 
        digitalWrite(3,LOW); 
      }
  }
  
 }


char ssid[]="1F";
char password[]="0915676129";
//char ssid[]="funrobot";
//char password[]="fun0426622863";


void setup()
{ Serial.print("開始連線到無線網路SSID:");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("連線完成");
  pinMode(3,OUTPUT);
  pinMode(14,1);
  pinMode(12,OUTPUT);
  digitalWrite(12,0);
  pinMode(1,INPUT);
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
 
}
