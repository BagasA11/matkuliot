int led1=13, led2=12, led3=14;
int button1=26, button2=25, button3=33;

byte lastButtonState[3]={HIGH, HIGH,HIGH};
bool modeActive[3]={false, false, false};
unsigned long lastDebounceTimes[3]={0,0,0};
unsigned long timeDelay=100;
// int queue=0;

void readButton(){
  int btnPins[3]={button1, button2, button3};
  for(int i=0;i<3;i++){
    if(i==1) continue;  
    byte reading=digitalRead(btnPins[i]);
    if(reading!=lastButtonState[i]){
      lastDebounceTimes[i]=millis();
      lastButtonState[i]=reading;
    }
    if(millis()-lastDebounceTimes[i]>timeDelay){
      if (reading==LOW){
        // toggle mode active/disabled
        modeActive[i]=!modeActive[i];
        Serial.print("mode-"); Serial.print(i); Serial.print(": ");
        Serial.println(modeActive[i]? "enabled":"disabled");
        // Serial.print(", ");
        if(modeActive[i]){
          forceButtonDisabled(i);
        }  
        delay(200);
      }
      // check if other button are active then force disabled
    }

  }
  // Serial.println();
}

void forceButtonDisabled(int i){
  for(int j=0; j<3; j++){
    if(j==i){
      continue;
    }
    modeActive[j]=false;
  }
}

int findActiveBTN(){
  int key=(-1);
  for(int i=0;i<3;i++){
    if(modeActive[i]){
      key=i;
      break;
    }
  }
  return key;
}

void modeOne(int led1, int led2, int led3){
  // led1 blink
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(300);
  // led2
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  delay(300);
  // led3
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(300);
  // off
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(100);

}

void modeTwo(int led1, int led2, int led3){
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
  delay(300);
  digitalWrite(led1,LOW);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,LOW);
  delay(300);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  delay(90);
}

void modeThree(int led1, int led2, int led3){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(200);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  delay(300);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(100);
}

void disabledLED(int led1,int led2,int led3){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  // output
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  // input
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  delay(100);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(100);
}
unsigned long printPoint=0;
void loop() {
  // put your main code here, to run repeatedly:
  readButton();
  int key=findActiveBTN();

  if(millis()-printPoint>2000){
    printPoint=millis();
    for(int i=0;i<3;i++){

      Serial.print("mode-");Serial.print(i);
      Serial.print(":");Serial.print(modeActive[i]?"TRUE":"FALSE");
      Serial.print(",");
    }
    
    Serial.println();
    Serial.print("index:");Serial.println(key);
  }

  switch(key){
    case -1:
      disabledLED(led1, led2, led3);
      break;
    case 0:
      modeOne(led1, led2, led3);
      break;
    case 1:
      modeTwo(led1, led2, led3);
      break;
    case 2:
      modeThree(led1, led2, led3);
      break;
    default:
      break;
  }
  if(key>2){
    key=-1;
  }

}
