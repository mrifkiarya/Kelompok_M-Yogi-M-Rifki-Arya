int relay = 13;
void setup(){
  pinMode(relay,HIGH);
}
void loop(){
  digitalWrite(relay,HIGH);
  delay(1000);
  digitalWrite(relay,LOW);
  delay(1000);
}
