int led=11; 
int i; 
void setup(){ 
pinMode(led,OUTPUT);
} 
void loop(){ 
for (i=0; i<=255; i+=5){ 
analogWrite(led,i); 
delay(100);
}
for (i=255; i>=0; i-=5){ 
analogWrite(led,i); 
delay(100);
}
}
