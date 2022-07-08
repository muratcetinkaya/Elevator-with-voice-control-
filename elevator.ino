#include <Stepper.h>    
 #include <SoftwareSerial.h>
#include "NewPing.h"
#include "TMRpcm.h"
#include "SPI.h"
#include "SD.h"
#define SD_ChipSelectPin 13

#define TRIGGER_PIN 9
#define ECHO_PIN 2
#define MAX_DISTANCE 400  
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float duration, distance;
TMRpcm tmrpcm;

SoftwareSerial  BT(7, 8); // RX,TX
String state;
int trigger=9;
int echo=10;
unsigned long sure;
int IN1 = 3;           
int IN2 = 5;
int IN3 = 6;
int IN4 = 4;
int i;
int j;
int katbilgi=1;
int tamtur = 2048; 
Stepper step_motorum = Stepper(tamtur, IN2, IN4, IN1, IN3); // Kütüphane hazırlanıyor
 
void setup() {
BT.begin(9600);
Serial.begin(9600);
}
 
void loop() {

tmrpcm.speakerPin = 10;

  if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}

  
distance = sonar.ping_cm();

while(BT.available()){
delay(10);
char c=BT.read();
state +=c;
}
if(state.length()>0)
{
Serial.println(state);  

if (state == "kat 1" )

{
  if (katbilgi==1)
{
  for (i=0; i<3; i++){
  step_motorum.setSpeed(10);  // Hızı dakikada 10 devir olarak ayarlıyoruz
  step_motorum.step(-tamtur);  // Bir tam tur dönsün
  delay(60);    
   }
    state="";
    
   }
   if (katbilgi==3)
{
  for (i=0; i<3; i++){
  step_motorum.setSpeed(10);  // Hızı dakikada 10 devir olarak ayarlıyoruz
  step_motorum.step(tamtur);  // Bir tam tur dönsün
  delay(60);    
   }
    state="";
    
   }


if(katbilgi==2)
{
  Serial.println("zaten kat 2");
  delay(60);    
   
    state="";
    
   }

      katbilgi=2;
tmrpcm.setVolume(5);
tmrpcm.play("kat1.wav");
delay(3000);
tmrpcm.play("git.wav");
delay(3000);    
}
if (state == "kat zemin" )

{
  if(katbilgi==2)
{
  for (i=0; i<3; i++){
  step_motorum.setSpeed(10);  // Hızı dakikada 10 devir olarak ayarlıyoruz
  step_motorum.step(tamtur);  // Bir tam tur dönsün
  delay(60);    
   }
    state="";
    
   }
   
if (katbilgi==3)
{
  for (i=0; i<6; i++){
  step_motorum.setSpeed(10);  // Hızı dakikada 10 devir olarak ayarlıyoruz
  step_motorum.step(tamtur);  // Bir tam tur dönsün
  delay(60);    
   }
    state="";
    
   }

   katbilgi=1;

tmrpcm.setVolume(5);
tmrpcm.play("zemin.wav");
delay(3000);
tmrpcm.play("git.wav");
delay(3000);    

}

if (state == "kat 2" )

{
  if (katbilgi==1)
{
  for (i=0; i<6; i++){
  step_motorum.setSpeed(10);  // Hızı dakikada 10 devir olarak ayarlıyoruz
  step_motorum.step(-tamtur);  // Bir tam tur dönsün
  delay(60);    
   }
    state="";
    
   }
if (katbilgi==2)
{
  for (i=0; i<3; i++){
  step_motorum.setSpeed(10);  // Hızı dakikada 10 devir olarak ayarlıyoruz
  step_motorum.step(-tamtur);  // Bir tam tur dönsün
  delay(60);    
   }
    state="";
    
   }

if(katbilgi==3)
{
  Serial.println("zaten kat 3");
  delay(60);    
   
    state="";
    
   }
   
   katbilgi=3;
tmrpcm.setVolume(5);
tmrpcm.play("kat2.wav");
delay(3000);
tmrpcm.play("git.wav");
delay(3000);    


   
}

else
{
  Serial.println("hata");  
state="";
  }
}


else if(distance>1 && distance<=5){
  Serial.print(distance);
    Serial.println(" cm");
  if(katbilgi==3)
  {
    
  
  for (i=0; i<6; i++){
  step_motorum.setSpeed(10);  // Hızı dakikada 10 devir olarak ayarlıyoruz
  step_motorum.step(tamtur);  // Bir tam tur dönsün
  delay(60);    
   }
    state="";
  }
    if(katbilgi==2)
{
  for (i=0; i<3; i++){
  step_motorum.setSpeed(10);  // Hızı dakikada 10 devir olarak ayarlıyoruz
  step_motorum.step(tamtur);  // Bir tam tur dönsün
  delay(60);    
   }
    state="";

   }
    if(katbilgi==1)
{
  Serial.println("zaten kat 1");
  delay(60);    
   
    state="";
    
   }
  katbilgi=1;
  tmrpcm.setVolume(5);

  tmrpcm.play("zemin.wav");
delay(3000);
tmrpcm.play("git.wav");
delay(3000);    
  }





}
  // Biraz bekleyelim
