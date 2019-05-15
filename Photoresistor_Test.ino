//This program reads data from a photo resistor and turns an LED on if the data is above a certain value.


#define LED_PIN     2
#define PHOTO_PIN   0

int value = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  value = analogRead(PHOTO_PIN);
  Serial.println(value);
  
  if(value >= 1000)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);
    
  delay(100);               // wait
}
