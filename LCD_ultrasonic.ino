/*
 Engineer: Michael Dubisz
 1/3/2019

 This program prints the distance an object is from the ultrasonic sensor to an LCD.
*/

//Trig of the ultrasonic sensor is hooked to pin 6, and Echo is hooked to pin 7
const int trigPin = 6, echoPin = 7;    
long duration;
int distance;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin , INPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Distance:");
  lcd.setCursor(4,1);
  lcd.print("cm");

  
}

void loop() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;

  //clears previous distnact, then prints distance to LCD screen
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(0,1);
  lcd.print(distance);

  delay(500);
}
