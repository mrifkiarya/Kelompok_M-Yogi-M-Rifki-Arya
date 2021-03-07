#include <LiquidCrystal_SR_LCD3.h> 
const int PIN_LCD_STROBE = 2; 
const int PIN_LCD_DATA = 3; 
const int PIN_LCD_CLOCK = 4; 
LiquidCrystal_SR_LCD3 lcd(PIN_LCD_DATA, 
PIN_LCD_CLOCK,
PIN_LCD_STROBE);

int led=10;
int led1=9;
int led2=8;

int i1=7;

void setup()
{
pinMode(led,OUTPUT);
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);

pinMode(i1,INPUT);

lcd.begin(16,2);
Serial.begin(9600);
lcd.setCursor(0,0);
lcd.print("HELLO BROOO!!!");
delay(1000);
lcd.clear();
}
void loop()
{
digitalWrite(led,HIGH);
digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);

if (Serial.available()) {
  
   while(Serial.available()>0){
   char ch=Serial.read();
 
   Serial.write(ch);
   lcd.write(ch);
  }
}
 if(digitalRead(i1)==LOW){
  for (int positionCounter = 0; positionCounter < 15; positionCounter++){
   lcd.scrollDisplayLeft();
   delay(150); 
 }
 }
}
