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
int i2=6;

void setup()
{
pinMode(led,OUTPUT);
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);

pinMode(i1,INPUT);
pinMode(i2,INPUT);

lcd.begin(16,2);
lcd.print("Running Text!!!");
}
void loop()
{
digitalWrite(led,HIGH);
digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);

if(digitalRead(i1)==LOW){
 for (int positionCounter = 0; positionCounter < 15; positionCounter++){
   lcd.scrollDisplayLeft();
   delay(150); 
  }
 }

 else if(digitalRead(i2)==LOW){
  for (int positionCounter = 0; positionCounter < 15; positionCounter++){
   lcd.scrollDisplayRight();
   delay(150); 
  }
 }
 
  else{
  }
}
