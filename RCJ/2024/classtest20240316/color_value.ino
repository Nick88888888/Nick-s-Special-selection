void get_value()//右邊
{
  Serial.print("右=");
  // 設定光電二極體讀取濾過的紅色值
  digitalWrite(S2_R,LOW);
  digitalWrite(S3_R,LOW);
  
  // 讀取輸出頻率
  redFrequency_R= pulseIn(sensorOut_R, LOW);
  
   // 列出紅色值
  Serial.print("R = ");
  Serial.print(redFrequency_R);
 
  
  // 設定光電二極體讀取濾過的綠色值
  digitalWrite(S2_R,HIGH);
  digitalWrite(S3_R,HIGH);
  
  // 讀取輸出頻率
  greenFrequency_R = pulseIn(sensorOut_R, LOW);
  
  // 列出綠色值 
  Serial.print(" G = ");
  Serial.print(greenFrequency_R);
 
 
  // 設定光電二極體讀取濾過的藍色值
  digitalWrite(S2_R,LOW);
  digitalWrite(S3_R,HIGH);
  
  // 讀取輸出頻率
  blueFrequency_R = pulseIn(sensorOut_R, LOW);
  
  // 列出藍色值，並換行
  Serial.print(" B = ");
  Serial.print(blueFrequency_R);
  Serial.println();
//  
//   Serial.print("左=");
//  // 設定光電二極體讀取濾過的紅色值
//  digitalWrite(S2_L,LOW);
//  digitalWrite(S3_L,LOW);
//  
//  // 讀取輸出頻率
//  redFrequency_L= pulseIn(sensorOut_L, LOW);
//  
//   // 列出紅色值
//  Serial.print("R = ");
//  Serial.print(redFrequency_L);
// 
//  
//  // 設定光電二極體讀取濾過的綠色值
//  digitalWrite(S2_L,HIGH);
//  digitalWrite(S3_L,HIGH);
//  
//  // 讀取輸出頻率
//  greenFrequency_L = pulseIn(sensorOut_L, LOW);
//  
//  // 列出綠色值 
//  Serial.print(" G = ");
//  Serial.print(greenFrequency_L);
//  
// 
//  // 設定光電二極體讀取濾過的藍色值
//  digitalWrite(S2_L,LOW);
//  digitalWrite(S3_L,HIGH);
//  
//  // 讀取輸出頻率
//  blueFrequency_L = pulseIn(sensorOut_L, LOW);
//  
//  // 列出藍色值，並換行
//  Serial.print(" B = ");
//  Serial.println(blueFrequency_L);
//  delay(10);
}
