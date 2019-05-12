/*
 * Engineer: Michael Dubisz
 * 4/26/2019
 * 
 * This program allows the user to turn on an LED
 * strobe light w/ a button and adjust its speed
 * w/ a potentiometer.
 * 
 * HARDWARE:
 *  LED & 5.1kohm resistor (or 2nd potentiometer to adjust brightness of LED)
 *  Button & 10kohm resistor
 *  Potentiometer
 */

#define BUTTON_PIN  2
#define LED_PIN     4

//analog pin
#define POT_PIN     0

int potValue;
bool isOn = false;
volatile bool blinkState = true;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  //set pin 2 as an interrupt
  attachInterrupt(0, SwitchBlinkState, RISING);
  
  Serial.begin(9600);

}


//toggle blinkState & turn LED on or off accordingly
void SwitchBlinkState()
{
  if(blinkState)
  {
    digitalWrite(LED_PIN, LOW);
    isOn = 0;
  }
  
  blinkState = !blinkState;
}


void loop() {
  //read data from potentiometer
  potValue = analogRead(POT_PIN);

  Serial.println(potValue);
  //since original value is between 0-1023, 
  //new value is between 20-531 (adjusted for better strobe speeds)
  potValue = (potValue*0.5) + 20;
  


  //wait around until blinkState is true
  while(!blinkState){}
  
  
  if(isOn)
    digitalWrite(LED_PIN, LOW);
  else
    digitalWrite(LED_PIN, HIGH);

  isOn = !isOn;
  delay(potValue);
    
}
