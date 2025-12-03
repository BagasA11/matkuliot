#define D4 2
#define D3 0
#define D2 4
#define D1 5

int leds[]={(int)D4, (int)D3, (int)D2, (int)D1};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<4;i++){
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0;i<4;i++){
    digitalWrite(leds[i], HIGH);
  }
}
