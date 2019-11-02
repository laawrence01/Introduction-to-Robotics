const int bluePin = 9;
const int greenPin = 6;
const int redPin = 5;

const int potPin1 = A0;
const int potPin2 = A1;
const int potPin3 = A2;

int potValue1 = 0;
int potValue2 = 0;
int potValue3 = 0;
void setup() {
  pinMode(potPin1,INPUT);
  pinMode(potPin2,INPUT);
  pinMode(potPin3,INPUT);
  
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);
  
  potValue1 = map(potValue1,0,1023,0,255);
  potValue2 = map(potValue2,0,1023,0,255);
  potValue3 = map(potValue3 ,0,1023,0,255);
  
  analogWrite(bluePin, potValue1);
  analogWrite(greenPin, potValue2);
  analogWrite(redPin, potValue3);

}
