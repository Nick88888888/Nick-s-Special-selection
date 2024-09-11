void get_value()//右邊
{
  int sum=0;
  if(count>=4)
    {
     count=0;
    }
    else{
     count++; 
    }

  // 設定光電二極體讀取濾過的紅色值
  digitalWrite(S2_R,LOW);
  digitalWrite(S3_R,LOW);
  
  // 讀取輸出頻率
  R_avenge_red[count]= pulseIn(sensorOut_R, LOW);
  
  // 設定光電二極體讀取濾過的綠色值
  digitalWrite(S2_R,HIGH);
  digitalWrite(S3_R,HIGH); 
  // 讀取輸出頻率
  R_avenge_green[count] = pulseIn(sensorOut_R, LOW);
 
  // 設定光電二極體讀取濾過的藍色值
  digitalWrite(S2_R,LOW);
  digitalWrite(S3_R,HIGH); 
  // 讀取輸出頻率
  R_avenge_blue[count] = pulseIn(sensorOut_R, LOW);
//  Serial.print("右=");  
//   // 列出紅色值
//  Serial.print("R = ");
//  Serial.print(R_avenge_red[count]);
//  // 列出綠色值 
//  Serial.print(" G = ");
//  Serial.print(R_avenge_green[count]);
//  // 列出藍色值，並換行
//  Serial.print(" B = ");
//  Serial.print(R_avenge_blue[count]);
//  Serial.println();
  
  sum=0;//處理移動平均
  for(int i=0;i<=4;i++)
    {
      sum = sum+R_avenge_red[i];
    }
  redFrequency_R = sum/5;
  sum = 0;
  for(int i=0;i<=4;i++)
    {
      sum = sum+R_avenge_blue[i];
    }
  blueFrequency_R = sum/5;
  sum = 0;
  for(int i=0;i<=4;i++)
    {
      sum = sum+R_avenge_green[count];
    }
  greenFrequency_R = sum/5;
//  Serial.print("ra");//把陣列顯示出來
//  for(int i=0;i<=4;i++)
//   {
//    Serial.print(R_avenge_red[i]);
//    Serial.print(",");
//   }
//  Serial.println();
//  Serial.println("ba");
//  for(int i=0;i<=4;i++)
//   {    
//    Serial.print(R_avenge_blue[i]);
//    Serial.print(",");
//   }
//  Serial.println();
//  Serial.println("ga");
//  for(int i=0;i<=4;i++)
//   { 
//    Serial.print(R_avenge_green[i]);
//    Serial.print(",");
//   }
//  Serial.println();
  

 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
   
  // 設定光電二極體讀取濾過的紅色值
  digitalWrite(S2_L,LOW);
  digitalWrite(S3_L,LOW);
  // 讀取輸出頻率
  L_avenge_red[count]= pulseIn(sensorOut_L, LOW);
  
  // 設定光電二極體讀取濾過的綠色值
  digitalWrite(S2_L,HIGH);
  digitalWrite(S3_L,HIGH);
  // 讀取輸出頻率
  L_avenge_green[count] = pulseIn(sensorOut_L, LOW);

  // 設定光電二極體讀取濾過的藍色值
  digitalWrite(S2_L,LOW);
  digitalWrite(S3_L,HIGH);
  // 讀取輸出頻率
  L_avenge_blue[count] = pulseIn(sensorOut_L, LOW);

//  Serial.print("左=");
//  // 列出紅色值
//  Serial.print("R = ");
//  Serial.print(L_avenge_red[count]);
//  // 列出綠色值 
//  Serial.print(" G = ");
//  Serial.print(L_avenge_green[count]);
//  // 列出藍色值，並換行
//  Serial.print(" B = ");
//  Serial.println( L_avenge_blue[count] );

  sum=0;//處理左移動平均
  for(int i=0;i<=4;i++)
    {
      sum = sum+L_avenge_red[i];
    }
  redFrequency_L = sum/5;
  sum = 0;
  for(int i=0;i<=4;i++)
    {
      sum = sum+L_avenge_blue[i];
    }
  blueFrequency_L = sum/5;
  sum = 0;
  for(int i=0;i<=4;i++)
    {
      sum = sum+L_avenge_green[count];
    }
  greenFrequency_L = sum/5;
  delay(10);
}
