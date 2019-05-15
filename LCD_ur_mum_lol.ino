/*
 Engineer: Michael Dubisz
 1/1/2019

 This program says "ur mum lol" and laughs at the user if they press the button.
*/

const int BUTTONPIN = 6;    //button connected to pin 6
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int buttonState = 0;

void setup() {

  pinMode(BUTTONPIN , INPUT);

  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
}

void loop() {
  
  // Print a message to the LCD.
  lcd.print("Press the button");
  lcd.setCursor(0,1);
  lcd.print("for a surprise! ");

  buttonState = digitalRead(BUTTONPIN);

 if (buttonState) {
  lcd.clear();
  lcd.print("ur mum lol");

  delay(2500);

  lcd.clear();
  lcd.print("XD XD XD XD XD");
  delay (500);
  
  for (int i = 0; i < 4; i++){
    lcd.scrollDisplayRight();
    delay (500);
    lcd.scrollDisplayLeft();
    delay (500);
  }
  
  lcd.clear();
  delay (1000);
 }
  
}
