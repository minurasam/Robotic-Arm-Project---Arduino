#define IR 8
#define LED 7
void setup() {
  pinMode(IR, INPUT);
  Serial.begin(9600);
}

void loop() {
 bool result = digitalRead(IR);
 if(result == LOW){
  digitalWrite(LED, HIGH);
 }
 else{
  digitalWrite(LED, LOW);
 }
 delay(100);
}
