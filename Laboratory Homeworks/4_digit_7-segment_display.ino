const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 13;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 7;

const int pinSW = A2;
const int pinX = A0;
const int pinY = A1;

int switchValue;
int yValue = 0;
int xValue = 0;

const int segSize = 8;
const int noOfDisplays = 4;
const int noOfDigits = 10;
const int interval = 100;

int minThreshold = 400;
int maxThreshold = 700;
int digit = 0;
int lastSwState = LOW;
bool joyMoved = false;
bool yJoyMoved = false;
bool clickSw = false; 
int number = 0;
int lastBlink = 0;

int values[4] = {0, 0, 0, 0};
int previousNumber = -1 ;


int segments[segSize] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
int digits[noOfDisplays]{
pinD1, pinD2, pinD3, pinD4
  
};
byte digitMatrix[noOfDigits][segSize - 1] = {
// a b c d e f g
{1, 1, 1, 1, 1, 1, 0}, // 0
{0, 1, 1, 0, 0, 0, 0}, // 1
{1, 1, 0, 1, 1, 0, 1}, // 2
{1, 1, 1, 1, 0, 0, 1}, // 3
{0, 1, 1, 0, 0, 1, 1}, // 4
{1, 0, 1, 1, 0, 1, 1}, // 5
{1, 0, 1, 1, 1, 1, 1}, // 6
{1, 1, 1, 0, 0, 0, 0}, // 7
{1, 1, 1, 1, 1, 1, 1}, // 8
{1, 1, 1, 1, 0, 1, 1}  // 9
};
void displayNumber(byte digit)
{
  for(int i = 0; i < segSize - 1; i++)
  digitalWrite(segments[i], digitMatrix[digit][i]);

  digitalWrite(segments[segSize-1], LOW);

  
}

void switchDisplay(int num){

  for(int i = 0; i < noOfDisplays; i++)
    digitalWrite(digits[i],HIGH);

    digitalWrite(digits[num],LOW);
}

void setup() {

for(int i = 0; i < segSize ; i++){
    pinMode(segments[i],OUTPUT);
}

for(int i = 0; i < noOfDisplays; i++){
    pinMode(digits[i],OUTPUT);
}

pinMode(pinSW,INPUT_PULLUP);
Serial.begin(9600);
}

void loop() { 
   
switchValue = digitalRead(pinSW);
if (switchValue != lastSwState) {
    if (switchValue == LOW) {
      clickSw = !clickSw;
      yJoyMoved = !yJoyMoved;
      }
}
lastSwState = switchValue;

switchDisplay(0);
displayNumber(values[0]);
if(number == 0 && previousNumber != number){
digitalWrite(pinDP,HIGH);
 if(clickSw == true){
  if(millis() - lastBlink >= interval){
    digitalWrite(pinDP,LOW);
    lastBlink = millis();
  }
}
}
delay(5);

switchDisplay(1);

displayNumber(values[1]);
if(number == 1 && previousNumber != number){
digitalWrite(pinDP,HIGH);
 if(clickSw == true){
  if(millis() - lastBlink >= interval){
    digitalWrite(pinDP,LOW);
    lastBlink = millis();
  }
}
}
delay(5);

switchDisplay(2);
displayNumber(values[2]);
if(number == 2 && previousNumber != number){
digitalWrite(pinDP,HIGH);
 if(clickSw == true){
  if(millis() - lastBlink >= interval){
    digitalWrite(pinDP,LOW);
    lastBlink = millis();
  }
}
}
delay(5);

switchDisplay(3);
displayNumber(values[3]);
if(number == 3 && previousNumber != number){
digitalWrite(pinDP,HIGH);
 if(clickSw == true){
  if(millis() - lastBlink >= interval){
    digitalWrite(pinDP,LOW);
    lastBlink = millis();
  }
}
}
delay(5);



switchValue = digitalRead(pinSW);
xValue = analogRead(pinX);
yValue = analogRead(pinY);


if(clickSw == true){
if(xValue < minThreshold && joyMoved == false){

  if(values[number] > 0){
    values[number]--;
  }else{
    values[number] = 9;
  }
  joyMoved = true;
}
if(xValue > maxThreshold && joyMoved == false){
  if(values[number] < 9){
    values[number]++;
  }else{
    values[number] = 0;
  }
  joyMoved = true;
}
  if(xValue >= minThreshold && xValue <= maxThreshold ){
   joyMoved = false;
  }
}
if(yValue < minThreshold && yJoyMoved == false){
  previousNumber = number;
  if(number > 0)
    number --;
    else
    number = 3;
    yJoyMoved = true;
}
if(yValue > maxThreshold && yJoyMoved == false){
  previousNumber = number;
  if(number < 3)
    number ++;
    else
    number = 0;   
    yJoyMoved = true;
}

if(yValue >= minThreshold && yValue <= maxThreshold && clickSw == false){
  yJoyMoved = false;
 
}

}
