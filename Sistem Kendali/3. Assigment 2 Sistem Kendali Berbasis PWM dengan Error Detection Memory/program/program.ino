int p=10;
int p1=9;
int p2=6;
int p3=5;

int led2=8;
int led3=7;
int led1=13;

int adc_sensor[8],x,sensorbit,t,a_size;
char sendat[8];

void setup() {
  Serial.begin(9600);
pinMode (p,OUTPUT);
pinMode (p1,OUTPUT);
pinMode (p2,OUTPUT);
pinMode (p3,OUTPUT);

pinMode (led2,OUTPUT);
pinMode (led3,OUTPUT);
pinMode (led1,OUTPUT);

pinMode (A0,INPUT);
pinMode (A1,INPUT);
pinMode (A2,INPUT);
pinMode (A3,INPUT);
pinMode (A4,INPUT);
pinMode (A5,INPUT);
pinMode (A6,INPUT);
pinMode (A7,INPUT);
}

void loop() {

  String relay1 = String(digitalRead(A0));
  String relay2 = String(digitalRead(A1));
  String relay3 = String(digitalRead(A2));
  String relay4 = String(digitalRead(A3));
  String relay5 = String(digitalRead(A4));
  String relay6 = String(digitalRead(A5));
  String relay7 = String(digitalRead(A6));
  String relay8 = String(digitalRead(A7));
  
  String  simpan= relay1+relay2+relay3+relay4+relay5+relay6+relay7+relay8;
 
  
  if (simpan == "10000000"){
      analogWrite(p,123); // belok kiri
      Serial.println("-6,motor kiri 50% motor kanan 0%.");
  }
  else if (simpan=="11000000"){
      analogWrite(p,123); // belok kiri
      analogWrite(p3,25); //5%
      Serial.println("-5,motor kiri 50% motor kanan 5%.");
  }
  else if (simpan=="01000000"){
      analogWrite(p,123); // belok kiri
      analogWrite(p3,40); //10%
      Serial.println("-4,motor kiri 50% motor kanan 10%.");
  }
   else if (simpan=="01100000"){
      analogWrite(p,123); // belok kiri
      analogWrite(p3,50); //15%
      Serial.println("-3,motor kiri 50% motor kanan 15%.");
  }
  else if (simpan=="00100000"){
      analogWrite(p,123); // belok kiri
      analogWrite(p3,56); //20%
      Serial.println("-2,motor kiri 50% motor kanan 20%.");
  }
  else if (simpan=="00110000"){
      analogWrite(p,123); // belok kiri
      analogWrite(p3,62); //25%
      Serial.println("-1,motor kiri 50% motor kanan 25%.");
  }
  else if (simpan=="00010000"){
      analogWrite(p,123); //50%
      analogWrite(p3,75); // 30%
      Serial.println("0,motor kiri 50% motor kanan 30%.");
  }
   else if (simpan=="00011000"){
      analogWrite(p,150); //60%
      analogWrite(p3,150); // 60%
      Serial.println("0,motor kiri 50% motor kanan 60%.");
  }
  else if (simpan=="00001000"){
      analogWrite(p,75); // belok kiri
      analogWrite(p3,123); // kanan
      Serial.println("0,motor kiri 30% motor kanan 50%.");
  }
  else if (simpan=="00001100"){
      analogWrite(p,62); // 25%
      analogWrite(p3,123); //belok kanan
      Serial.println("1,motor kiri 25% motor kanan 50%.");
  }
  else if (simpan=="00000100"){
      analogWrite(p,56); // 20%
      analogWrite(p3,123); //belok kanan
      Serial.println("2,motor kiri 20% motor kanan 50%.");
  }
  else if (simpan=="00000110"){
      analogWrite(p,50); // 15%
      analogWrite(p3,123); //belok kanan
      Serial.println("3,motor kiri 15% motor kanan 50%.");
  }
  else if (simpan=="00000010"){
      analogWrite(p,40); // 10%
      analogWrite(p3,123); //belok kanan
      Serial.println("4,motor kiri 10% motor kanan 50%.");
  }
  else if (simpan=="00000011"){
      analogWrite(p,25); // 5%
      analogWrite(p3,123); //belok kanan
      Serial.println("5,motor kiri 5% motor kanan 50%.");
  }
  else if (simpan=="00000001"){
      analogWrite(p3,123); //belok kanan
      Serial.println("6,motor kiri 0% motor kanan 50%.");
  }
  else{
  digitalWrite(p,LOW);
  digitalWrite(p1,LOW);
  digitalWrite(p2,LOW);
  digitalWrite(p3,LOW);
  }
}
