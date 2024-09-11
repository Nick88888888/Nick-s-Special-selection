void get_value(){

     digitalWrite(8,LOW);
     digitalWrite(9,HIGH);
     delay(10);  
   
      //Serial.println("TCS34725 found"); // 在串行監視器中列印感應器已找到的訊息 
     
      uint16_t clear, red, green, blue; // 定義變數用於儲存顏色資料
      tcs.getRawData(&red, &green, &blue, &clear); // 從感應器獲取原始資料
      // 列印顏色資料到串行監視器
      /*Serial.print("Clear: "); Serial.print(clear);
      Serial.print(" Red: "); Serial.print(red);
      Serial.print(" Green: "); Serial.print(green);
      Serial.print(" Blue: "); Serial.println(blue);*/
      color1[0]=red;
      color1[1]=green;
      color1[2]=blue;
      
    
  
}
