#include <Servo.h> 

Servo servo1;
void setup() { 
  servo1.attach(8);
  servo1.write(0);
}

void loop(){
  /*for(int i = 0; i <= 50; i++){
    servo1.write(i);
    delay(20);
  }

  delay(2000);

  for(int i = 50; i >= 0; i--){
    servo1.write(i);
    delay(20);
  }*/
}
