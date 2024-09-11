void setup() {
  pinMode(13,OUTPUT);

  pinMode(12,OUTPUT); 
  
  for(int i=55;i<=62;i++){
    pinMode(i,INPUT);
  }
  Serial.begin(9600);
//  pinMode(63,INPUT);//距離感測器
}
int speed1 = 90;
int value[3][6];//暫存的陣列value{61,60,59,58,57,56}
int sum_all[6];//最終算出的陣列
int count=0;//用來計數的
void loop() { 
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

  /*if(sum<3900 && sum>3200 || sum>2200 && sum<2400)
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
              if(sum_all[1]<800 && sum_all[1]>700 )  
                see1+=1;
              delay(1000); 
              straight(150);
              delay(70);
              stop1();
              for(int a=0;a<=6;a++)
                get_value();
              if(sum_all[1]<800 && sum_all[1]>700 )  
                see1+=1;            
              if(see1>=1)
                for(int a=0;a<=6;a++)
                {
                  digitalWrite(13,HIGH);
                  delay(200);
                  digitalWrite(13,LOW);
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
                   digitalWrite(12,HIGH);
                   delay(200);
                   digitalWrite(12,LOW);
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
  
 }*/
// if(analogRead(63)>500);
// {
//  stop1();
//  delay(3000);
// }
 
  if(analogRead(60)<=500)
   {
    while(analogRead(59)>=500)
     {
       big_left(170);
       
    }
   }
   else if(analogRead(57)<=500)
  {
     while(analogRead(58)>=500)
    {
      big_right(170);
    
    }
  
  }
//  else if(analogRead(58)>=500)
//  {
//    left(140);
//  }
//  else if(analogRead(59)>=500)
//  {
//    right(140);
//  }
  else
  {
    straight(speed1);    
    digitalWrite(13,LOW);
    digitalWrite(12,LOW); 
  }
  delay(1);
}
