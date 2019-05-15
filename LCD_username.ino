/*
 Engineer: Michael Dubisz
 1/4/2019

 This program allows the user to print a username with letters and numbers on the LCD using a joystick.
*/

//switch pin of joystick is connected to D6, x pin & y pin are connected to A1 and A0, respectively
const int switchPin = 6, xPin = 1, yPin = 0;

//BLINKRATE = how fast the cursor blinks
const int BLINKRATE = 1000;
//CENTER_TOLERANCE = how far you have to move the joystick from the middle for it to register (normally between 0-400)
const int CENTER_TOLERANCE = 300;

//used to see whether caps is on or off
const int CAPS_ON = 1, CAPS_OFF = 0;
int capsState = CAPS_OFF;

//measures the x and y position of the joystick, and whether or not the button has been pressed  
int xPosition, yPosition, pressed;

int cursorPosition = 0;
//keeps track of the current char in each of the 16 positions in the first row of the LCD
char currentChar[16] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
//used for looping the cursor blink
int count;

//this character will blink to represent the cursor
byte blinker[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

// include the LiquidCrystal library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




//If caps is on and userChar is a letter, print userChar as a captial letter. 
//Otherwise, just print userChar.
void printChar(char userChar){
    if(capsState == CAPS_ON && (userChar >= 'a' && userChar <= 'z') ){
      lcd.print( static_cast<char>(userChar - 32) );
    }
    else{
      lcd.print(userChar);
    }
}





void setup() {

  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //print an initial message
  lcd.setCursor(0,1);
  lcd.print("Caps: Off");
  
  //blinker is specialchar #1
  lcd.createChar(1, blinker);
}





void loop() {

  //read the joystick data
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  pressed = digitalRead(switchPin);

  count = 0;
  //while the joystick hasn't been moved/ pressed and it's been less than 1 second
  while (    (xPosition > (512 - CENTER_TOLERANCE) && xPosition < (512 + CENTER_TOLERANCE) ) 
          && (yPosition > (512 - CENTER_TOLERANCE) && yPosition < (512 + CENTER_TOLERANCE) )
          && (pressed)
          && (count < BLINKRATE) ) {

    lcd.setCursor(cursorPosition, 0);
    
    if (count < BLINKRATE/2){
      printChar(currentChar[cursorPosition]);
    }
    
    else{
      lcd.write(byte(1));
    }

    delay(100);
    
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    pressed = digitalRead(switchPin);
    count = count + 100;
  }
  


  //if the joystick is pushed left
  if(yPosition > (512 + CENTER_TOLERANCE) ) {
    
    //leave the current position with the correct char
    lcd.setCursor(cursorPosition, 0);
    printChar(currentChar[cursorPosition]);

    //update the current position to 1 left (if it's already at 0, stay at 0)
    cursorPosition = (cursorPosition == 0)? 0 : cursorPosition - 1;

    //print the blinker on new current position
    lcd.setCursor(cursorPosition, 0);
    lcd.write(byte(1));
    
    delay(250);
  }


  //if the joystick is pushed right
  else if(yPosition < (512 - CENTER_TOLERANCE)){

    //leave the current position with the correct char
    lcd.setCursor(cursorPosition, 0);
    printChar(currentChar[cursorPosition]);

    //update the current position to 1 left (if it's already at 15, stay at 15)
    cursorPosition = (cursorPosition == 15)? 15 : cursorPosition + 1;  

     //print the blinker on new current position
    lcd.setCursor(cursorPosition, 0);
    lcd.write(byte(1));
    
    delay(250);
  }


  //if the joystick is pushed up
  else if (xPosition < (512 - CENTER_TOLERANCE) ) {

    //figure out what the next char will be
    if (currentChar[cursorPosition] == ' ')
      currentChar[cursorPosition] = 'a';
    else if (currentChar[cursorPosition] == 'z')
      currentChar[cursorPosition] = '0';
    else if (currentChar[cursorPosition] == '9')
      currentChar[cursorPosition] = ' ';
    else
      currentChar[cursorPosition]++; 
    

    //print the new char
    lcd.setCursor(cursorPosition, 0);
    printChar(currentChar[cursorPosition]);

    delay(250);
    
  }


  //if the joystick is pushed down
  else if (xPosition > (512 + CENTER_TOLERANCE) ) {

    //figure out what the next char will be
    if (currentChar[cursorPosition] == ' ')
      currentChar[cursorPosition] = '9';
    else if (currentChar[cursorPosition] == '0')
      currentChar[cursorPosition] = 'z';
    else if (currentChar[cursorPosition] == 'a')
      currentChar[cursorPosition] = '  ';
    else
      currentChar[cursorPosition]--; 

    //print the new char
    lcd.setCursor(cursorPosition, 0);
    printChar(currentChar[cursorPosition]);
    
    delay(250);
    
  }
  


  //if the joystick is pressed
  else if (!pressed) {

    if (capsState == CAPS_OFF){
      capsState = CAPS_ON;
      lcd.setCursor(6,1);
      lcd.print("On ");
    }

    else if (capsState == CAPS_ON){
      capsState = CAPS_OFF;
      lcd.setCursor(6,1);
      lcd.print("Off");
    }

    //prints the new char (capital or lowercase)
    lcd.setCursor(cursorPosition, 0);
    printChar(currentChar[cursorPosition]);

    delay(250);
  }


 
}
