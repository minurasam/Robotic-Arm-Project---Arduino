void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  Serial.begin(9600);
  

}

int ir1 = HIGH, ir2 = HIGH;
boolean train = false;

void loop() {
  ir1 = digitalRead(11);
  ir2 = digitalRead(10);

if(ir1 == LOW){
  train = true;
}
else if(ir2 == LOW){
  train = false;
}

if(train){
  digitalWrite(9, HIGH);
}
else{
  digitalWrite(9, LOW);
}
}
