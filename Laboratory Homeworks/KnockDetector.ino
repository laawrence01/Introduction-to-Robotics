const int knockSensorPin = A0;
const int buzzerPin = 11;
const int pushButton = 2;
int knockSensorValue = 0;
int buzzerTone = 4000;
const int interval = 5000;
const int threshold = 1;
unsigned long currentTime = 0;
unsigned long knockTime = 0;
bool ok = 0;
int buttonState = 0;

void setup() {
  pinMode(knockSensorPin,INPUT);
  pinMode(pushButton,INPUT_PULLUP); 
  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(pushButton);
  knockSensorValue = analogRead(knockSensorPin);
  
  if(knockSensorValue > threshold){   
     knockTime=millis();   
     Serial.println("Knock");
     ok = 1;
  }
  
  if(buttonState == 0) // Daca butonul este apasat se va intrerupe sunetul
  noTone(buzzerPin);
  
  currentTime = millis();
  if(currentTime - knockTime >= interval && ok != 0){
    tone(buzzerPin,buzzerTone);
     //if(buttonState == 0) De intrebat de ce are delay ?
         ok = 0;
  }
 
delay(10);
}
