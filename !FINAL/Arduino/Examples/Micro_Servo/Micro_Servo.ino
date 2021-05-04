#include <Servo.h> 

Servo servo; 
int servoPin = 10; 
int servoAngle = 0;

void setup() { 
   servo.attach(servoPin); 
}

void loop(){
  for(servoAngle = 0; servoAngle <= 180; servoAngle++)  //move the micro servo from 0 degrees to 180 degrees
  {                                  
    servo.write(servoAngle);              
    delay(20);                  
  }
  
  delay(1000);
  
  for(servoAngle = 180; servoAngle >= 0; servoAngle--)  //move the micro servo from 0 degrees to 180 degrees
  {                                  
    servo.write(servoAngle);              
    delay(20);                  
  }
  delay(1000);
}
