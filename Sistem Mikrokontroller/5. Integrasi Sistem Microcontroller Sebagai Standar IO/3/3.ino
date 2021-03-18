int led1=9;
int led2=11;
int led3=10;
int i; 
void setup(){
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
}
void loop(){
for (i=0; i<=255; i+=5){ 
analogWrite(led1,i);
analogWrite(led2,i);
analogWrite(led3,i); 
}
}
