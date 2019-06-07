/*
Engineer: Michael Dubisz
6/7/2019

This program allows the user to play different tones on multiple buzzers simultaneously (hopefully...)
*/


#define BUZZER1_PIN     8
#define BUZZER2_PIN     9
#define BUTTON_PIN      2

#define SONG_LENGTH     8


volatile bool playMusic = false;
volatile int count1 = 0;
volatile int count2 = 0;
int pitches1[] = {0, 138, 69, 87, 130, 92, 87, 92}; //{0, 276, 138, 174};
int pitches2[] = {0, 116, 58, 69, 109, 77, 69, 77}; //{0, 232, 116, 138};
volatile int counter = 0;
volatile int pitch1 = pitches1[counter];
volatile int pitch2 = pitches2[counter];


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
    delay(30);
    //either increment counter or set it back to 0
    if(counter == SONG_LENGTH-1)
        counter = 0;
    else
        counter++;
        
    //if we're at the beginning of the array, don't play anything.
    //otherwise, play the nth note in the pitches array.
    if(counter == 0)
        playMusic = false;
    else
    {
        playMusic = true;
        pitch1 = pitches1[counter];
        pitch2 = pitches2[counter];
        count1 = 0;
        count2 = 0;
    }
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






