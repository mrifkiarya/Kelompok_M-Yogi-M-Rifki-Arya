#include <BlynkSimpleStream.h>

// Pin Assignments
int redPin=12,yellowPin=11,greenPin=13,bluePin=10;

//Ganti Auth Token sesuai kode yang muncul pada aplikasi Blynk pada
//smartphone Anda. Auth Token di bawah ini hanyalah contoh. 
char auth[] = "yogxilhKMiiLzcSjihysND5roWPoELTw";

void setup()
{
//Atur pin sebagai output 
pinMode(redPin,OUTPUT); 
pinMode(yellowPin,OUTPUT); 
pinMode(greenPin,OUTPUT);
pinMode(bluePin,OUTPUT);

// Blynk berkomunikasi melalui komunikasi serial 
Serial.begin(9600);
Blynk.begin(auth, Serial);
}

void loop()
{
//mengaktifkan fungsi Blynk 
Blynk.run();
}
