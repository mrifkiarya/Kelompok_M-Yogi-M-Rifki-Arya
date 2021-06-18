#include<EEPROM.h>

byte data;
int led=9;
int Lm=A1;
void setup(){
  pinMode(led, OUTPUT);
  if(tombol==LOW){
    tekan=tekan+1;
    }
}

void loop(){
  data= analogRead(Lm)/4;
  
    if(digitalRead(tombol)==LOW){
    tekan=tekan+1;
    }
    delay(1000);
    if(tekan==1){
      EEPROM.write(0,data);
       }
    else if(tekan==2){
      EEPROM.read(0);
      hasil=data;
    }
    else if(tekan==3){
      EEPROM.write(0,0);
      digitalWrite(buzzer,HIGH);
      digitalWrite(led2,HIGH);
      delay(1000);
      digitalWrite(buzzer,LOW);
      digitalWrite(led2,LOW);
      delay(1000);
      digitalWrite(buzzer,HIGH);
      digitalWrite(led2,HIGH);
      delay(1000);
      digitalWrite(buzzer,LOW);
      digitalWrite(led2,LOW);
      delay(1000);
      digitalWrite(buzzer,HIGH);
      digitalWrite(led2,HIGH);
      delay(1000);
      digitalWrite(buzzer,LOW);
      digitalWrite(led2,LOW);
      delay(1000);
      lcd.clear();
    }
}
