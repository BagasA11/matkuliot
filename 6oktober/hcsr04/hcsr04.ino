
const int trig_pin=13, echo_pin=12;
float timing=0.0, distance=0.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig_pin, INPUT);
  pinMode(echo_pin, OUTPUT);
  digitalWrite(trig_pin, LOW);
  Serial.begin(9600);
}

float getDistance(float timing){
  return (timing * 0.034)/2;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig_pin, LOW);
  delay(2);

  digitalWrite(trig_pin, HIGH);
  delay(10);

  timing=pulseIn(echo_pin, HIGH);
  distance=getDistance(timing);
  Serial.print(timing);Serial.print(", ");
  Serial.println(distance);
}
