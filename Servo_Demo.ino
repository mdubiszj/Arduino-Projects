//Basic demo of a servo motor
//note: the servo can only rotate from 0 to 180 degrees

#include <Servo.h>

const int SERVO_PIN = 9;
Servo servo;
int angle = 0;

void setup() {
  // put your setup code here, to run once:
  servo.attach(SERVO_PIN);
  servo.write(angle);
}

void loop() {
  // scan from 0 to 180 degrees
  for(angle = 10; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  } 

}
