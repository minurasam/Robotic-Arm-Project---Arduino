#define trigPin 2
#define echoPin 4

void setup() { 
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  int duration = pulseIn(echoPin, HIGH);
  int cm = (duration/2) / 29.1;

  Serial.println(cm);
  delay(100);
}
