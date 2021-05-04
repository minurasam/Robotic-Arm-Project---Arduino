#include<SoftwareSerial.h>
SoftwareSerial serialWriter(5, 4); //d1 d2 rx tx

void setup() {
  Serial.begin(9600);
  serialWriter.begin(9600);
}

void loop() {
  //if(Serial.available())
    serialWriter.write("Hello");//Serial.read());
}
