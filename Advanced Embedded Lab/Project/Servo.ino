#include <Servo.h>


int servoPin = 9;
Servo servo;
int angle = 0; //The initial position of the servo in degree

void setup() {
    servo.attach(servoPin);
   
}
void loop() {
  // We will scan the angle from 0 to 180 degree. As we 
  // have to enable our motor to open the curtain 
  // in both direction, the angles are important

  for(angle = 0; angle < 180; angle++){
    servo.write(angle);
    delay(15); 
  }

  // Now we will rotate the servo towards other direction
  // for that we will consider the angle from 180 to 0 degree
  
  for (angle = 180; angle > 0; angle--) {
    servo.write(angle);
    delay(15);
  }
}
