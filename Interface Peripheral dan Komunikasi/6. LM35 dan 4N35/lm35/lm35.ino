float tempC; // untuk menyimpan variable temperatur derajat celcius
int reading; // variable pembaca
int tempPin = A0; // pin lm35 ada di A0

void setup() {
  Serial.begin(9600); //untuk menyalakan serial monitor
  analogReference(INTERNAL); //memiliki nilai sebesar 5 volts atau 3.3 volts
  pinMode(tempPin,INPUT); // setpin A0/temPin sebagai input
} 
void loop() { 
  reading = analogRead(tempPin); // menyimpan hasil dari analogread ke reading
  tempC = reading / 9.31;   // menyimpan hasil dari pembagian reading / 9.31
  Serial.println(tempC); // untuk menampilkan hasil dari pembagian tersebut ke serial monitor
} 
