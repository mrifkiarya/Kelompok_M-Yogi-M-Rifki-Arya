#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

float  Val,Val1,kecepatan,jarak  ;                                                  // Inisialilasasi Input
float m_kecepatan, m_jarak;                                                         // Inisialilasasi Derajat Keanggotaan 
float sangat_lambat, lambat, c_sedang, cepat, sangat_cepat;                         // Inisialilasasi Membership Function kecepatan
float sangat_dekat, dekat, j_sedang, jauh, sangat_jauh;                             // Inisialilasasi Membership Function jarak
float sangat_lambat_1, lambat_1, c_sedang_1, cepat_1, sangat_cepat_1;               // Inisialilasasi Membership yang aktif
float sangat_dekat_1, dekat_1, j_sedang_1, jauh_1, sangat_jauh_1;                   // Inisialilasasi Membership yang aktif
float VLmax=0, Lmax=0, Mmax=0, Hmax=0, VHmax=0;                                     // Inisialilasasi Defuzzification
float fsmax=0;                                                                      // Inisialilasasi nilai maksimum
float num, den, output, pwm ;                                                       // Inisialilasasi defuzzification


// ------------------------------------------------- Fuzzification ------------------------------------------------------------

float mf_kecepatan(float a, float b, float c)              // Mencari Derajat keanggotaan membership function segitiga kecepatan
   {
     if (kecepatan>=a&&kecepatan<b) {m_kecepatan=(kecepatan-a)/(b-a); }
     if (kecepatan>=b&&kecepatan<c) {m_kecepatan=(c-kecepatan)/(c-b);}
   }

float mf_jarak(float a1, float b1, float c1)          // Mencari Derajat keanggotaan membership function segitiga Jumlah jarak
   {
     if (jarak>=a1&&jarak<b1) {m_jarak=(jarak-a1)/(b1-a1);}
     if (jarak>=b1&&jarak<c1) {m_jarak=(c1-jarak)/(c1-b1);}
   }
                                                                                                                                            
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  
}

void loop() {

   Val = analogRead(A0);    // Input ADC0
   kecepatan = ((Val/1023)*18)+18;
   Val1 = analogRead(A1);   // Input ADC1
   jarak = (Val1/1023)*40;

// ----------------------------------------- Membership Function ---------------------------------------------
 
 if(kecepatan>=15&&kecepatan<=20)
    {mf_kecepatan(0,15,20);   sangat_lambat =m_kecepatan;  c_sedang=0; cepat=0; sangat_cepat=0; }              //  sangat_lambat
 if(kecepatan>=15&&kecepatan<=25)
    {mf_kecepatan(15,20,25);  lambat=m_kecepatan;  cepat=0; sangat_cepat=0; }                            //  lambat
 if(kecepatan>=20&&kecepatan<=30)
    {mf_kecepatan(20,25,30);  sangat_lambat =0;  c_sedang=m_kecepatan;  sangat_cepat=0;  }                     //  Sedang
 if(kecepatan>=25&&kecepatan<=35)
    {mf_kecepatan(25,20,35);  sangat_lambat =0;  lambat=0; cepat=m_kecepatan;  }                                //  cepat
 if(kecepatan>=30&&kecepatan<=35)
    {mf_kecepatan(30,35,0);   sangat_lambat =0;  lambat=0; c_sedang=0; sangat_cepat=m_kecepatan;  }             //  sangat cepat
                                                                                                                                              
 if(jarak>=0&&jarak<=15)
    {mf_jarak(0,0,15);    sangat_dekat=m_jarak;   j_sedang=0; jauh=0; sangat_jauh=0;  }  // Sangat dekat
 if(jarak>=0&&jarak<=25)
    {mf_jarak(0,15,25);   dekat=m_jarak;  jauh=0; sangat_jauh=0; }                       // dekat
 if(jarak>=15&&jarak<=35)
    {mf_jarak(15,25,35);  sangat_dekat=0;   j_sedang=m_jarak;  sangat_jauh=0; }            // sedang
 if(jarak>=25&&jarak<=40)
    {mf_jarak(15,35,40);  sangat_dekat=0;  dekat=0;  jauh=m_jarak; }                    // jauh
 if(jarak>=35&&jarak<=40)
    {mf_jarak(35,40,0);   sangat_dekat=0;  dekat=0; j_sedang=0; sangat_jauh=m_jarak; }  // sangat jauh

//  ----------------------------------------- mechanism Inferens  ----------------------------------------

  if (sangat_lambat >0)        {sangat_lambat_1 = 1;}           else {sangat_lambat_1 = 0;}
  if (lambat >0)         {lambat_1 = 1;}            else {lambat_1  = 0;}
  if (c_sedang >0)       {c_sedang_1 = 1;}          else {c_sedang_1 = 0;}
  if (cepat >0)          {cepat_1 = 1;}             else {cepat_1= 0;}
  if (sangat_cepat >0)   {sangat_cepat_1 = 1;}      else {sangat_cepat_1= 0;}

  if (sangat_dekat >0)  {sangat_dekat_1 = 1;}     else {sangat_dekat_1 = 0;}
  if (dekat >0)         {dekat_1 = 1;}            else {dekat_1 = 0;}
  if (j_sedang >0)      {j_sedang_1 = 1;}         else {j_sedang_1 = 0;}
  if (jauh >0)          {jauh_1 = 1;}             else {jauh_1 = 0;}
  if (sangat_jauh>0)    {sangat_jauh_1 = 1;}      else {sangat_jauh_1 = 0;}

  float VL[7]={0,1,2,3,4,5,6};                                                                                      // Very Low
  {
  if (sangat_lambat_1==1 && sangat_dekat_1==1)      {VL[1]=min(sangat_lambat,sangat_dekat );}    else {VL[1]=0;}      
  if (sangat_lambat_1==1 && dekat_1==1)             {VL[2]=min(sangat_lambat,dekat);}            else {VL[2]=0;}   
  if (sangat_lambat_1==1 && j_sedang_1==1)          {VL[3]=min(sangat_lambat,j_sedang);}         else {VL[3]=0;}  
  if (sangat_lambat_1==1 && jauh_1==1)              {VL[4]=min(sangat_lambat,jauh);}             else {VL[4]=0;} 
  if (lambat_1==1 && sangat_dekat_1==1)             {VL[5]=min(lambat,sangat_dekat );}           else {VL[5]=0;}   
  if (lambat_1==1 && dekat_1==1)                    {VL[6]=min(lambat,dekat);}                   else {VL[6]=0;}  
  }
  
  float L[6]={0,1,2,3,4,5};                                                                                        // Low
  {
  if (sangat_lambat_1==1 && sangat_jauh_1==1)       {L[1]=min(sangat_lambat,sangat_jauh);}       else {L[1]=0;}  
  if (lambat_1==1 && j_sedang_1==1)                 {L[2]=min(lambat,j_sedang);}                 else {L[2]=0;}  
  if (lambat_1==1 && jauh_1==1)                     {L[3]=min(lambat,jauh);}                     else {L[3]=0;}  
  if (lambat_1==1 && sangat_jauh_1==1)              {L[4]=min(lambat,sangat_jauh);}              else {L[4]=0;}   
  if (c_sedang_1==1 && sangat_dekat_1==1)           {L[5]=min(c_sedang,sangat_dekat );}          else {L[5]=0;}   
  }
  
  float M[4]={0,1,2,3};                                                                                            // Medium
  {
  if (c_sedang_1==1 && dekat_1==1)                 {M[1]=min(c_sedang,dekat);}                  else {M[1]=0;}  
  if (c_sedang_1==1 && j_sedang_1==1)              {M[2]=min(c_sedang,j_sedang);}               else {M[2]=0;}  
  if (c_sedang_1==1 && jauh_1==1)                  {M[3]=min(c_sedang,jauh);}                   else {M[3]=0;}  
  }
                                                                                                                                                   
  float H[6]={0,1,2,3,4,5};                                                                                         // High
  {
  if (c_sedang_1==1 && sangat_jauh_1==1)          {H[1]=min(c_sedang,sangat_jauh);}             else {H[1]=0;} 
  if (cepat_1==1 && sangat_dekat_1==1)            {H[2]=min(cepat,sangat_dekat );}              else {H[2]=0;}   
  if (cepat_1==1 && dekat_1==1)                   {H[3]=min(cepat,dekat);}                      else {H[3]=0;}  
  if (cepat_1==1 && j_sedang_1==1)                {H[4]=min(cepat,j_sedang);}                   else {H[4]=0;}
  if (sangat_cepat_1==1 && sangat_dekat_1==1)     {H[5]=min(sangat_cepat,sangat_dekat );}       else {H[5]=0;} 
  }
 
  float VH[7]={0,1,2,3,4,5,6};                                                                                        // Very High
  {
  if (cepat_1==1 && jauh_1==1)                   {VH[1]=min(cepat,jauh);}                     else {VH[1]=0;}  
  if (cepat_1==1 && sangat_jauh_1==1)            {VH[2]=min(cepat,sangat_jauh);}              else {VH[2]=0;} 
  if (sangat_cepat_1==1 && dekat_1==1)           {VH[3]=min(sangat_cepat,dekat);}             else {VH[3]=0;}  
  if (sangat_cepat_1==1 && j_sedang_1==1)        {VH[4]=min(sangat_cepat,j_sedang);}          else {VH[4]=0;}  
  if (sangat_cepat_1==1 && jauh_1==1)            {VH[5]=min(sangat_cepat,jauh);}              else {VH[5]=0;}  
  if (sangat_cepat_1==1 && sangat_jauh_1==1)     {VH[6]=min(sangat_cepat,sangat_jauh);}       else {VH[6]=0;} 
  }
                                                                                                                                              
  VLmax=VL[0];  int index1=0;  for (int a=1; a<=6; a++)  {   if(VLmax<=VL[a])    { VLmax=VL[a];     index1=a;}  }
  Lmax=L[0];    int index2=0;  for (int b=1; b<=5; b++)  {   if(Lmax<=L[b])      { Lmax=L[b];       index2=b;}  }
  Mmax=M[0];    int index3=0;  for (int c=1; c<=3; c++)  {   if(Mmax<=M[c])      { Mmax=M[c];       index3=c;}  }
  Hmax=H[0];    int index4=0;  for (int d=1; d<=5; d++)  {   if(Hmax<=H[d])      { Hmax=H[d];       index4=d;}  }
  VHmax=VH[0];  int index5=0;  for (int e=1; e<=6; e++)  {   if(VHmax<=VH[e])    { VHmax=VH[e];     index5=e;}  }
  
// --------------------------------------------------------------------------- End Interface Mechanism ----------------------------------------------------------------

// --------------------------------------------------------------------------- Defuzzyfication  -----------------------------------------------------------------------//

float num = (VLmax*20) + (Lmax*40) + (Mmax*60) + (Hmax*80) + (VHmax*100);
float den =  VLmax+ Lmax + Mmax + Hmax+ VHmax;
float output = num/den;
  
  // Untuk LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cepat: ");
  lcd.setCursor(6,0);
  lcd.print(int(kecepatan));
  lcd.setCursor(0,1);
  lcd.print("Jarak: ");
  lcd.setCursor(6,1);
  lcd.print(int(jarak));
  lcd.setCursor(9,1);
  lcd.print("Out: ");
  lcd.setCursor(13,1);
  lcd.print(int(output));
  delay(100);

}
