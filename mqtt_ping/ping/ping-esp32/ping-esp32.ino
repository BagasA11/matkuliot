#define L1 15 
#define L2 2
#define L3 4
#define L4 5

void setup() {
  // put your setup code here, to run once:
  pinMode(L1,OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(L1, HIGH);
  digitalWrite(L2,HIGH);
  digitalWrite(L3, HIGH);
  digitalWrite(L4,HIGH);
}
