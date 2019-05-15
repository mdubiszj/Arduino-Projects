/*
 * Engineer: Michael Dubisz
 * 
 * This program demonstrates using an RGB LED
 * controlled by PWM signals.
 * 
 * HARWARE:
 *  RGB LED
 *  2X 1kohm resistors
 *  330ohm resistor (red seems to be a bit weaker, so using a smaller resistor makes it brighter
 */

#define RED_PIN   3
#define GREEN_PIN 5
#define BLUE_PIN  6


void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {

  //gradually brighten purple
  for(int i = 0; i <= 255; i++)
  {
    analogWrite(RED_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }
  //gradually dim purple
  for(int i = 255; i >= 0; i--)
  {
    analogWrite(RED_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }


  //gradually brighten cyan
  for(int i = 0; i <= 255; i++)
  {
    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }

  //gradually dim cyan
  for(int i = 255; i >= 0; i--)
  {
    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }



  //gradually brighten yellow-ish
  for(int i = 0; i <= 255; i++)
  {
    analogWrite(RED_PIN, i);
    analogWrite(GREEN_PIN, i);
    delay(5);
  }

  //gradually dim yellow-ish
  for(int i = 255; i >= 0; i--)
  {
    analogWrite(RED_PIN, i);
    analogWrite(GREEN_PIN, i);
    delay(5);
  }


  //gradually brighten white
  for(int i = 0; i <= 255; i++)
  {
    analogWrite(RED_PIN, i);
    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }

  //gradually dim white
  for(int i = 255; i >= 0; i--)
  {
    analogWrite(RED_PIN, i);
    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }

}
