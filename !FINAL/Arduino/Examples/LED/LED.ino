#define LEDPin 8
void setup() {
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  digitalWrite(LEDPin, HIGH);
  delay(1000);
  digitalWrite(LEDPin, LOW);
  delay(500);
}
