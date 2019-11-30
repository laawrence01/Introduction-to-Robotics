#include <LiquidCrystal.h>
const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);
int startValue = 0;
int playerChoice = 0;
int prevMillis = 0;
unsigned long currentMillis = 0;
int switchValue;
int ok = 0;
int i = 0;
int startLvlValue = 0;
int afterPlayLvlValue = 0;
const int pinSW = 13;
const int pinX = A0;
const int pinY = A1;
bool clickSw = false;
bool joyMoved = false;
bool choseOption = false;
const int minThreshold = 400;
const int maxThreshold = 600;
const int addLevelInterval = 5000;
const int finishLevel = 10000;
int xValue = 0;
int yValue = 0;
int lastSwState = HIGH;

void setup(){
  lcd.begin(16, 2);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
}

void play()
{ 
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.setCursor(6, 0);
  lcd.print(startLvlValue);
  lcd.setCursor(9, 0);
  lcd.print("Lives:3");
  lcd.setCursor(4, 1);
  lcd.print("Score:");
  lcd.setCursor(10, 1);
  lcd.print(startLvlValue* 3);
  
  if(currentMillis - prevMillis >= addLevelInterval ){
    startLvlValue++;
    prevMillis = currentMillis;
    if(startLvlValue >= 30)
    startLvlValue = 0;
    i++;
  }
  if(prevMillis >= finishLevel && i == 2)
  {
   lcd.clear();
   ok = 1;
   prevMillis = 0;
  }
  
  
}

void settings()
{
  yValue = analogRead(pinY);
   if (yValue > maxThreshold && joyMoved == false) {
        startLvlValue++;
        if (startLvlValue > 30) {
          startLvlValue = 0;
        }
   joyMoved = true;
   }
    if (yValue < minThreshold && joyMoved == false) {
        startLvlValue--;
        if (startLvlValue < 0) {
          startLvlValue= 30;
        }
        joyMoved = true;
      }
      if (yValue > minThreshold && yValue < maxThreshold) {
        joyMoved = false;
      }
  lcd.setCursor(0, 0);
  lcd.print("Level :");
  lcd.setCursor(8, 0);
  lcd.print(startLvlValue);
  
  if(startLvlValue < 10) {
    lcd.setCursor(8, 0);
    lcd.print("0");
    lcd.setCursor(9, 0);
    lcd.print(startLvlValue);
  } else {
    lcd.setCursor(8, 0);
    lcd.print(startLvlValue);
  }
  
}
void hScore()
{
  lcd.setCursor(0, 0);
  lcd.print("Highscore is:");
  lcd.setCursor(14, 0);
  lcd.print(afterPlayLvlValue * 3);
}

void loop(){

  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  switchValue = digitalRead(pinSW);
  
  if (switchValue != lastSwState) {
    if (switchValue == LOW) {
        choseOption = !choseOption;
        lcd.clear();
        ok = 0;         
      }
      lastSwState = switchValue;
      ok = 0;
  }
  
  if(choseOption == false){
    
    lcd.setCursor(0, 0);
  if (playerChoice == 0) {
    lcd.print(">Play");
  } else {
    lcd.print(" Play");
  }
  lcd.setCursor(7, 0);
  if (playerChoice == 1) {
    lcd.print(" >Settings");
  } else {
    lcd.print("  Settings");
  }
  lcd.setCursor(0, 1);
  if (playerChoice == 2) {
    lcd.print(">HScore");
  } else {
    lcd.print(" HScore");
  }
  
  if(xValue < minThreshold && joyMoved == false){

    playerChoice--;
    if(playerChoice < 0)
       playerChoice = 2;
  
    joyMoved = true;
  }
  if(xValue > maxThreshold && joyMoved == false){
  playerChoice++;
   if(playerChoice > 2)
     playerChoice = 0;
  
  joyMoved = true;
}
 if(xValue >= minThreshold && xValue <= maxThreshold ){
   joyMoved = false;
 }
  }
  else
  {  
    if(playerChoice == 0){
      currentMillis = millis();
      if( ok == 0 )
       play();       
     
     else
      {
      afterPlayLvlValue = startLvlValue;
      lcd.setCursor(0, 0);
      lcd.print("Congratulations");
      i = 0;
      }       
       
    }
     if(playerChoice == 1)
       settings();
     
       if(playerChoice == 2)
       hScore();
  }


  
 
}
