/*
 * Adjustable STrobe Light (Basics)
 * This program allows the user to adjust the speed
 * of a strobe light w/ a potentiometer.
 * 
 * HARDWARE:
 *  LED & 5.1kohm resistor (or 2nd potentiometer to adjust brightness of LED)
 *  Potentiometer
 */

int LED_PIN = 4;

//analog pin
int POT_PIN = 0;

int potValue;
bool isOn = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  //set pin 2 as an interrupt
  attachInterrupt(0, SwitchBlinkState, RISING);
  
  Serial.begin(9600);

}



void loop() {
  //read data from potentiometer
  potValue = analogRead(POT_PIN);

  Serial.println(potValue);
  //since original value is between 0-1023, 
  //new value is between 20-531 (adjusted for better strobe speeds)
  potValue = (potValue*0.5) + 20;
  
  
  if(isOn)
    digitalWrite(LED_PIN, LOW);
  else
    digitalWrite(LED_PIN, HIGH);

  isOn = !isOn;
  delay(potValue);
    
}
