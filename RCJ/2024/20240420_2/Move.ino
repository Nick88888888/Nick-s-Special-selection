void stop1(){
  analogWrite(2, 255);
  digitalWrite(3,1);
  digitalWrite(4,1);
  analogWrite(7, 255);
  digitalWrite(5,1);
  digitalWrite(6,1);
}
void back(int i){ 
  analogWrite(2, i);
  digitalWrite(3,1);
  digitalWrite(4,0);
  analogWrite(7, i);
  digitalWrite(5,1);
  digitalWrite(6,0);
}
void straight(int i){
  analogWrite(2,i);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i);
  digitalWrite(5,0);
  digitalWrite(6,1);
}
void left(int i){
  analogWrite(2,i);
  digitalWrite(3,0);
  digitalWrite(4,0);
  analogWrite(7,i);
  digitalWrite(5,0);
  digitalWrite(6,1);
}
void right(int i){
  analogWrite(2,i);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i);
  digitalWrite(5,0);
  digitalWrite(6,0);
}
void big_left(int i){
  analogWrite(2,i);
  digitalWrite(3,1);
  digitalWrite(4,0);
  analogWrite(7,i);
  digitalWrite(5,0);
  digitalWrite(6,1);
}
void big_right(int i){
  analogWrite(2,i);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i);
  digitalWrite(5,1);
  digitalWrite(6,0);
}
void turn_left(int i){
  analogWrite(2,i-50);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i-50);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(400);
  analogWrite(2,i);
  digitalWrite(3,1);
  digitalWrite(4,0);
  analogWrite(7,i);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(300);
  while(analogRead(59)>=500){
     analogWrite(2,i);
      digitalWrite(3,1);
      digitalWrite(4,0);
      analogWrite(7,i);
      digitalWrite(5,0);
      digitalWrite(6,1);
  }
  
}
void turn_right(int i){
  analogWrite(2,i-50);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i-50);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(400);
  analogWrite(2,i);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(400);
  while(analogRead(58)>=400){
      analogWrite(2,i);
      digitalWrite(3,0);
      digitalWrite(4,1);
      analogWrite(7,i);
      digitalWrite(5,1);
      digitalWrite(6,0);
  }
  
}
void return1(int i){
   analogWrite(2,i);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(2000);
  while(analogRead(57)>500){
      analogWrite(2,i);
      digitalWrite(3,0);
      digitalWrite(4,1);
      analogWrite(7,i);
      digitalWrite(5,1);
      digitalWrite(6,0);
  }
  analogWrite(2,i);
  digitalWrite(3,0);
  digitalWrite(4,1);
  analogWrite(7,i);
  digitalWrite(5,0);
  digitalWrite(6,0);
  delay(400);
  stop1();
}
void barrier(int i){
  big_left(i);
  delay(1500);
  stop1();
  delay(500);
  straight(120);
  delay(700);
  big_right(i);
  delay(1500);
  stop1();
  delay(500);
  straight(120);
  delay(1300);
  big_right(i);
  delay(1300);
  stop1();
  delay(500);
  do{
    straight(90);
  }
  while(analogRead(59)>=200);
  stop1();
}
