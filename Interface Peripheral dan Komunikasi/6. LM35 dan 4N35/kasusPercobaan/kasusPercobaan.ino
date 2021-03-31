#include<EEPROM.h>
#include <LiquidCrystal_SR_LCD3.h> 
const int PIN_LCD_STROBE = 2; 
const int PIN_LCD_DATA = 3; 
const int PIN_LCD_CLOCK = 4;
LiquidCrystal_SR_LCD3 lcd(PIN_LCD_DATA,
PIN_LCD_CLOCK,
PIN_LCD_STROBE);

float tempC; 
int reading; 
int tempPin = A0;
int tom=9; 
int tekan=0;
int buz=11;
int led=A5;

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  analogReference(INTERNAL); 
  pinMode(tempPin,INPUT);
  pinMode(tom,INPUT);
  pinMode(led,OUTPUT);
  pinMode(buz,OUTPUT);
} 
void loop() { 

  if(digitalRead(tom)==LOW){
    tekan=tekan+1;
  }
  satu:
  if(tekan==1){
    reading = analogRead(tempPin); 
    tempC = reading / 9.31; 
    EEPROM.write(0,tempC);
    Serial.println("1. merekam data");
    lcd.print("merekam data    ");
    tekan=1;
  }
  else if(tekan==2){
    Serial.print("2. data = ");
    Serial.println(EEPROM.read(0));
    lcd.clear();
    lcd.print(EEPROM.read(0));
    tekan=2;
  }
  else if(tekan==3){
    EEPROM.write(0,0);
    lcd.clear();
    Serial.println("3. menghapus data");
    digitalWrite(buz,HIGH);
    delay(500);
    tekan=3;
  }
  else if(tekan==4){
    lcd.clear();
    digitalWrite(buz,LOW);
    Serial.println("4. blinking LED");
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
    tekan=4;
  }
  else if(tekan==5){
    tekan=1;
  }
  delay(500);
} 
