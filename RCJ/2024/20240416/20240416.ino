void setup() {
  pinMode(13,OUTPUT);

  pinMode(12,OUTPUT); 
  
  for(int i=55;i<=62;i++){
    pinMode(i,INPUT);
  }
  Serial.begin(9600);
}
int speed1 = 90;
void loop() { 

  // put your main code here, to run repeatedly:
  int sum=0;
 for(int i=61;i>=56;i--)
    sum+=analogRead(i);
 Serial.print(sum);
 Serial.print("\t");
 for(int i=61;i>=56;i--)
  {
    Serial.print(analogRead(i));   
    Serial.print("\t");
  }
 Serial.println();
 
 if(sum<3600 && sum>3000){
  if(analogRead(58)<=100 && analogRead(59)<=100)
  {if(analogRead(60)<800 && analogRead(60)>500 )
   {
    digitalWrite(13,HIGH);
    stop1();
   }
  if(analogRead(57)<500 && analogRead(57)>400 )  
    {
      Serial.println(analogRead(57));
      digitalWrite(12,HIGH);
      stop1();
    }
  } 
  
 }
 else if(analogRead(60)<=500)
   {
    while(analogRead(58)>=500)
     {
       big_left(190);
    }
   }
   else if(analogRead(57)<=500)
  {
     while(analogRead(59)>=500)
    {
     big_right(190);
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
}
