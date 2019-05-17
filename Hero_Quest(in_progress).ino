/*
 Engineer: Michael Dubisz
 5/19/2019
 
 
 This program runs a game where the hero must dodge obstacles in his way
 
 HARDWARE:
    LCD/ LCD accessories 
    Button & 10kohm resistor
    
*/

// Used for LCD
#include <LiquidCrystal.h>



#define BUTTON_PIN  2

//used to keep track of where obstacles are
bool row0 [16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool row1 [16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

volatile bool heroPosition = 0;


//this character will blink to represent the cursor
byte hero[8] = {
  B01110,
  B01110,
  B00100,
  B01111,
  B10100,
  B00100,
  B01011,
  B01000,
};

byte obstacle[8] = {
  B11111,
  B10001,
  B10001,
  B10101,
  B10101,
  B10001,
  B10001,
  B11111,
};


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//NOTE: Some of the LCD pins have been chnaged so that the button could be on pin 2
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




// the setup routine runs once when you press reset:
void setup() {
  
  pinMode(BUTTON_PIN,INPUT);
  
  //set pin 2 as an interrupt
  attachInterrupt(0, ToggleHeroPosition, RISING);
  
  
  lcd.begin(16,2);
  
  //hero is specialchar #1, obstacle is #2
  lcd.createChar(1, hero);
  lcd.createChar(2, obstacle);
  
  lcd.setCursor(0,0);
  lcd.write(byte(1));
  
  lcd.setCursor(15,0);
  lcd.write(byte(2));
  row0[15] = 1;
  
}


void ToggleHeroPosition()
{
    //clear where the hero currently is
    lcd.setCursor(0,heroPosition);
    lcd.print(' ');
    
    //toggle row that the hero is in 
    heroPosition = !heroPosition;
    
    //print the hero in the new row
    lcd.setCursor(0,heroPosition);
    lcd.write(byte(1));
    
    //delay(30);
}




// the loop routine runs over and over again forever:
void loop() {
  
   delay(1000);
  
  //shift row markers 1 left
  for(int i = 0; i <= 15; i++)
  {
      row0[i] = row0[i+1];
      row1[i] = row1[i+1];
  }
  
  row0[15] = 0;
  row1[15] = 0;
  
  
  lcd.clear();
  lcd.setCursor(0,heroPosition);
  lcd.write(byte(1));
  
  //reprint the obstacles
  for(int i = 0; i <= 15; i++)
  {
      if(row0[i] == 1)
      {
        lcd.setCursor(0, i);
        lcd.write(byte(2));
      }
      
      if(row1[i] == 1)
      {
        lcd.setCursor(1, i);
        lcd.write(byte(2));
      }
  }
  
 
  
}

