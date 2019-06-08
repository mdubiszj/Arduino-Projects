/*
Engineer: Michael Dubisz
6/7/2019

This program allows the user to play different tones on multiple buzzers simultaneously (hopefully...)
*/


#define BUZZER1_PIN     8
#define BUZZER2_PIN     9
#define BUZZER3_PIN     10
#define BUTTON_PIN      2

#define SONG_LENGTH     8


volatile bool playMusic = false;
volatile int count1 = 0;
volatile int count2 = 0;
volatile int count3 = 0;
int pitches1[] = {0, 360, 381, 360, 360, 360, 360, 360};
int pitches2[] = {0, 302, 320, 302, 269, 269, 269, 285};
int pitches3[] = {0, 240, 240, 227, 214, 227, 240, 240};
volatile int counter = 0;
volatile int pitch1 = pitches1[counter];
volatile int pitch2 = pitches2[counter];
volatile int pitch3 = pitches3[counter];



// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(BUZZER1_PIN, OUTPUT);
  pinMode(BUZZER2_PIN, OUTPUT);
  pinMode(BUZZER3_PIN, OUTPUT);
  
  //set pin 2 as an interrupt
  attachInterrupt(0, ButtonPress, RISING);
  
  for(int i = 0; i < SONG_LENGTH; i++){
    pitches1[i] = pitches1[i]*2;
    pitches2[i] = pitches2[i]*2;
    pitches3[i] = pitches3[i]*2;
}

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
        pitch3 = pitches3[counter];
        count1 = 0;
        count2 = 0;
        count3 = 0;
    }
}



// the loop routine runs over and over again forever:
void loop() {
    
  if(playMusic)
  {
      
          count1++;
          if(count1 == pitch1/2)
            digitalWrite(BUZZER1_PIN, HIGH);
          if(count1 == pitch1){
            digitalWrite(BUZZER1_PIN, LOW);
            count1 = 0;}
      

          count2++;
          if(count2 == pitch2/2)
            digitalWrite(BUZZER2_PIN, HIGH);
          if(count2 == pitch2){
            digitalWrite(BUZZER2_PIN, LOW);
            count2 = 0;}
        
        
        count3++;
          if(count3 == pitch3/2)
            digitalWrite(BUZZER3_PIN, HIGH);
          if(count3 == pitch3){
            digitalWrite(BUZZER3_PIN, LOW);
            count3 = 0;}
        
      
      delayMicroseconds(1);
  }
  
}


/*LIBRARY

Claire de Lune (2-part)
8
{0, 521, 261, 328, 492, 348, 328, 348};
{0, 438, 219, 261, 414, 293, 261, 293};


*/


