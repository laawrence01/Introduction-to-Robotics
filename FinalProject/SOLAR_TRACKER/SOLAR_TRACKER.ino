#include "LedControl.h"
LedControl lc = LedControl(7, 6, 5, 1); //DIN, CLK, LOAD, No. DRIVER
const uint64_t sadFace[] = {
  0x423c0000e7a5a5e7,
  0x423c0000e7a5e700,
  0x423c0000e7e70000,
  0x423c0000e7000000,
  0x423c0000e7e70000,
  0x423c0000e7a5e700,
  0x423c0000e7a5a5e7,
  0x423c0001e7a5a5e7,
  0x423c0301e7a5a5e7,
  0x423f0301e7a5a5e7,
  0x433f0100e7a5a5e7,
  0x433d0000e7a5a5e7,
  0x433c0000e7a5a5e7
};
const int sadFace_LEN = sizeof(sadFace)/8;

const uint64_t happyFace[] = {
 0x003c4200e7a5a5e7,
  0x003c4200e7a5e700,
  0x003c4200e7e70000,
  0x003c4200e7000000,
  0x003c4200e7e70000,
  0x003c4200e7a5e700,
  0x003c4200e7a5a5e7
};
const int happyFace_LEN = sizeof(happyFace)/8;

unsigned long  animationTime;
unsigned long  prevAnimationTime = 0;
int animationIndex ;
int animationInterval = 100;
int maxLength = 8;
int constant = 100; // used for precision when comparing
void animation(uint64_t image) {
  for (int i = 0; i < maxLength; i++) {
    byte r = (image >> i * maxLength) & 0xFF;
    for (int j = 0; j < maxLength; j++) {
      lc.setLed(0, i, j, bitRead(r, j));
    }
  }
}
#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 0;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 20;

//declaring light sensors
int ldrtopl = 0; //top left sensor 
int ldrtopr = 1; //top right sensor 
int ldrbotl = 2; // bottom left sensor 
int ldrbotr = 3; // bottom right sensor 

 void setup () 
 {
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 10); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  servohori.attach(10);
  servohori.write(90);
  servoverti.attach(9);
  servoverti.write(90);
  Serial.begin(9600);
  delay(500);
 }

void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();

  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculating average
  int avgtop = (topl + topr) / 2; //average of top sensors
  int avgbot = (botl + botr) / 2; //average of bottom sensors
  int avgleft = (topl + botl) / 2; //average of left sensors
  int avgright = (topr + botr) / 2; //average of right sensors

  if (avgtop + constant  < avgbot)
  {  
    if(servov > servovLimitLow)
    servoverti.write(servov -5);
    
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (avgbot + constant  < avgtop)
  { 
   if(servov < servovLimitHigh)
    servoverti.write(servov +5);
    
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
  }
  else 
  {    
    servoverti.write(servov);
  }
  
  if (avgleft - constant  > avgright)
  { 
    servohori.write(servoh +5);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright - constant > avgleft)
  { 
    servohori.write(servoh -5);
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);
  }

  if(topl < 350 && topr < 350 && botl < 350 && botr < 350){
    animationTime = millis();
    if(animationTime - prevAnimationTime > animationInterval){
      if(animationIndex < sadFace_LEN){
      Serial.println(animationIndex);
      animation(sadFace[animationIndex]);
      animationIndex ++;}       
    else{
      animationIndex = 0;}
    prevAnimationTime = animationTime;}
  }
  else
  {  animationTime = millis();
      if(animationTime - prevAnimationTime > animationInterval){
      if(animationIndex < happyFace_LEN){
      Serial.println(animationIndex);
      animation(happyFace[animationIndex]);
      animationIndex ++;}       
    else{
      animationIndex = 0;}
    prevAnimationTime = animationTime;}
  }
  delay(50);
}
