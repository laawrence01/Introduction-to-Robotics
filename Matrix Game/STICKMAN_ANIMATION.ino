#include "LedControl.h"
LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER

const uint64_t doodleImage[] = {
  0xc64438927c103838,
  0x6c28107c92383800,
  0x6c10385438380000,
  0x4428ba5438103838,
  0x0028287c54381038,
  0x000010286c543810,
  0x0000000010286c7c,
  0x00000028282810fe,
  0x0000282828103854,
  0x004444281038d638,
  0x6c28107c92383800,
  0x6c10385438380000,
  0x6c28107c92383800,
  0x44443810fe103838,
};
const int doodleImage_LEN = sizeof(doodleImage) / 8;
unsigned long  animationTime;
unsigned long  prevAnimationTime = 0;
int animationIndex ;
int animationInterval = 100;
int maxLength = 8;

void animation(uint64_t image) {
  for (int i = 0; i < maxLength; i++) {
    byte r = (image >> i * maxLength) & 0xFF;
    for (int j = 0; j < maxLength; j++) {
      lc.setLed(0, i, j, bitRead(r, j));
    }

  }
}

void setup() {
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 10); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}

void loop() {
  animationTime = millis();
  if(animationTime - prevAnimationTime > animationInterval){
      if(animationIndex < doodleImage_LEN){
      Serial.println(animationIndex);
      animation(doodleImage[animationIndex]);
      animationIndex ++;       
      }       
    else{
      animationIndex = 0;
    }
    prevAnimationTime = animationTime;
    }
}
  
