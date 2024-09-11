volatile long int encoder_pos = 0;
#define ENCODER1 21
#define ENCODER2 20
void setup() {
  pinMode(22,OUTPUT);//LED燈
  pinMode(24,OUTPUT); 
  digitalWrite(22,HIGH);
  digitalWrite(24,HIGH);
  delay(500);
  digitalWrite(22,LOW);//左邊
  digitalWrite(24,LOW);
  
  for(int i=55;i<=62;i++){
    pinMode(i,INPUT);
  }
  Serial.begin(9600);
  pinMode(63,INPUT);//距離感測器
 // attachInterrupt(digitalPinToInterrupt(ENCODER1), encoder, RISING);
  pinMode(ENCODER1, INPUT);
  pinMode(ENCODER2, INPUT);
}
int speed1 = 70;
int value[3][6];//暫存的陣列value{61,60,59,58,57,56}
int sum_all[6];//最終算出的陣列
int count=0;//用來計數的
void loop() { 
  Serial.print("Encoder Count: ");
  Serial.println(encoder_pos);

uint16_t value_d = analogRead (63);
 double distance = get_IR (value_d); //Convert the analog voltage to the distance
 Serial.println (value_d); //Print the data to the arduino serial monitor
 Serial.print (distance);
 Serial.println (" cm");
 Serial.println ();
//  Serial.print("雷色距離:");
//  Serial.println(analogRead(63));
  int sum=0,number=0;

 for(int i=61;i>=56;i--)
 {   
   sum+=analogRead(i);
 } 
 Serial.println(sum);
 Serial.print("\t");
 for(int i=61;i>=56;i--)
  {
    Serial.print(analogRead(i));   
    Serial.print("\t");
  }
 Serial.println();

  if(sum<3900 && sum>3200 || sum>2200 && sum<2400)
  {
      get_value(); 
      Serial.println(sum_all[5]);
      if(analogRead(59)<=500 && analogRead(58)<=500)
      {   int see1=0;//用來確保有沒有看到
          int see2=0;//用來確保有沒有看到
          if(sum_all[1]<850 && sum_all[1]>600 )
            {
              
              stop1();
              delay(100);
              back(150);
              delay(70);
              stop1();
              for(int a=0;a<=3;a++)
                get_value();
              if(sum_all[1]<850 && sum_all[1]>700 )  
                see1+=1;
              delay(1000); 
              straight(150);
              delay(70);
              stop1();
              for(int a=0;a<=6;a++)
                get_value();
              if(sum_all[1]<850 && sum_all[1]>700 )  
                see1+=1;            
              if(see1>=1)
                for(int a=0;a<=6;a++)
                {
                  digitalWrite(22,HIGH);
                  delay(200);
                  digitalWrite(22,LOW);
                  delay(200);
                }   
            }
          else
            {
             digitalWrite(13,LOW);
            }
            
          if(sum_all[4]<800 && sum_all[4]>600 )  
            {
              
               stop1();
               delay(100);
               back(150);
               delay(70);
               stop1();
               for(int a=0;a<=6;a++)
                 get_value();
               if(sum_all[4]<750 && sum_all[4]>600 )  
                 see2+=1;
               delay(1000);
               straight(150);
               delay(70);
               stop1();
               for(int a=0;a<=6;a++)
                 get_value();
               if(sum_all[4]<750 && sum_all[4]>600 )  
                 see2+=1;            
               if(see2>=1)
                 for(int a=0;a<=2;a++)
                 {
                   digitalWrite(24,HIGH);
                   delay(200);
                   digitalWrite(24,LOW);
                   delay(200);
                 }   
            }
          else
            {
               digitalWrite(12,LOW);
            }
            Serial.print("see1 and see2");
            Serial.print(see1);
            Serial.print("\t");
            Serial.println(see2);
            
            if(see1 >=1 && see2>=1)
            {
                return1(160);
            }
            else if(see1>=1)
            {
              turn_left(160);
            }
            else if(see2>=1)
            {
              turn_right(160);
              
            }
            else{
             straight(90);
             delay(1);
            }
      } 
  
 }
 if(distance<=5.0)
 {
  stop1();
  delay(1000);
  barrier(175);
 }
 if(analogRead(61)<=200){
  while(analogRead(58)>=500)
     {
       big_left(160);
       
    }
 }
 else if(analogRead(56)<=200){
    while(analogRead(59)>=500)
    {
      big_right(160);
    
    }
 }
 else if(analogRead(60)<=500)
   {
    while(analogRead(59)>=500)
     {
       big_left(140);
       
    }
   }
   else if(analogRead(57)<=500)
  {
     while(analogRead(58)>=500)
    {
      big_right(140);
    
    }
  
  }
  else
  {
    straight(speed1);    
    digitalWrite(13,LOW);
    digitalWrite(12,LOW); 
  }
  delay(1);
}
