/*
    Engineer: Michael Dubisz
    5/27/2019
    
    This program will play a melody on a piezo buzzer
    
    HARDWARE:
        Passive piezo buzzer & 100ohm resistor
        Button & 10kohm resistor
        
*/
#include <LiquidCrystal.h>


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

#define SPEAKER_1_PIN   8
#define SPEAKER_2_PIN   9
#define BUTTON_PIN      2

#define SONG_DURATION   38
//beats per minute, based on 4/4 time
#define TEMPO           110
//(0 = really short, 1 = really long)
#define NOTE_LENGTH     0.9


volatile bool playMusic = false;


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//NOTE: Some of the LCD pins have been chnaged so that the button could be on pin 2
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);






// notes in the melody:
int melody[] = {
  0, NOTE_DS4, NOTE_DS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, NOTE_AS4, NOTE_GS4,
  0, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_F4, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_FS4, NOTE_F4, NOTE_DS4,
  0, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_AS4, NOTE_AS4, NOTE_CS5, NOTE_DS5, NOTE_DS5, NOTE_CS5, 0,
  0, NOTE_FS4, NOTE_AS4, NOTE_AS4, NOTE_CS5, NOTE_DS5, NOTE_DS5, NOTE_CS5
};

int harmony[] = {
  
};


// note durations: 4 = quarter note, 8 = eighth note, etc.:
// (a dotted note can be the value in between the two notes. EX: dotted quarter-note = 3)
int beats[] = {
  4, 8, 8, 8, 8, 8, 8, 1,
  8, 8, 8, 8, 8, 8, 8, 8, 3, 8, 2,
  8, 8, 8, 8, 8, 8, 8, 3, 8, 2, 8,
  3, 8, 8, 8, 8, 3, 8, 2
};


void setup() {
    
    for(int i = 0; i < SONG_DURATION; i++)
    {
        harmony[i] = harmony[i]/2;
    }
    
    
    pinMode(BUTTON_PIN, INPUT);
    
    //set pin 2 as an interrupt
    attachInterrupt(0, ButtonPress, RISING);
    
    lcd.begin(16, 2);
    
    //plays a nasty note if the melody, noteDuration, and SONG_DURATION*2 are not all the same
    //(don't ask me why we have to multiply SONG_DURATION by 2)
    if( (sizeof(melody) != sizeof(beats)) || (SONG_DURATION*2 != sizeof(melody)) )
    {
        tone(SPEAKER_1_PIN, NOTE_D3, 1000);
        // lcd.setCursor(0,0);
        // lcd.print(sizeof(noteDurations));
        // lcd.setCursor(0,1);
        // lcd.print(SONG_DURATION);
        while(1){}
    }
    
        
}


//toggle playMusic
void ButtonPress()
{
    playMusic = !playMusic;
}


void loop() 
{
    
    
  //wait around until playMusic becomes true
  while (playMusic == false){}
    
    
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < SONG_DURATION; thisNote++) 
  {
    //if button is pressed, stop the music
    if(playMusic == false)
        break;
        
    //note duration = 240,000/ (tempo*rhythm of note)
    //(240,000 = 4beats/measure * 60sec/min * 1000ms/sec)
    int noteDuration = 240000 / (TEMPO*beats[thisNote]);
    tone(SPEAKER_1_PIN, melody[thisNote], noteDuration*NOTE_LENGTH);
    //tone(SPEAKER_2_PIN, harmony[thisNote], noteDuration*NOTE_LENGTH);

    //play note for noteDuration long
    delay(noteDuration);
    // stop the tone playing:
    noTone(SPEAKER_1_PIN);
    //noTone(SPEAKER_2_PIN);
  }
  
  //once the tune is done, switch playMusic to false
  playMusic = false;
}


//The Final Countdown
//      SONG_DURATION
// 24
//      Melody
// NOTE_FS4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_FS4,
// 0, NOTE_D5, NOTE_CS5, NOTE_D5, NOTE_CS5, NOTE_B4,
// 0, NOTE_D5, NOTE_CS5, NOTE_D5, NOTE_FS4,
// 0, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_B4, NOTE_A4
//      Harmony
// NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4,
// NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
// NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3,
// NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_F4, NOTE_F4, NOTE_FS4
//      Beats
// 3, 16, 16, 4, 4,
// 3, 16, 16, 8, 8, 4, 
// 3, 16, 16, 4, 4,
// 3, 16, 16, 8, 8, 8, 8, 4


// Bum, bada bum bum.... bum bum!
// 8
// NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
// 4, 8, 8, 4, 4, 4, 4, 4


// Full Range quarter notes
// 16
// NOTE_C1, NOTE_G1, NOTE_C2, NOTE_G2, NOTE_C3, NOTE_G3, NOTE_C4, NOTE_G4, 
// NOTE_C5, NOTE_G5, NOTE_C6, NOTE_G6, NOTE_C7, NOTE_G7, NOTE_C8, 0
// 4, 4, 4, 4, 4, 4, 4, 4,
// 4, 4, 4, 4, 4, 4, 4, 4
