void get_value(){
  if(count>=2){
  count=0;
 }
 else{
  count+=1;
 }

 for(int i=0;i<=5;i++){//把每個叫位讀出來的存進去
    value[count][i] = analogRead(61-i);
    //Serial.print(61-i);

 }
 /*for(int i=0;i<=2;i++){//把整個陣列顯示出來
  for(int k=0;k<=5;k++)
  {
    Serial.print(value[i][k]);
    Serial.print("\t");
  }
  Serial.println();
 }*/
 for(int k=0;k<=5;k++){//算平均
  int all=0;
   for(int m=0;m<=2;m++){
     all+=value[m][k];
   }
   sum_all[k]= all/3;//每行加總除3
 }
   Serial.print("sum_all=");//最終算出顯示出來
  for(int k=0;k<=5;k++){
   Serial.print(sum_all[k]);
   Serial.print("\t");
 }

 Serial.println("END");
}
double get_IR (uint16_t value) {
 if (value < 16) value = 16;
 return 2076.0 / (value - 11.0);
}
void encoder() {
  // Add this line to see if the encoder signal is being detected
//  Serial.println("Encoder signal detected!");

  if (digitalRead(ENCODER2) == HIGH) {
    encoder_pos++;
  } else {
    encoder_pos--;
  }
}
