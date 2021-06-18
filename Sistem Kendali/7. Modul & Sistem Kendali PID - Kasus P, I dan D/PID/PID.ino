#include <EEPROM.h>

int motorKanan1=9;
int motorKanan2=10;
int motorKiri1=6;
int motorKiri2=5;
int EnA= 11;
int EnB= 3;

int tekan2=0;
int tekan=0;

int kananAtas=13;
int kananBawah=2;
int kiriAtas=12;
int kiriBawah=4;

int rate = 0;
int moveControl = 0;
int kecepatanMotorKanan = 0;
int kecepatanMotorKiri = 0;
int kecepatanSetPoint = 150;

int state = 0;
int setting=0;

int errSum;
unsigned long int SampleTime = 1000;
unsigned long int now;
unsigned long int lastTime;
unsigned long int timeChange;


int sensor[8];
int NilaiMaxSensor[8];
int NilaiMinSensor[8];
int NilaiTengahSensor[8];

int Kp=20;
int Ki=10;
int Kd=5;

int led2 = 7;
int led1 = 8;

int Error=0;
int LastError=0;

int Error2=0;
int LastError2=0;

int tom=2;

int peka[8]={500,500,500,500,500,500,500,500};

void setup(){
  Serial.begin(9600);
  pinMode(motorKanan1,OUTPUT);
  pinMode(motorKanan2,OUTPUT);
  pinMode(motorKiri1,OUTPUT);
  pinMode(motorKiri2,OUTPUT);
  pinMode(EnA,OUTPUT);
  pinMode(EnB,OUTPUT);

  pinMode (A0,INPUT);
  pinMode (A1,INPUT);
  pinMode (A2,INPUT);
  pinMode (A3,INPUT);
  pinMode (A4,INPUT);
  pinMode (A5,INPUT);
  pinMode (A6,INPUT);
  pinMode (A7,INPUT);

  pinMode (tom,INPUT);

  for (int a=0;a<8;a++){
    peka[a]=EEPROM.read(a)*4;
  }
  EEPROM.write(8,Kp);
  EEPROM.write(9,Kd);

  Kp=EEPROM.read(8);
  Kd=EEPROM.read(9);

  for(int b=0;b<8;b++){
    Serial.print("Peka ");
    Serial.print(b);
    Serial.print(" = ");
    Serial.println(peka[b]);
  }
    Serial.print("Kp     = ");
    Serial.println(Kp);
    Serial.print("Kd     = ");
    Serial.println(Kd);
    Serial.print("Ki     = ");
    Serial.println(Ki);
  
}

void loop(){
  if(digitalRead(kiriBawah)==HIGH){
    if(setting==0){
      state=1;
    }
    else if(setting==1){
      state=3;
    }
  }

  if(digitalRead(kiriAtas)==HIGH){
    if(setting==0){
      state=2;
      setting=1;
    }
    else if(setting==1){
      state=4;
    }
  }
  
  if(digitalRead(kananBawah)==HIGH){
    if(setting==1){
      state=5;
    }
  }

  if(digitalRead(kananAtas)==HIGH){
    if(setting==1){
      state=6;
    }
  }

  if(digitalRead(kananAtas)==HIGH){
    if (digitalRead(kiriAtas)==HIGH){
      if(setting==1){
        state=7;
      }
    }
  }
   if(digitalRead(kananBawah)==HIGH){
    if (digitalRead(kiriBawah)==HIGH){
      if(setting==1){
        state=8;
      }
    }
  }

  now = millis();
  timeChange=now-lastTime;

  if(state==1){
    tekan=tekan+1;
    Serial.println("Kalibrasi...");
    
  } 
  else if(state==2){
    tekan=tekan+1;
    for (int a=0;a<8;a++){
      EEPROM.write(a, peka[a]/4);
    }
  }
  else if(state==3){
    tekan=tekan+1;
    digitalWrite(led1,HIGH);
    delay(500);
    digitalWrite(led1,LOW);
    delay(500);
    Kp=Kp-1;
    EEPROM.write(8,Kp);
    state=1;

  }
  else if(state==4){
    tekan=tekan+1;
    digitalWrite(led1,HIGH);
    delay(1000);
    digitalWrite(led1,LOW);
    delay(1000);
    Kp=Kp+1;
    EEPROM.write(8,Kp);
     state=1;

  }
  else if(state==5){
    tekan=tekan+1;
    digitalWrite(led1,HIGH);
    delay(1000);
    digitalWrite(led1,LOW);
    delay(1000);
    Kd=Kd-1;
    EEPROM.write(9,Kd);
     state=1;

  }
  else if(state==6){
    tekan=tekan+1;
    digitalWrite(led1,HIGH);
    delay(1000);
    digitalWrite(led1,LOW);
    delay(1000);
    Kd=Kd+1;
    EEPROM.write(9,Kd);
     state=1;

  }
  else if(state==7){
    tekan=tekan+1;
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    delay(500);
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    delay(500);
    Ki=Ki+1;
    EEPROM.write(11,Ki);
     state=1;
  }
  else if(state==8){
    tekan=tekan+1;
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    delay(500);
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    delay(500);
    Ki=Ki-1;
    EEPROM.write(12,Ki);
     state=1;
  } Serial.println("================");
    Serial.print("Kp     = ");
    Serial.println(Kp);
    Serial.print("Kd     = ");
    Serial.println(Kd);
    Serial.print("Ki     = ");
    Serial.println(Kd);
    delay(1000);

      
      String sensor1 = String(digitalRead(A0));
      String sensor2 = String(digitalRead(A1));
      String sensor3 = String(digitalRead(A2));
      String sensor4 = String(digitalRead(A3));
      String sensor5 = String(digitalRead(A4));
      String sensor6 = String(digitalRead(A5));
      String sensor7 = String(digitalRead(12));
      String sensor8 = String(digitalRead(4));
      
    if(tekan==1){
      Serial.print(tekan);
      for(int i=0; i<8; i++){
        if(i==0){
        NilaiMaxSensor[i]=1023;
        NilaiMinSensor[i]=0;
        }
      }
      sensor[0]=atoi(sensor1.c_str());
      sensor[1]=atoi(sensor2.c_str());
      sensor[2]=atoi(sensor3.c_str());
      sensor[3]=atoi(sensor4.c_str());
      sensor[4]=atoi(sensor5.c_str());
      sensor[5]=atoi(sensor6.c_str());
      sensor[6]=atoi(sensor7.c_str());
      sensor[7]=atoi(sensor8.c_str());
    
      for(int i=0; i<8; i++){
        if(sensor[i] > NilaiMinSensor[i]){
          NilaiMinSensor[i] =sensor[i];
        }
        if(sensor[i] < NilaiMaxSensor[i]){
          NilaiMaxSensor[i] =sensor[i];
        }
        NilaiTengahSensor[i]= NilaiMinSensor[i]+NilaiMaxSensor[i]/2;
      
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        delay(200);
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        delay(200);
      }
      Serial.println("Kalibrasi selesai");
      tekan=2;
      
    }
    
      else if(tekan>=3){
      
          String kondisi = sensor1+sensor2+sensor3+sensor4+sensor5+sensor6+sensor7+sensor8;
          
          if(kondisi == "10000000"){
            satu();
          }
          else if(kondisi == "11000000"){
            dua();
          }
          else if(kondisi == "01000000"){
            tiga();
          }
          else if(kondisi == "01100000"){
            empat();
          }
          else if(kondisi == "00100000"){
            lima();
          }
          else if(kondisi == "00110000"){
            enam();
          }
          else if(kondisi == "00010000"){
            tujuh();
          }
          else if(kondisi == "00011000"){
            delapan();
          }
          else if(kondisi == "00001000"){
            sembilan();
          }
          else if(kondisi == "00001100"){
            sepuluh();
          }
          else if(kondisi == "00000100"){
            sebelas();
          }
          else if(kondisi == "00000110"){
            duabelas();
          }
          else if(kondisi == "00000010"){
            tigabelas();
          }
          else if(kondisi == "00000011"){
            empatbelas();
          }
          else if(kondisi == "00000001"){
            limabelas();
          }
          else if(kondisi == "00000000"){
            enambelas();
          }
          delay(300);
      }


}
void satu(){
  LastError = Error;
  Error = -7;
  if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void dua(){
  LastError = Error;
  Error = -6;
   if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void tiga(){
  LastError = Error;
  Error = -5;
    if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void empat(){
  LastError = Error;
  Error = -4;
   if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void lima(){
  LastError = Error;
  Error = -3;
    if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void enam(){
  LastError = Error;
  Error = -2;
   if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void tujuh(){
  LastError = Error;
  Error = -1;
  if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void delapan(){
  LastError = Error;
  Error = 0;
  if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void sembilan(){
  LastError = Error;
  Error = 1;
  if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void sepuluh(){
  LastError = Error;
  Error = 2;
 if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void sebelas(){
  LastError = Error;
  Error = 3;
 if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void duabelas(){
  LastError = Error;
  Error = 4;
 if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void tigabelas(){
  LastError = Error;
  Error = 5;
 if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void empatbelas(){
  LastError = Error;
  Error = 6;
  if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void limabelas(){
  LastError = Error;
  Error = 7;
   if(LastError<0){
    LastError2=LastError*-1;
  }
  else if(LastError>=0){
    LastError2=LastError;
  }
  if(Error<0){
    (Error2=Error*-1);
  }
  else if(Error>=0){
    Error2=Error;
  }
  
  if (Error2>=LastError2){
    rate = (Error2-LastError2);
  }
  else if (Error2<LastError2){
    rate = (LastError2-Error2);
  }
   if (timeChange>SampleTime){
    
    errSum = (Error2*timeChange)+errSum;
    moveControl = (Kp*Error2)+(Ki*errSum)+(Kd*rate);
    kecepatanMotorKanan=kecepatanSetPoint-moveControl;
    kecepatanMotorKiri=kecepatanSetPoint+moveControl;
    digitalWrite(motorKanan1,HIGH);
    digitalWrite(motorKanan2,LOW);
    digitalWrite(motorKiri1,HIGH);
    digitalWrite(motorKiri2,LOW);
    analogWrite(EnA,kecepatanMotorKanan);
    analogWrite(EnB,kecepatanMotorKiri);
  }
  Serial.print("Error = ");
  Serial.println(Error2);
}
void enambelas(){
  digitalWrite(motorKanan1,LOW);
  digitalWrite(motorKanan2,LOW);
  digitalWrite(motorKiri1,LOW);
  digitalWrite(motorKiri2,LOW);
  analogWrite(EnA,0);
  analogWrite(EnB,0);
  Serial.println("Keluar Lintasan");
}
