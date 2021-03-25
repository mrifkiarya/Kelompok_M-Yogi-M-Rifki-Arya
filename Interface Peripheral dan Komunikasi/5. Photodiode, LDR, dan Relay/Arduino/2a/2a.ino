int buzz = 11;
int senRead = 0;
int limit = 850;
int buz;
int pd;

void setup(){
  pinMode(pd,OUTPUT);
  pinMode(buzz,OUTPUT);
  digitalWrite(buz,LOW);
  Serial.begin(9600);
}
void loop(){
  int val=analogRead(senRead);
  Serial.println(val);
  if(val <= limit){
    digitalWrite(buzz,HIGH);
    delay(20);
  }else if(val > limit){
    digitalWrite(buzz,LOW);
    delay(20);
  }
}
