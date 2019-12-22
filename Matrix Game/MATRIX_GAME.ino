#include "LedControl.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>
const int RS = 9;
const int enable = 8;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int Vo = 6;
LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);
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
const uint64_t level1[] = {
  0x00000000000000ff,
  0x00000000003c5a99,
  0x0000183c5ad91818,
  0x183c5ad918181818,
  0xff181818181818ff,
  0x00c33c181818997e,
  0x0042241818995a3c,
  0x00c33c181818997e,
  0x0000ff1818181818,
  0x3c5a991818183c42,
  0x7e99181818183cc3,
  0xff181818181818ff
};
const uint64_t level2[] = {
  0x000000000000003c,
  0x00000000003c66a5,
  0x0000182466e76666,
  0x182466e766666666,
  0xff666666666666ff,
  0x00c37e666666e77e,
  0x0081427e6666e766,
  0x00c37e666666e77e,
  0x00ff666666666666,
  0x3c66e76666667e42,
  0x7ee7666666667ec3,
  0xff666666666666ff 
};
const uint64_t level3[] = {
 0x3c00000000000000,
  0x00000000003c7e99,
  0x0000183c5adb5a5a,
  0x183c7edb5a5a5a5a,
  0xff5a5a5a5a5a5aff,
  0x00c37e5a5a5adb7e,
  0x0081427e5a5adb5a,
  0x00c37e5a5a5adb7e,
  0x00ff5a5a5a5a5a5a,
  0x3c5adb5a5a5a7e42,
  0xff5a5a5a5a5a5aff  
};
byte Jump[] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B10101,
  B00100,
  B00100,
  B00100
};
byte Skull[] = {
  B00000,
  B01110,
  B10101,
  B11011,
  B01110,
  B01110,
  B00000,
  B00000
};
byte Heart[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};
bool initialMatrix3[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 1},
  {1, 1, 0, 0, 0, 0, 0, 0}
};
bool initialMatrix2[8][8] = {
  {1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
bool initialMatrix1[8][8] = {
  {0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
bool matrix[8][8] = {
  {0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
bool skull[8][8] = {
  {0, 0, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 1, 0, 0, 1, 1},
  {1, 1, 0, 1, 1, 0, 1, 1},
  {0, 1, 1, 0, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0}
};
const int level1_LEN = sizeof(level1) / 8;
const int level2_LEN = sizeof(level2) / 8;
const int level3_LEN = sizeof(level3) / 8;
const int doodleImage_LEN = sizeof(doodleImage) / 8;
const int minThreshold = 400;
const int maxThreshold = 600;
const int joyX = A1;
const int joyY = A0;
const int pushButton = 13;
const int maxLength = 8;
const int maxJump = 3;
const int difficultySpawnTime1 = 1500;
const int difficultySpawnTime2 = 800;
const int difficultySpawnTime3 = 600;
const int difficultySpawnTime4 = 300;
const int maxScoreLevel1 = 9;
const int maxScoreLevel2 = 30;
const int distanceBetweenPlatforms = 3;
const int maxContrast = 200;
const int minContrast = 50;
const int animationInterval = 100;;
const int deathIntervalSpawn = 2000;
char incomingByte;
char username[255];
unsigned long  animationTime;
unsigned long  prevAnimationTime = 0;
unsigned long scoreTime;
unsigned long prevScoreTime = 0;
unsigned long deathTime;
unsigned long prevDeathTime = 0;
unsigned long Time;
unsigned long currentTime;
unsigned long previousTime = 0;
int highestScore = 0;
int score = 0;
int contrast = 120;
int lives = 3;
int index = 0;
int level = 1;
int jumpVelocity = 1;
int valX, valY;
int animationIndex = 0;
int ok = 1;
int moveInfo = 0;
int difficulty = 1;
int scrollSettings = 0;
int i = 1;
int selected = 1;
int buttonState;
int prevButtonState = 0;
int setupSelected = 0;
bool movedX = false, movedY = false;
bool high;
bool died = false;
bool stopGame = true;
bool showGreet = true;
bool passLevel = true;
bool passLevel2 = true;
bool passLevel3 = true;

struct player {
  int x;
  int y;
} doodle;

void mapRendering() {
  for (int row = 0; row < maxLength; row++) {
    for (int col = 0; col < maxLength; col++) {
      lc.setLed(0, row, col, matrix[row][col]);
    }
  }
}

void scoreFuntion() {
  scoreTime = millis();
  if (scoreTime - prevScoreTime >= 3000) {
    if (level == 1) {
      score++;
    }
    else if (level == 2) {
      score = score + 2;
    }
    else {
      score = score + 3;
    }
    prevScoreTime = scoreTime;
  }
  if (score > EEPROM.get(0, highestScore)) {
    highestScore = score;
  }
  EEPROM.put(0, highestScore);
}

void idleJump() {
  if (ok == 1) {
    lc.setLed(0, doodle.y, doodle.x, true);
    if (millis() - Time >= 150) {
      lc.setLed(0, doodle.y, doodle.x, false);
      Time = millis();
      doodle.y = doodle.y - 1;
      i++;
      if (i == 3) {
        ok = 0;
      }
      if (i == 3) {
        high = true;
      }
    }
  }
  if (ok == 0) {
    lc.setLed(0, doodle.y, doodle.x, true);
    if (millis() - Time >= 100) {
      lc.setLed(0, doodle.y, doodle.x, false);
      Time = millis();
      doodle.y = doodle.y + 1;
      i--;
      if (i != 3) {
        high = false;
      }
      if (i == 1) {
        ok = 1;
      }
    }
  }
}

void moveJump() {
  if (valX < minThreshold && high == true ) {
    if (movedX == false) {
      doodle.x = doodle.x - jumpVelocity;
      if (doodle.x < 0 && jumpVelocity == 1) {
        doodle.x = 7;
      }
      if (doodle.x < 0 && jumpVelocity > 1) {
        doodle.x = 6;
      }
      idleJump();
      movedX = true;
    }
  }
  else {
    if ( valX > maxThreshold && high == true ) {
      if (movedX == false) {
        doodle.x = doodle.x + jumpVelocity;

        if (doodle.x > 7 && jumpVelocity == 1) {
          doodle.x = 0;
        }
        if (doodle.x > 7 && jumpVelocity > 1) {
          doodle.x = 1;
        }
        idleJump();
        movedX = true;
      }
    }
    else {
      idleJump();
      movedX = false;
    }
  }
}

void checkPlatform() {
  if (matrix[doodle.y + 1][doodle.x] != 1 && matrix[doodle.y + 2][doodle.x] != 1 &&
      matrix[doodle.y + 3][doodle.x] != 1 ) {
    doodle.y = doodle.y + 1;
  }
  if (doodle.y >= 7) {
    died = true;
  }
}

void moveOnPlatform() {
  if (matrix[doodle.y][doodle.x] == 1) {
    doodle.y = doodle.y - 1;
  }
}

void death() {
  for (int row = 0; row < maxLength; row++) {
    for (int col = 0; col < maxLength; col++) {
      lc.setLed(0, row, col, skull[row][col]);
    }
  }
  for (int row = 0; row < maxLength; row++) {
    for (int col = 0; col < maxLength; col++) {
      matrix[row][col] = initialMatrix1[row][col];
    }
  }
  if(level == 1){
  doodle.x = 6;
  doodle.y = 5;
  }
  else if(level == 2){
  doodle.x = 1;
  doodle.y = 4;
  }
  else if(level == 3){
  doodle.x = 7;
  doodle.y = 5;
  }
}

void checkDeath() {

  if (died == true) {
    lives--;
    jumpVelocity = 1;
    if (lives == 0) {
      level = 1;
      stopGame = true;
      score = 0;
      passLevel  = true;
      passLevel2 = true;
      passLevel3 = true;
    }
    deathTime = millis();
  }
}

void jumpSize() {
  if (prevButtonState !=  buttonState) {
    if ( buttonState == LOW) {
      if ( jumpVelocity < maxJump) {
        jumpVelocity ++;
      }
      else if ( jumpVelocity == maxJump) {
        jumpVelocity = 1;
      }
    }
    prevButtonState =  buttonState;
  }
}

void frequencyPlatformSpawn() {
  currentTime = millis();
  switch (difficulty) {
    case 1:  if (currentTime -  previousTime >= difficultySpawnTime1) {
        fall();
        platformSpawn(level);
        previousTime = currentTime;
      }
      break;
    case 2:  if (currentTime -  previousTime >= difficultySpawnTime2) {
        fall();
        platformSpawn(level);
        previousTime = currentTime;
      }
      break;
    case 3:  if (currentTime -  previousTime >= difficultySpawnTime3) {
        fall();
        platformSpawn(level);
        previousTime = currentTime;
      }
      case 4:  if (currentTime -  previousTime >= difficultySpawnTime4) {
        fall();
        platformSpawn(level);
        previousTime = currentTime;
      }
      break;
    default: break;
  }
}

void levelFunction() {
  if (level == 1) {
    if (score >  maxScoreLevel1 && passLevel2 == true) {
      for ( int i = 0; i < level2_LEN; i++) {
        animation(level2[i]);
        delay(100);
      }
      delay(3000);
      level++;
      passLevel2 = false;
    }
  }
  else if (level == 2) {
    if (score >  maxScoreLevel2 && passLevel3 == true) {
      for ( int i = 0; i < level3_LEN; i++) {
        animation(level3[i]);
        delay(100);
      }
      delay(3000);
      level++;
      passLevel3 = false;
    }
  }
}

void platformSpawn (int level) {
  bool empty = true;
  for (int i = 0; i < distanceBetweenPlatforms; i++) {
    for (int j = 0; j < maxLength; j++) {
      if (matrix[i][j] != 0) {
        empty = false;
      }
    }
  }
  if (empty) {
    long pivotPoint = random(0, 8);
    switch (level) {

      case 1:
        for (int i = 0; i <= 3 ; i++) {
          matrix[0][pivotPoint + i] = 1;
          lc.setLed(0, 0, pivotPoint, true);
        }

      case 2:
        for (int i = 0; i <= 2 ; i++) {
          matrix[0][pivotPoint + i] = 1;
          lc.setLed(0, 0, pivotPoint, true);
        }

      case 3:
        for (int i = 0; i <= 1 ; i++) {
          matrix[0][pivotPoint + i] = 1;
          lc.setLed(0, 0, pivotPoint, true);
        }
        break;
      default: break;
    }
  }
}

void fall() {
  for (int i = maxLength - 1; i > 0; i--) {
    for (int j = 0; j < maxLength; j++) {
      matrix[i][j] = matrix[i - 1][j];
      lc.setLed(0, i - 1, j, false);
      lc.setLed(0, i, j, matrix[i][j]);
    }
  }

  for (int j = 0; j < maxLength; j++) {
    matrix[0][j] = 0;
    lc.setLed(0, 0, j, false);
  }
}

void animation(uint64_t image) {
  for (int i = 0; i < maxLength; i++) {
    byte r = (image >> i * maxLength) & 0xFF;
    for (int j = 0; j < maxLength; j++) {
      lc.setLed(0, i, j, bitRead(r, j));
    }
  }
}

void lcdSetup() {
  selectedFunction(selected);
  moveArrow();

  if (prevButtonState !=  buttonState) {
    if ( buttonState == LOW) {
      if (selected == 1) {

        setupSelected = 1;
        lcd.clear();
      }

      else if (selected == 2) {
        setupSelected = 2;
        lcd.clear();
      }

      else if (selected == 3) {
        setupSelected = 3;
        lcd.clear();
      }
      else if (selected == 4) {
        setupSelected = 4;
        lcd.clear();
      }
    }
    prevButtonState =  buttonState;
  }
}

void settings() {

  if (valX < minThreshold) {
    if (movedX == false) {
      scrollSettings = !scrollSettings;
      movedX = true;
    }

  }
  else {
    movedX = false;
  }

  if (valY < minThreshold) {
    if (movedY == false) {
      if (scrollSettings == 0) {
        if (difficulty < 5) {
          difficulty++;
        }
        if (difficulty > 4) {
          difficulty = 1;
        }

      }
      else if (scrollSettings == 1) {
        if (contrast < maxContrast)
          contrast = contrast + 10;
      }
      movedY = true;
      lcd.clear();
    }
  }
  else {
    if ( valY > maxThreshold) {
      if (movedY == false) {
        if (scrollSettings == 0) {
          if (difficulty > 0) {
            difficulty--;
          }
          if (difficulty < 1) {
            difficulty = 4;
          }

        }
        else if (scrollSettings == 1) {
          if (contrast > minContrast) {
            contrast = contrast - 10;
          }
        }
        movedY = true;
        lcd.clear();
      }
    }
    else
    {
      movedY = false;
    }
  }
  switch (difficulty) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Are u a:");
      lcd.setCursor(8, 0);
      lcd.print("Baby");
      lcd.setCursor(12, 0);
      lcd.write(byte(1));
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Are u a:");
      lcd.setCursor(8, 0);
      lcd.print("Novice");
      lcd.setCursor(14, 0);
      lcd.write(byte(1));
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Are u a:");
      lcd.setCursor(8, 0);
      lcd.print("Hero");
      lcd.setCursor(12, 0);
      lcd.write(byte(1));
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("Are u:");
      lcd.setCursor(6, 0);
      lcd.print("Insane");
      lcd.setCursor(12, 0);
      lcd.write(byte(1));
      lcd.setCursor(13, 0);
      lcd.print("?    ");
      break;
    default: break;
  }
  lcd.setCursor(0, 1);
  lcd.print("Contrast:");
  lcd.setCursor(9, 1);
  lcd.print(contrast);
}
void info() {
  if (valX < minThreshold) {
    if (movedX == false) {
      if(moveInfo > 1){
        moveInfo = 0;
      }
      else{
        moveInfo ++;
      } 
      movedX = true;
    }
  }
  else {
    movedX = false;
  }
  if(moveInfo == 0){
  lcd.setCursor(0, 0);
  lcd.print("Anghel Laurentiu");
  lcd.setCursor(0, 1);
  lcd.print("@UnibucRobotics");
  }
  else if(moveInfo == 1){
    lcd.setCursor(0, 0);
    lcd.print("    GitHub:     ");
    lcd.setCursor(0, 1);
    lcd.print("bit.ly/38Su49t");
  }  
  else{
    lcd.setCursor(0, 0);
    lcd.print(" DoodleJump    ");
    lcd.setCursor(0, 1);
    lcd.print("Thanks for plein");
  }
}

void start() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HP:");
  lcd.setCursor(3, 0);
  lcd.print(lives);
  lcd.setCursor(4, 0);
  lcd.write(byte(0));
  lcd.setCursor(7, 0);
  lcd.print("Score:");
  lcd.setCursor(14, 0);
  lcd.print(score);
  lcd.setCursor(0, 1);
  lcd.print("Jump:");
  lcd.setCursor(5, 1);
  lcd.print(jumpVelocity);
  lcd.setCursor(6, 1);
  lcd.write(byte(2));


  switch (difficulty) {
    case 1:
      lcd.setCursor(8, 1);
      lcd.print("Baby");
      lcd.setCursor(12, 1);
      lcd.write(byte(1));
      break;
    case 2:
      lcd.setCursor(8, 1);
      lcd.print("Novice");
      lcd.setCursor(14, 1);
      lcd.write(byte(1));
      break;
    case 3:
      lcd.setCursor(8, 1);
      lcd.print("Hero");
      lcd.setCursor(12, 1);
      lcd.write(byte(1));
      break;
     case 4:
      lcd.setCursor(8, 1);
      lcd.print("Insane");
      lcd.setCursor(14, 1);
      lcd.write(byte(1));
      break;
    default: break;
  }
}

void highScore() {
  int value;
  value = EEPROM.get(0, highestScore);
  lcd.setCursor(0, 0);
  lcd.print("HighestScore:");
  lcd.setCursor(13, 0);
  lcd.print(value);
  lcd.setCursor(0, 1);
  lcd.print("Name:");
  lcd.setCursor(5, 1);
  for (int i = 0; i < index; i++) {
    lcd.print(username);
  }
}

void showGreetings() {
  if (showGreet == true) {
    lcd.setCursor(0, 0);
    lcd.print("Welome to DoodleJump");
    lcd.setCursor(5, 1);
    lcd.print("Enjoy!");
    delay(2000);
    showGreet = false;
    lcd.clear();
  }
}

void moveArrow() {
  if (valX > maxThreshold) {
    if ( movedX == false ) {
      selected++;
      if (selected > 4) {
        selected = 1;
      }
      movedX = true;
    }
  }
  else
  {
    if (valX < minThreshold) {
      if ( movedX == false ) {
        selected--;
        if (selected < 1) {
          selected = 4;
        }

        movedX = true;
      }
    }
    else {
      movedX = false;
    }
  }
}

void selectedFunction(int selected) {
  lcd.setCursor(0, 0);
  if (selected == 1) {
    lcd.print(">Start");
  }
  else {
    lcd.print(" Start");
  }
  lcd.setCursor(7, 0);
  if (selected == 2) {
    lcd.print(">Settings");
  } else {
    lcd.print(" Settings");
  }
  lcd.setCursor(0, 1);
  if (selected == 3) {
    lcd.print(">Info");
  } else {
    lcd.print(" Info");
  }
  lcd.setCursor(6, 1);
  if (selected == 4) {
    lcd.print(">HighScore");
  } else {
    lcd.print(" HighScore");
  }
}

void lcdClearLine(int line) {
  lcd.setCursor(0, line);
  for (int i = 0; i < maxLength * 2; ++i) {
    lcd.write(' ');
  }
}

void setup() {
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 15); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  pinMode(pushButton, INPUT_PULLUP);
  Serial.begin(9600);
  doodle.x = 7;
  doodle.y = 5;
  Time = millis();
  lcd.begin(16, 2);
  randomSeed(analogRead(A3));
  lcd.createChar(0, Heart);
  lcd.createChar(1, Skull);
  lcd.createChar(2, Jump);
}

void loop() {
  valX = analogRead(joyX);
  valY = analogRead(joyY);
  buttonState = digitalRead(pushButton);
  analogWrite(Vo, contrast);

  if (stopGame == false) {
    if (died == false) {

      if (passLevel == true) {
        for ( int i = 0; i < level1_LEN; i++) {
          animation(level1[i]);
          delay(100);
        }
        delay(2000);
        passLevel = false;
      }
      mapRendering();
      moveJump();
      frequencyPlatformSpawn();
      moveOnPlatform();
      checkPlatform();
      jumpSize();
      scoreFuntion();
      checkDeath();

      if (doodle.y < 0) {
        doodle.y = 1;
      }

      if (setupSelected == 1) {
        start();
        levelFunction();
        if (lives == 0) {
          lcd.clear();
          setupSelected = 0;
        }
      }
    }
    else {
      death();
      currentTime = millis();
      if (currentTime - deathTime >= deathIntervalSpawn ) {
        died = false;
      }
    }
  }
  else {
    animationTime = millis();
    if(animationTime - prevAnimationTime > animationInterval){
      if(animationIndex < doodleImage_LEN){
      animation(doodleImage[animationIndex]);
      animationIndex ++;       
      }       
    
    else{
      animationIndex = 0;
    }
    prevAnimationTime = animationTime;
    }
    
    if (setupSelected == 0 ) {
      lives = 3;
      showGreetings();
      lcdSetup();
    }
    if (setupSelected == 2) {
      settings();
      if (prevButtonState !=  buttonState) {
        if ( buttonState == LOW) {
          setupSelected = 0;
          lcd.clear();
        }
        prevButtonState =  buttonState;
      }
    }
    if (setupSelected == 3) {
      info();
      if (prevButtonState !=  buttonState) {
        if ( buttonState == LOW) {
          setupSelected = 0;
          lcd.clear();
        }
        prevButtonState =  buttonState;
      }
    }
    if (setupSelected == 4) {
      highScore();
      if (prevButtonState !=  buttonState) {
        if ( buttonState == LOW) {
          setupSelected = 0;
          lcd.clear();
        }
        prevButtonState =  buttonState;
      }
    }
    if (setupSelected == 1) {
      stopGame = false;
    }
  }
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    username[index] = incomingByte;
    
    index++;
  }else
  Serial.flush();
  username[index] = '\0';
}
