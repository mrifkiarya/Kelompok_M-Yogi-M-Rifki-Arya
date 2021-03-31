int led = A5; // set pin A5 untuk LED
void setup() {
  pinMode(led, OUTPUT); //men set pin led sebagai outputt
} 
void loop() { 
 digitalWrite(led, HIGH); //menuliskan led untuk menyala (HIGH)
delay(1000); // memberi delay selama 1 detik
digitalWrite(led, LOW); // menuliskan led untuk mati (LOW)
delay(1000); // memberi delay selama 1 detik
} 
