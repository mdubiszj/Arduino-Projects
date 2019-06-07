/*
Engineer: Michael Dubisz
6/2/2019

This program allows the user to play different tones on multiple buzzers simultaneously (hopefully...)
*/


#define BUZZER_PIN      8
#define BUTTON_PIN      2


bool playMusic = false;
int pitch = 2400;
//2273


// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(BUZZER_PIN, OUTPUT);
  
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
      
      for(int i = 0; i <= pitch/3; i++)
      {
          if(i == (pitch/3)/2)
            digitalWrite(BUZZER_PIN, HIGH);
          if(i == pitch/3)
            digitalWrite(BUZZER_PIN, LOW);
          delayMicroseconds(3);
      }
  }
  
}






