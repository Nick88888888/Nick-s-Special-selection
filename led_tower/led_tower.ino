int x[4][4] = {
               {0,1,2,3},
               {4,5,6,7},
               {8,9,10,11},
               {12,13,14,15}
              };

void All_shine()
{
  for(int i =16;i<=19;i++)//全部亮  
     digitalWrite(i,0);
  for(int i=0;i<=15;i++)
     digitalWrite(i,1);  
}
void All_black()
{
  for(int i=0;i<=19;i++)
  digitalWrite(i,0);
}

void setup() 
{
  for(int i=0;i<=19;i++)
    pinMode(i,1);
   All_shine();
   

}

void loop() 
{  
  delay(1000);
  All_black();
  
   for(int i=0;i<=15;i++)
     digitalWrite(i,1);     
   for(int i=19;i>=16;i--)    
      digitalWrite(i,1);       
   for(int i=16;i<=19;i++)
     {
      digitalWrite(i,0);
      delay(500);  
     }
     All_black();
     delay(500);
   for(int i=0;i<=15;i++)
      digitalWrite(i,1);  
   for(int i=19;i>=16;i--)    
      digitalWrite(i,1);  
   for(int i=19;i>=16;i--)
     {
      digitalWrite(i,0);
      delay(500);  
     }
   All_black();
   delay(500);    
}
