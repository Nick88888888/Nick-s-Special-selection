void setup() {
  pinMode(13,OUTPUT);

  pinMode(12,OUTPUT); 
  
  for(int i=55;i<=62;i++){
    pinMode(i,INPUT);
  }
  Serial.begin(9600);
}
int speed1 = 90;
int value[3][6];//暫存的陣列value{61,60,59,58,57,56}
int sum_all[6];//最終算出的陣列
int count=0;//用來計數的
void loop() { 
  int sum=0,number=0;
  get_value();
 for(int i=61;i>=56;i--)
 {   
   sum+=analogRead(i);
 } 
 Serial.println(sum);
// Serial.print("\t");
// for(int i=61;i>=56;i--)
//  {
//    Serial.print(analogRead(i));   
//    Serial.print("\t");
//  }
// Serial.println();
 Serial.println(sum_all[5]);
  if(sum<3700 && sum>2800 || sum>2200 && sum<2400){
  if(analogRead(59)<=500 && analogRead(58)<=500)
  {
    if(sum_all[1]<850 && sum_all[1]>500 )
   {
    digitalWrite(13,HIGH);
    stop1();
   }
   else{
     digitalWrite(13,LOW);
   }
  if(sum_all[5]<700 && sum_all[5]>400 )  
    {
      digitalWrite(12,HIGH);
      stop1();
    }
    else{
       digitalWrite(12,LOW);
    }
  } 
  
 }
 else if(analogRead(60)<=700)
   {
    while(analogRead(59)>=500)
     {
       big_left(170);
       
    }
   }
   else if(analogRead(57)<=700)
  {
     while(analogRead(58)>=500)
    {
      big_right(170);
    
    }
  
  }
  else if(analogRead(58)>=500)
  {
    left(170);
  }
  else if(analogRead(59)>=500)
  {
    right(170);
  }
  else
  {
    straight(speed1);    
    digitalWrite(13,LOW);
    digitalWrite(12,LOW); 
  }
  delay(10);
}
