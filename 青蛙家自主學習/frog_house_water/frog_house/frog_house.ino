void setup() {
  pinMode(A0,INPUT_PULLUP);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
}
int count=1,now=0,past=0;
void loop() {
  if(count>2){
    count=1;
  }
  now = digitalRead(A0) ;
  if(now!=past && digitalRead(A0)==LOW)  
    count+=1;
  past = now;
  Serial.print("count=");
  Serial.println(count);
  Serial.println(analogRead(A2));
  delay(10);
  digitalWrite(9,LOW);
  digitalWrite(11,HIGH);
  if(count==2){
    while(analogRead(A2)>480){
      digitalWrite(2,1);
      digitalWrite(3,0);
      Serial.println(analogRead(A2));
    }
    while(analogRead(A2)<=610){
      digitalWrite(2,0);
      digitalWrite(3,0);
      analogWrite(10,250);
      Serial.println(analogRead(A2));
    } 
    analogWrite(10,0);
  }
}
