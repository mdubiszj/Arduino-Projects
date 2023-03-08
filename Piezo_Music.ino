/*
    Engineer: Michael Dubisz
    5/26/2019
    
    This program will play a melody on a piezo buzzer
    
    HARDWARE:
        Piezo buzzer (passive or active)
        100ohm resistor (or potentiometer) to control volume
        Button & 10kohm resistor
        
*/


//#include "pitches.h"
void pitches()
{
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
}

#define SPEAKER_PIN   8
#define BUTTON_PIN    2


//beats per minute, based on 4/4 time
#define TEMPO           110
//0 = really short (stacatto), 1 = really long (legato)
#define NOTE_LENGTH     0.8


volatile bool playMusic = false;




// notes in the melody:
int melody[] = {
  NOTE_D3, NOTE_D3, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C3, NOTE_C3, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_B2, NOTE_B2, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_AS2, NOTE_AS2, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_D3, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C3, NOTE_C3, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_B2, NOTE_B2, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_AS2, NOTE_AS2, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_B3, NOTE_B3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_AS3, NOTE_AS3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_B3, NOTE_B3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_AS3, NOTE_AS3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_A4, NOTE_D5, NOTE_C5, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4 
  
};


// note durations: 4 = quarter note, 8 = eighth note, etc.:
// (a tied note rhythm = (rhythm/number) EX: dotted quarter-note (3 8th notes tied together) = 8/3.0)
double beats[] = {
  16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 16, 16, 16, 16, 16, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 8, 16, 16, 16, 2, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 8, 8, 16, 8
  
};


void setup() {    
    pinMode(BUTTON_PIN, INPUT);
    Serial.begin(9600);
    //set pin 2 as an interrupt
    attachInterrupt(0, ButtonPress, RISING);
    
    //plays a nasty note if the melody and beats are not the same length
    //(don't ask me why we have to multiply SONG_DURATION by 2)
    if( (sizeof(melody)/sizeof(int) != sizeof(beats)/sizeof(double)) )
    {
        tone(SPEAKER_PIN, NOTE_D3, 1000);
        delay(1000);
        Serial.println(sizeof(melody));
        Serial.println(sizeof(beats));
        Serial.println(sizeof(int));
        Serial.println(sizeof(double));
    } 
}




//toggle playMusic
void ButtonPress()
{
    delayMicroseconds(20);
    playMusic = !playMusic;
}




void loop() 
{
  //wait around until playMusic becomes true
  while (!playMusic){}
    
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++) 
  {
    //if button is pressed, stop the music
    if(!playMusic)
        break;
        
    //note duration = 240,000/ (tempo*rhythm of note)     (240,000 = 4beats/measure * 60sec/min * 1000ms/sec)
    int noteDuration = 240000 / (TEMPO*beats[thisNote]);
    tone(SPEAKER_PIN, melody[thisNote], noteDuration*NOTE_LENGTH);
    //play note for noteDuration long
    delay(noteDuration);
    }
  
  //once the tune is done, switch playMusic to false
  playMusic = false;
}









///////////////////
// SONG LIBRARY  //
///////////////////

/*
The Sound of Silence
          SONG_DURATION
   67

          TEMPO
  110
          
  
          Melody
   0, NOTE_DS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, NOTE_AS4, NOTE_GS4,
   0, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_F4, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_FS4, NOTE_F4, NOTE_DS4,
   0, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, NOTE_AS4, NOTE_CS5, NOTE_CS5, NOTE_DS5, NOTE_DS5, NOTE_CS5, 0,
   0, NOTE_FS4, NOTE_FS4, NOTE_AS4, NOTE_AS4, NOTE_CS5, NOTE_CS5, NOTE_DS5, NOTE_DS5, NOTE_CS5, 0,
   0, NOTE_FS4, NOTE_FS4, 
   NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_CS5,
   0, NOTE_DS5, NOTE_CS5, NOTE_AS4, 0, 0, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_CS5, NOTE_F4, NOTE_FS4, NOTE_DS4
          Beats
   4, 8, 8, 8, 8, 8, 8, 1,
   8, 8, 8, 8, 8, 8, 8, 8, (8/3.0), 8, 2,
   8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 2, 8,
   4, 8, 8, 8, 8, 8, 8, 4, 8, 2, 8,
   4, 8, 8,
   8, (8/5.0), 8, 8, 8, (8/3.0), 8, 4, (8/5.0),
   4, 8, 8, 2, 2, 8, 8, 8, 8, (8/7.0), 8, 8, (8/7.0)
 */




/*
The Final Countdown
      SONG_DURATION
 24

      TEMPO
  110
      Melody
 NOTE_FS4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_FS4,
 0, NOTE_D5, NOTE_CS5, NOTE_D5, NOTE_CS5, NOTE_B4,
 0, NOTE_D5, NOTE_CS5, NOTE_D5, NOTE_FS4,
 0, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_B4, NOTE_A4
 
      Harmony
 NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4,
 NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
 NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3,
 NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_F4, NOTE_F4, NOTE_FS4
 
      Beats
 3, 16, 16, 4, 4,
 3, 16, 16, 8, 8, 4, 
 3, 16, 16, 4, 4,
 3, 16, 16, 8, 8, 8, 8, 4
 */




/*
 Bum, bada bum bum.... bum bum!
 
    Melody
 NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4

    Beats
 4, 8, 8, 4, 4, 4, 4, 4
*/




/*
    Super Mario Theme

      TEMPO
  180
  
      Melody
  NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5,
  NOTE_G5, 0, NOTE_G4, 0, 
  NOTE_C5, NOTE_G4, 0, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  0, NOTE_E5,NOTE_C5, NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_G4, 0, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  0, NOTE_E5,NOTE_C5, NOTE_D5, NOTE_B4,
  
  0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  0, NOTE_GS4, NOTE_A4, NOTE_C4, 0, NOTE_A4, NOTE_C5, NOTE_D5,
  0, NOTE_DS5, 0, NOTE_D5,
  NOTE_C5, 0,
  
  0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  0, NOTE_GS4, NOTE_A4, NOTE_C4, 0, NOTE_A4, NOTE_C5, NOTE_D5,
  0, NOTE_DS5, 0, NOTE_D5,
  NOTE_C5, 0,
  
  NOTE_C5, NOTE_C5, NOTE_C5, 0, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  
  NOTE_C5, NOTE_C5, NOTE_C5, 0, NOTE_C5, NOTE_D5, NOTE_E5,
  0, 
  NOTE_C5, NOTE_C5, NOTE_C5, 0, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5,
  NOTE_G5, 0, NOTE_G4, 0, 
  

      Beats
  8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4, 
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,
  
  
  4, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  2, 2,
  
  4, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  2, 2,
  
  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  
  8, 4, 8, 8, 8, 8, 8,
  1, 
  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8, 4,
  4, 4, 4, 4, 

 */




/*
    Megalovania

        TEMPO
    110

        Melody
    NOTE_D3, NOTE_D3, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C3, NOTE_C3, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_B2, NOTE_B2, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_AS2, NOTE_AS2, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_D3, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C3, NOTE_C3, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_B2, NOTE_B2, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_AS2, NOTE_AS2, NOTE_D4, NOTE_A3, 0, NOTE_GS3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_B3, NOTE_B3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_AS3, NOTE_AS3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_B3, NOTE_B3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_AS3, NOTE_AS3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_A4, NOTE_D5, NOTE_C5, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4 



        Beats
    16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 16, 16, 16, 16, 16, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 8, 16, 16, 16, 2, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 8, 8, 16, 8

 */




// Full Range quarter notes
// 16
// NOTE_C1, NOTE_G1, NOTE_C2, NOTE_G2, NOTE_C3, NOTE_G3, NOTE_C4, NOTE_G4, 
// NOTE_C5, NOTE_G5, NOTE_C6, NOTE_G6, NOTE_C7, NOTE_G7, NOTE_C8, 0
// 4, 4, 4, 4, 4, 4, 4, 4,
// 4, 4, 4, 4, 4, 4, 4, 4
