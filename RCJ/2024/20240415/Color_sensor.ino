void get_value(){
  uint16_t clear1, red1, green1, blue1; // 定義第一個感應器的顏色資料變數
  uint16_t clear2, red2, green2, blue2; // 定義第二個感應器的顏色資料變數

  tcs1.getRawData(&red1, &green1, &blue1, &clear1); // 從第一個感應器獲取原始資料
  tcs2.getRawData(&red2, &green2, &blue2, &clear2); // 從第二個感應器獲取原始資料

  // 列印第一個感應器的顏色資料到串行監視器
  Serial.print("Sensor 1 - Clear: "); Serial.print(clear1);
  Serial.print(" Red: "); Serial.print(red1);
  Serial.print(" Green: "); Serial.print(green1);
  Serial.print(" Blue: "); Serial.println(blue1);

  // 列印第二個感應器的顏色資料到串行監視器
  Serial.print("Sensor 2 - Clear: "); Serial.print(clear2);
  Serial.print(" Red: "); Serial.print(red2);
  Serial.print(" Green: "); Serial.print(green2);
  Serial.print(" Blue: "); Serial.println(blue2);

  delay(10); 
}
