
int led1=13, led2=12, led3=14, led4=27, led5=26;//25 33 32 18
int led6=25, led7=33, led8=32, led9=18;
int btn1=34, btn2=39, btn3=36;

// bool ledTest=true;

// unsigned long lastTime1=millis();
// byte lastButtonState1;
// byte ledState1=LOW;
// bool led1_disabled=false;

// unsigned long lastTime2=millis();
// byte lastButtonState2;
// byte ledState2=LOW;
// bool led2_disabled=false;

// unsigned long lastTime3=millis();
// byte lastButtonState3;
// byte ledState3=LOW;
// bool led3_disabled=false;

bool rowActive[3] = {true, true, true}; // row1,row2,row3
byte lastButtonState[3] = {HIGH, HIGH, HIGH};
unsigned long lastDebounceTime[3] = {0,0,0};
const unsigned long debounceDelay = 100;
int queue=0;

// fungsi baca tombol toggle
void readButtons() {
  int btnPins[3] = {btn1, btn2, btn3};
  for (int i=0; i<3; i++) {
    int reading = digitalRead(btnPins[i]);

    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
      lastButtonState[i] = reading;
    }

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // tombol ditekan (LOW karena pakai INPUT_PULLUP)
      if (reading == LOW) {
        rowActive[i] = !rowActive[i]; // toggle aktif/nonaktif
        Serial.print("Row "); Serial.print(i+1);
        Serial.print(" state = ");
        Serial.println(rowActive[i] ? "ACTIVE" : "DISABLED");
        delay(200); // cegah double toggle
      }
    }
    Serial.print(i);Serial.print(". "); Serial.print(reading); Serial.print(":");
    Serial.println(lastButtonState[i]);
    
  }
}

// unsigned long ledDuration=millis();
void setup() {
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  
  Serial.begin(115200);
}
// bool tekan=false;
// merah(100)->kuning
void loop() {
  readButtons();
  switch(queue){
    case 0:
      if(rowActive[0]) {
        // row1 hijau
        digitalWrite(led1, LOW);   // merah row1 off
        digitalWrite(led2, LOW);   // merah row1 off
        digitalWrite(led3, HIGH);  // hijau row1 on

        if(rowActive[1]) {
          digitalWrite(led4, HIGH);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
        } else{ 
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
        } 

        if(rowActive[2]) { 
          digitalWrite(led7, HIGH);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
        }else {
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          // digitalWrite(led5, LOW);
        }
        delay(2000);
        // transisi 
        // merah mati, kuning nyala
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
        delay(300);
        // kuning -> merah
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        delay(300);
        // digitalWrite(led4, HIGH);
        // digitalWrite(led5, HIGH);
        
      }
      break;

    case 1:
      if(rowActive[1]) {
        // merah -> kuning
        digitalWrite(led4, LOW);
        digitalWrite(led5, HIGH);
        digitalWrite(led6, LOW);
        delay(300);
        // kuning -> hijau
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
        digitalWrite(led6, HIGH);

        if(rowActive[0]) { 
          digitalWrite(led1, HIGH); 
          digitalWrite(led2, LOW); 
          digitalWrite(led3, LOW); 
        } else{ 
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW); 
        }

        if(rowActive[2]){
          digitalWrite(led7, HIGH);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
        } else{
          digitalWrite(led7, LOW);
          digitalWrite(led8, LOW);
          digitalWrite(led9, LOW);
          
        }
        delay(2000);
        // reverse
        digitalWrite(led4, LOW);
        digitalWrite(led5, HIGH);
        digitalWrite(led6, LOW);
        delay(300);
        digitalWrite(led4, HIGH);
        digitalWrite(led5, LOW);
        digitalWrite(led6, LOW);
        delay(300);
        // delay(1000);
      }
      break;

    case 2:
      if(rowActive[2]) {
        // merah->kuning
        digitalWrite(led7, LOW);
        digitalWrite(led8, HIGH);
        digitalWrite(led9, LOW);
        delay(300);
        // kuning -> hijau
        digitalWrite(led7, LOW);
        digitalWrite(led8, LOW);
        digitalWrite(led9, HIGH);
      
        if(rowActive[0]){ 
          digitalWrite(led1, HIGH); 
          digitalWrite(led2, LOW); 
          digitalWrite(led3, LOW); 
        }else{
          digitalWrite(led1, LOW); 
          digitalWrite(led2, LOW); 
          digitalWrite(led3, LOW);
        }

        if(rowActive[1]){
          digitalWrite(led4, HIGH);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
        }else{
          digitalWrite(led4, LOW);
          digitalWrite(led5, LOW);
          digitalWrite(led6, LOW);
          // digitalWrite(led4, LOW);
        }
        delay(2000);
        // reverse
        // hijau -> kuning
        digitalWrite(led7, LOW);
        digitalWrite(led8, HIGH);
        digitalWrite(led9, LOW);
        delay(300);
        digitalWrite(led7, HIGH);
        digitalWrite(led8, LOW);
        digitalWrite(led9, LOW);
        delay(300);
        // delay(1000);
      }
      break;
  }
  Serial.print("row1:");Serial.print(rowActive[0]);
  Serial.print(",row2:");Serial.print(rowActive[1]);
  Serial.print(",row3:");Serial.println(rowActive[2]);
  Serial.println();

  queue+=1;
  if(queue>2){
    queue=0;
    // transisi dari merah ke hijau
    if(rowActive[0]){
      // merah
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      delay(300);
      // kuning menyala
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      delay(300);
      
    } else{
      // memastikan lampu tetap mati jika tidak aktif
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      delay(100);
    }
    if(!rowActive[1])digitalWrite(led4, LOW);
    if(!rowActive[2])digitalWrite(led5, LOW);
  };


  // // Serial.print(".");
  // // if (ledState1 != HIGH) digitalWrite(led1, LOW);
  // // if (ledState2 != HIGH) digitalWrite(led2, LOW);
  // // if (ledState3 != HIGH) digitalWrite(led3, LOW);

  // if(millis()-lastTime1 >= 500){
  //   byte btnState1=digitalRead(btn1);
  //   if(btnState1 != lastButtonState1){
  //     lastButtonState1=btnState1;
  //     lastTime1=millis();
  //     // if released
  //     if(btnState1==LOW){
  //       if(ledState1==HIGH){
  //         ledState1=LOW;
  //         // led1_disabled=true;
  //       }else{
  //         ledState1=HIGH;
  //         // led1_disabled=false;
  //       }
  //       // digitalWrite(led1, ledState1);
  //     }
  //   }
  //   Serial.print("led1: ");
  //   Serial.println(lastButtonState1);
  // }

  // if(millis()-lastTime2 >= 500){
  //   byte btnState2=digitalRead(btn2);
  //   if(btnState2 != lastButtonState2){
  //     lastButtonState2=btnState2;
  //     lastTime2=millis();
  //     // if released
  //     if(btnState2==LOW){
  //       if(ledState2==HIGH){
  //         ledState2=LOW;
  //         // led2_disabled=true;
  //       }else{
  //         ledState2=HIGH;
  //         // led2_disabled=false;
  //       }
  //       // digitalWrite(led2, ledState2);
  //     }
  //   }
  //   Serial.print("led2: ");
  //   Serial.println(lastButtonState2);
  // }

  // if(millis()-lastTime3 >= 500){
  //   byte btnState3=digitalRead(btn3);
  //   if(btnState3 != lastButtonState3){
  //     lastButtonState3=btnState3;
  //     lastTime3=millis();
  //     // if released
  //     if(btnState3==LOW){
  //       if(ledState3==HIGH){
  //         ledState3=LOW;
  //         // led3_disabled=true;
  //       }else{
  //         ledState3=HIGH;
  //         // led3_disabled=false;
  //       }
  //       // digitalWrite(led3, ledState3);
  //     }
  //   }
  //   Serial.print("led3: ");
  //   Serial.println(lastButtonState3);
  //   Serial.println();
  //   Serial.println();
  // }
  // switch(queue){
  //   case 0:
  //     if(ledState1==HIGH){
  //       digitalWrite(led1, LOW);
  //       digitalWrite(led3, HIGH);

  //       if(ledState2==HIGH){
  //         digitalWrite(led4, HIGH);
  //       }
  //       if(ledState3==HIGH){
  //         digitalWrite(led5, HIGH);
  //       }
  //       delay(2000);
  //       digitalWrite(led1, HIGH);
  //       digitalWrite(led3, LOW);
  //       delay(1000);
  //     }else{}
  //     break;

  //   case 1:
  //     if(ledState2==HIGH){
  //       // row 2
  //       digitalWrite(led4, LOW);
  //       // row 1
  //       if(ledState1==HIGH){
  //         digitalWrite(led1, HIGH);
  //         digitalWrite(led3, LOW);
  //       }
  //       // row 3
  //       if(ledState3==HIGH){
  //         digitalWrite(led5, HIGH);
  //       }
  //       delay(2000);
  //       digitalWrite(led4, HIGH);
  //       delay(1000);

  //     }else{}
  //     break;

  //   case 2:
  //     if(ledState3==HIGH){
  //       // row 3
  //       digitalWrite(led5, LOW);
  //       // row 1
  //       if(ledState1==HIGH){
  //         digitalWrite(led1, HIGH);
  //         digitalWrite(led3, LOW);
  //       }
  //       if(ledState2 == HIGH){
  //         digitalWrite(led4, HIGH);
  //       }
  //       delay(2000);
  //       digitalWrite(led5, HIGH);
  //       delay(1000);
  //     }else{}

  //     break;

  //   default:
  //     queue=0;
  //     break;
  // }
  // Serial.print(ledState1); Serial.print(", ");
  // Serial.print(ledState2); Serial.print(", ");
  // Serial.println(ledState3);
  // Serial.print("queue: ");
  // Serial.println(queue);
  // queue++;
}
