void setup() {
  pinMode(13,OUTPUT);

  pinMode(12,OUTPUT); 
  
  for(int i=55;i<=62;i++){
    pinMode(i,INPUT);
  }
  Serial.begin(9600);
}
int speed1 = 90;
int value[5][6];//暫存的陣列
int sum_all[6];//最終算出的陣列
int count=0;//用來計數的
void loop() { 

 if(count>=4){
  count=0;
 }
 else{
  count+=1;
 }
 int sum=0,number=0;
 for(int i=61;i>=56;i--)
 {   
   sum+=analogRead(i);
 }
 for(int i=0;i<=5;i++){//把每個叫位讀出來的存進去
    value[count][i] = analogRead(61-i);
 
 }
 for(int i=0;i<=4;i++){//把整個鄭烈顯示出來
  for(int k=0;k<=5;k++)
  {
    Serial.print(value[i][k]);
    Serial.print("\t");
  }
  Serial.println();
 }
 for(int k=0;k<=5;k++){//算平均
  int all=0;
   for(int m=0;m<=4;m++){
     all+=value[m][k];
   }
   sum_all[k]= all/5;//每行加總除5
 }
 Serial.print("sum_all=");//最終算出顯示出來
 for(int k=0;k<=5;k++){
   Serial.print(sum_all[k]);
   Serial.print("\t");
 }

 Serial.println("END");
  delay(10);
}
