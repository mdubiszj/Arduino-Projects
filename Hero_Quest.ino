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

//different values for variable gameState
#define MENU            0
#define GAME            1
#define GAME_OVER       2

//this is the initial speed of how fast the obstacles move 1 space (in ms) 
#define INITIAL_SPEED   800


//used to keep track of where obstacles are
bool row0 [16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool row1 [16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

volatile bool heroPosition = 0;
unsigned long counter = 0;
volatile int gameState = MENU;
int speed = INITIAL_SPEED;


//this character represents the hero
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

//this character represents the obstacle
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


void setup() {
  
  pinMode(BUTTON_PIN,INPUT);
  
  //set pin 2 as an interrupt
  attachInterrupt(0, ButtonPress, RISING);
  
  
  lcd.begin(16,2);
  
  //hero is specialchar #1, obstacle is #2
  lcd.createChar(1, hero);
  lcd.createChar(2, obstacle);
  
}



//button performs different actions depending on what gameState the program is in
void ButtonPress()
{
    //deals with debouncing
    delay(40);
    
    switch(gameState)
    {
        //start game
        case MENU:
        {
            gameState = GAME;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.write(byte(1));
            break;
        }
        
        //toggle hero position
        case GAME:
        {
            //clear where the hero currently is
            lcd.setCursor(0,heroPosition);
            lcd.print(' ');
            
            //toggle row that the hero is in 
            heroPosition = !heroPosition;
            
            //print the hero in the new row
            lcd.setCursor(0,heroPosition);
            lcd.write(byte(1));
            break;
        }
        
        //do nothing
        case GAME_OVER:
        {
            break;
        }
    }
}


//print game menu
void PrintMenu()
{
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("HERO QUEST");
  
  lcd.setCursor(1,0);
  lcd.write(byte(1));
  
  lcd.setCursor(14,0);
  lcd.write(byte(2));
  
  lcd.setCursor(2,1);
  lcd.print("Press Button");
}


//print game over message and score
void PrintGameOver()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GAME OVER");
    delay(2000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SCORE:");
    lcd.setCursor(6,0);
    lcd.print(counter);
    delay(2000);
}



void loop() {
  
  PrintMenu();
  
  //wait until button is pressed/ gameMode switches to GAME
  while(gameState != GAME){}
  
  
  while(gameState == GAME)
  {
      
      //course goes 25% faster every 20 spaces 
      if(counter%20 == 0)
        speed = 0.8 * speed;
      
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
      
      //increment counter
      counter++;
      
      
      //if there is an obstacle in the same space as the hero, then it's GAME OVER
      //(checks for collision with obstacle every 1/10 of speed)
      for(int i = 0; i < 10; i++)
      {
          if( (row0[0] && heroPosition == 0) || (row1[0] && heroPosition == 1) )
          {
              gameState = GAME_OVER;
              PrintGameOver();
              gameState = MENU;
              
              //reset counter, hero position, speed, and obstacle markers
              counter = 0;
              heroPosition = 0;
              speed = INITIAL_SPEED;
              for(int i = 0; i < 16; i++)
              {
                  row0[i] = 0;
                  row1[i] = 0;
              }
              
              break;
          }
          delay(speed/10);
      }
      
      
  }
  
}
