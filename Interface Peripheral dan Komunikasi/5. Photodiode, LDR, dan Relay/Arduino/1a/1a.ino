int lightPin = A0;
int ledPin = 6;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}
void loop(){
  Serial.println(analogRead(lightPin));
  analogWrite(ledPin, analogRead(lightPin)/4);
  delay(10);
}
