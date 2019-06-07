/*
Engineer: Michael Dubisz
6/6/2019

This program allows the user to play different tones on multiple buzzers simultaneously (hopefully...)
*/


#define BUZZER1_PIN     8
#define BUZZER2_PIN     9
#define BUTTON_PIN      2


bool playMusic = false;
int count1 = 0;
int count2 = 0;
int pitch1 = 1460;
int pitch2 = 955;


byte filler = 0;


// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(BUZZER1_PIN, OUTPUT);
  pinMode(BUZZER2_PIN, OUTPUT);
  
  //set pin 2 as an interrupt
  attachInterrupt(0, ButtonPress, RISING);
  
}


//toggle playMusic
void ButtonPress()
{
    playMusic = !playMusic;
}


// the loop routine runs over and over again forever:
void loop() {
    
  if(playMusic)
  {
      
          count1++;
          if(count1 == (pitch1/3)/2)
            digitalWrite(BUZZER1_PIN, HIGH);
          if(count1 == pitch1/3){
            digitalWrite(BUZZER1_PIN, LOW);
            count1 = 0;}
      

          count2++;
          if(count2 == (pitch2/3)/2)
            digitalWrite(BUZZER2_PIN, HIGH);
          if(count2 == pitch2/3){
            digitalWrite(BUZZER2_PIN, LOW);
            count2 = 0;}
        
      
      delayMicroseconds(3);
  }
  
}






