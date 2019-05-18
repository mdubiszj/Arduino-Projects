/*
 Engineer: Michael Dubisz
 5/18/2019
 
 
 This program runs a game where the hero must dodge obstacles in his way
 
 HARDWARE:
    LCD/ LCD accessories 
    Button & 10kohm resistor
    
*/

// Used for LCD
#include <LiquidCrystal.h>



#define BUTTON_PIN  2
#define MENU        0
#define GAME        1

//used to keep track of where obstacles are
bool row0 [16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool row1 [16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

volatile bool heroPosition = 0;
byte counter = 0;
volatile int gameState = MENU;


//this character respresents the hero
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

//this character represents the obstacles
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
  attachInterrupt(0, ButtonPress, RISING);
  
  
  lcd.begin(16,2);
  
  //hero is specialchar #1, obstacle is #2
  lcd.createChar(1, hero);
  lcd.createChar(2, obstacle);
  
}


void ButtonPress()
{
    if(gameState == MENU)
    {
        gameState = GAME;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(byte(1));
    }
    
    else if (gameState == GAME)
    {
        //clear where the hero currently is
        lcd.setCursor(0,heroPosition);
        lcd.print(' ');
        
        //toggle row that the hero is in 
        heroPosition = !heroPosition;
        
        //print the hero in the new row
        lcd.setCursor(0,heroPosition);
        lcd.write(byte(1));
        //delay(15);
    }
}




void loop() {
  
      //print menu
      lcd.setCursor(0,0);
      lcd.print("Hero Quest");
      lcd.setCursor(0,1);
      lcd.print("Press Button:");
  
  //wait until button is pressed/ gameMode switches to GAME
  while(gameState == MENU){}
  
  
  while(gameState == GAME)
  {
      
      //shift row markers 1 left
      for(int i = 0; i < 15; i++)
      {
          row0[i] = row0[i+1];
          row1[i] = row1[i+1];
      }
      
      
      //print new obstacles every other space
      row0[15] = (counter%4==0) ? 1 : 0;
      row1[15] = (counter%4==2) ? 1 : 0;
      
      
      // clear the screen (but reprint the hero)
      lcd.clear();
      lcd.setCursor(0,heroPosition);
      lcd.write(byte(1));
      
      //reprint the obstacles
      for(int i = 0; i <= 15; i++)
      {
          if(row0[i])
          {
            lcd.setCursor(i, 0);
            lcd.write(byte(2));
          }
          
          if(row1[i])
          {
            lcd.setCursor(i, 1);
            lcd.write(byte(2));
          }
      }
      
      
      //if there is an obstacle in the same space as the hero, then it's GAME OVER
      for(int i = 0; i < 10; i++)
      {
          if( (row0[0] && heroPosition == 0) || (row1[0] && heroPosition ==1) )
          {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("GAME OVER");
              
              delay(2000);
              
              //reset counter, hero position & obstacle markers
              counter = 0;
              heroPosition = 0;
              for(int i = 0; i < 16; i++)
              {
                  row0[i] = 0;
                  row1[i] = 0;
              }
              
              gameState = MENU;
          }
          
          delay(100);
      }
      
      counter++;
  }
}
