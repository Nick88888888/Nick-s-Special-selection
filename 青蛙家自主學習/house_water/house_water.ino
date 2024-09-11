void setup() {
 pinMode(4,1);
 pinMode(5,1);
 pinMode(6,1);
 pinMode(7,1);
 pinMode(A0,INPUT_PULLUP);
Serial.begin(115200);
    
}
void play(){
   digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
  delay(20000);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
  delay(20000);
   digitalWrite(4,LOW);
      digitalWrite(5,LOW);
}
int count=1,past,now;
void loop() {
  if(count>2){
    count=1;
  }
  now = digitalRead(A0) ;
  if(now!=past && digitalRead(A0)==LOW)  
    count+=1;
  past = now;
  if(count==2){
    play();
    count=1;
  }
  Serial.println(count);

         
}
