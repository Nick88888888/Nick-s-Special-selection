int x[4][4] = {  {0,1,2,3},
                 {4,5,6,7},
                 {8,9,10,11},
                 {12,13,14,15}
               };

int delay_time =3;
void black()
{
  for(int i=0;i<=19;i++)
  {
    digitalWrite(i,0);
  }
}
void setup() 
{
  for(int i=0;i<=19;i++)
     pinMode(i,1);  
  for(int i=16;i<=19;i++)//起始全亮
     digitalWrite(i,0);
  for(int i=0;i<=15;i++)
     digitalWrite(i,1);
     delay(1000);
  black();

}

void loop() 
{
  black();
  for(int i=16;i<=19;i++)//從上往下
     digitalWrite(i,1);
  for(int i=0;i<=15;i++)
     digitalWrite(i,1);
  for(int i=16;i<=19;i++)
  {
     digitalWrite(i,0);
     delay(400);
     digitalWrite(i,1);
     delay(300);
  }
  delay(200);

  for(int i=16;i<=19;i++)//從下往上
     digitalWrite(i,1);
  for(int i=0;i<=15;i++)
     digitalWrite(i,1);
  for(int i=19;i>=16;i--)
  {
     digitalWrite(i,0);
     delay(400);
     digitalWrite(i,1);
     delay(300);
  }
  delay(300);

   black();
   for(int i=0;i<=3;i++)//從右往左
     {
      for(int j=0;j<=3;j++)
        {
          digitalWrite(x[i][j],1);
        }
        delay(300);
     }
     
    delay(300);
    black();
   for(int i=3;i>=0;i--)//從左往右
     {
      for(int j=3;j>=0;j--)
        {
          digitalWrite(x[i][j],1);
        }
        delay(300);
     }
     delay(300);

    black();
    for(int i=16;i<=19;i++)//亂閃
       digitalWrite(i,1);
    for(int i=1;i<=30;i++)
       {
        int b = random(16,20);
        int a = random(0,15);
        digitalWrite(a,1);
        digitalWrite(b,0);
        delay(50);
        digitalWrite(b,1);
        digitalWrite(a,0);
        delay(30);
       }
       
       black();    
       for(int i=0;i<=3;i++)//蛇行
       {
        if(i%2==1)//看要從上往下還是相反
          {
            for(int j=3;j>=0;j--)
              {
                digitalWrite(x[i][j],1);
                delay((i+1)*60);
              }
          } 
         else
         {
            for(int w=0;w<=3;w++)
               {
                digitalWrite(x[i][w],1);
                delay((i+1)*60);      
               }
         }
       }
       delay(300);
       
       for(int i=3;i>=0;i--)//蛇行
       {
        if(i%2==1)
          {
            for(int j=0;j<=3;j++)
              {
                digitalWrite(x[i][j],0);
                delay(i*60);
              }
          } 
         else
         {
            for(int w=3;w>=0;w--)
               {
                digitalWrite(x[i][w],0);
                delay(i*60);      
               }
         }
       }
       delay(300);

       black();
       for(int j=1;j<=2;j++)//全亮
         {
           for(int i=0;i<=15;i++)
              digitalWrite(i,1);
           delay(150);
           for(int i=0;i<=15;i++)
              digitalWrite(i,0);
           delay(50);
         }
        delay(250);

       black();
       for(int i=1;i<=30;i++)//下雨
       {
        int a = random(0,16);
        for(int i=16;i<=19;i++)
        digitalWrite(i,1);
        digitalWrite(a,1);
        for(int i=16;i<=19;i++)
           {
            digitalWrite(i,0);
            delay(30);
           }
        for(int i=16;i<=19;i++)
          {
            digitalWrite(i,1);
            delay(30);
          }
          digitalWrite(a,0);
       }
       delay(200);

       black();
       for(int k=16;k<=19;k++)//一層一層蛇行
         digitalWrite(k,1);
       for(int k=16;k<=19;k++)
       {
        digitalWrite(k,0);
       if(k%2==1)
       { 
       for(int i=3;i>=0;i--)
       {
        if(i%2==0)
        {
          for(int j=3;j>=0;j--)
          {
            digitalWrite(x[i][j],1);
            delay(30);
          }
        }
        else
          {
            for(int j=0;j<=3;j++)
            {
              digitalWrite(x[i][j],1);
              delay(30);
            }
          }
       }
       }
       else
       {
         for(int i=0;i<=3;i++)
       {
        if(i%2==1)
        {
          for(int j=0;j<=3;j++)
          {
            digitalWrite(x[i][j],1);
            delay(30);
          }
        }
        else
          {
            for(int j=3;j>=0;j--)
            {
              digitalWrite(x[i][j],1);
              delay(30);
            }
          }
       }
       }
       digitalWrite(k,1);
       for(int l=0;l<=15;l++)
       digitalWrite(l,0);
       
       }
       
       delay(300);

       black();
       for(int i=1;i<=10;i++)//上下交換
       {
       digitalWrite(17,1);
       digitalWrite(19,1);
       for(int i=0;i<=15;i++)
          digitalWrite(i,1);
       delay(200);   
       black();
       digitalWrite(16,1);
       digitalWrite(18,1);
       for(int i=0;i<=15;i++)
          digitalWrite(i,1);
       delay(200);
       black();
       }

     for(int t=0;t<=5;t++)
     {
       black();
       
       for(int i=2;i<=5;i++)
       {
        if(i%2==0)
        {
          for(int j=1;j<=3;j+=2)
          digitalWrite(x[i-2][j],1);
        }
        else
        {
          for(int j=0;j<=2;j+=2)
          digitalWrite(x[i-2][j],1);
        }
       }
      
       delay(100);
       black();
     
       for(int i=2;i<=5;i++)
       {
        if(i%2==1)
        {
          for(int j=1;j<=3;j+=2)
          digitalWrite(x[i-2][j],1);
        }
        else
        {
          for(int j=0;j<=2;j+=2)
          digitalWrite(x[i-2][j],1);
        }
       }
      
    delay(100);
       
       
     black();

     for(int w=0;w<=10;w++)  //
     {
      black();
       for(int k=16;k<=19;k++)
       digitalWrite(k,1);
       digitalWrite(17,0);
       digitalWrite(19,0);
      for(int i=0;i<=3;i+=1)
      {
        if(i%2==0)
        {
          for(int j=0;j<=3;j+=2)
          {
            digitalWrite(x[i][j],1);
          }
        }
        else
        {
          for(int j=1;j<=3;j+=2)
          {
            digitalWrite(x[i][j],1);
          }
        }
      }

    delay(delay_time);
    for(int k=16;k<=19;k++)
       digitalWrite(k,1);
     digitalWrite(16,0);
     digitalWrite(18,0);
    for(int i=0;i<=3;i+=1)
      {
        if(i%2==0)
        {
          for(int j=1;j<=3;j+=2)
          {
            digitalWrite(x[i][j],1);
            for(int j=0;j<=3;j+=2)
             digitalWrite(x[i][j],0);
          }
        }
        else
        {
          for(int j=0;j<=3;j+=2)
          {
            digitalWrite(x[i][j],1);
             for(int j=1;j<=3;j+=2)
             digitalWrite(x[i][j],0);
          }
        }
      }
       delay(delay_time);
     }
     delay(5);
     }

     
   /*for(int w=1;w<=3;w++)
   {
     black();   
   for(int i=16;i<=19;i++)
     digitalWrite(i,1);
   digitalWrite(17,0);
   digitalWrite(18,0);
   for(int k=1;k<=2;k++)
   {
    for(int l=1;l<=2;l++)
    {
     digitalWrite(x[k][l],1);
     digitalWrite(x[k][l],1);
    }
   }
   delay(300);
   black(); 
   for(int k=0;k<=15;k++)
   digitalWrite(k,1);
   for(int q=1;q<=10;q++)
   {
   for(int j=0;j<=3;j++)
   {
    if(j%2==0)
    {
      for(int o=1;o<=2;o++)
      digitalWrite(x[j][o],0);
    }
    else
    {
       for(int o=0;o<=3;o++)
      digitalWrite(x[j][o],0);
    }
   }
   }
   
    delay(300);
   }*/

   
   
  
   
}
