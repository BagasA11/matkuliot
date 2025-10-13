const int PWM_CHANNEL = 0;     // ESP32 has 16 channels which can generate 16 independent waveforms
const int PWM_FREQ = 500;      // Recall that Arduino Uno is ~490 Hz. Official ESP32 example uses 5,000Hz
const int PWM_RESOLUTION = 8;  // We'll use same resolution as Uno (8 bits, 0-255) but ESP32 can go up to 16 bits

// The max duty cycle value based on PWM resolution (will be 255 if resolution is 8 bits)
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1);

const int LED_OUTPUT_PIN = 18;

const int DELAY_MS = 4;  // delay between fade increments

void setup() {
  // Attach the GPIO to the Channel
  ledcAttachChannel(LED_OUTPUT_PIN, PWM_FREQ, PWM_RESOLUTION, PWM_CHANNEL);
  Serial.begin(115200);
}

void loop() {

  // fade up PWM on given channel
  // for (int dutyCycle = 0; dutyCycle <= MAX_DUTY_CYCLE; dutyCycle++) {
  //   ledcWriteChannel(PWM_CHANNEL, dutyCycle);
  //   Serial.println(dutyCycle);
  //   delay(DELAY_MS);
  // }
  ledcWriteChannel(PWM_CHANNEL, MAX_DUTY_CYCLE);
  delay(2000);
  ledcWriteChannel(PWM_CHANNEL, 0);
  // Serial.println(0);
  delay(1000);

  // fade down PWM on given channel
  // for (int dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= 0; dutyCycle--) {
  //   ledcWriteChannel(PWM_CHANNEL, dutyCycle);
  //   Serial.println(dutyCycle);
  //   delay(DELAY_MS);
  // }
  
}