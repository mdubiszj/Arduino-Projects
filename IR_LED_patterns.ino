/*
 * Engineer: Michael Dubisz
 * 1/7/2019
 * 
 * This program allows you to choose from a number of pre-recorded
 * patterns on the LED's using a remote control
 *  
 * HARDWARE:
 *  10X LEDS (or a different number)
 *  10X 5.1kohm resistors
 *  IR receiver
 *  IR remote
 */
 
#include <IRremote.h>

//IR receiver pin
const int RECV_PIN = 2;
//LED pins
const int BASE = 3, NUM = 10;

//remote buttons
//Standard IR Remote
const long ZERO   = 0XFF6897,
           ONE    = 0xFF30CF,
           TWO    = 0xFF18E7,
           THREE  = 0xFF7A85,
           FOUR   = 0xFF10EF,
           FIVE   = 0xFF38C7,
           SIX    = 0xFF5AA5,
           SEVEN  = 0xFF42BD,
           EIGHT  = 0xFF4AB5,
           NINE   = 0xFF52AD;
////SONY BD Remote
//const long  ZERO  = 0x90B47,
//            ONE   = 0x00B47,
//            TWO   = 0x80B47,
//            THREE = 0x40B47,
//            FOUR  = 0xC0B47,
//            FIVE  = 0x20B47,
//            SIX   = 0xA0B47,
//            SEVEN = 0x60B47,
//            EIGHT = 0xE0B47,
//            NINE  = 0x10B47;

//used in case 6
bool LEDs[NUM];
int temp;

int currentState = 0, nextState = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;




//checks if a button on the remote is pressed & acts accordingly
bool CheckStateChange() {
  if (irrecv.decode(&results)){
    switch (results.value) {
      case ZERO:    {nextState = 0; break;}
      case ONE:     {nextState = 1; break;}
      case TWO:     {nextState = 2; break;}
      case THREE:   {nextState = 3; break;}
      case FOUR:    {nextState = 4; break;}
      case FIVE:    {nextState = 5; break;}
      case SIX:     {nextState = 6; break;}
      case SEVEN:   {nextState = 7; break;}
      case EIGHT:   {nextState = 8; break;}
      case NINE:    {nextState = 9; break;}
      default:{break;}//do nothing
    }
    irrecv.resume(); 
  }
  if(nextState != currentState){
    TurnLEDsOff();
    return true;
  }
  else {
    return false;
  }
}





//turns all LED's off
void TurnLEDsOff(){
  for (int i = BASE; i < BASE + NUM; i ++)
    digitalWrite(i, LOW);   
}




//turns all LED's on
void TurnLEDsOn(){
  for (int i = BASE; i < BASE + NUM; i ++)
    digitalWrite(i, HIGH);   
}




void setup(){
  irrecv.enableIRIn();
  irrecv.blink13(true);
  for (int i = BASE; i < BASE + NUM; i ++) {
    pinMode(i, OUTPUT);      //set port ‘i’ as an output port
    LEDs[i] = false;         //set LEDs array as all false 
  }
}




void loop(){
    switch(currentState){

      
          //off
          case 0: {
            //do nothing
            if( CheckStateChange() )
                  goto bottom;
            break;
          }



          //up then down
          case 1: { 
              //turn LED's on in ascending order
              for(int i = 0; i < NUM; i++){
                digitalWrite(BASE + i, HIGH);
                delay(100);
                if( CheckStateChange() )
                  goto bottom;
              }

              //wait 0.5 seconds
              for(int i = 0; i < 5; i++) {
                delay(100);
                if( CheckStateChange() )
                  goto bottom;
              }

              //turn LED's off in descendinng order
              for(int i = NUM-1; i >= 0; i--){
                digitalWrite(BASE + i, LOW);
                delay(100);
                if( CheckStateChange() )
                  goto bottom;
              }

              //wait 1 second
              for(int i = 0; i < 10; i++) {
                delay(100);
                if( CheckStateChange() )
                  goto bottom;
              }
              
            break;
          }



          //down then up
          case 2: {
            //turn LED's on in descending order
              for(int i = NUM-1; i >= 0; i--){
                digitalWrite(BASE + i, HIGH);
                delay(100);
                if( CheckStateChange() )
                  goto bottom;
              }

              //wait 0.5 seconds
              for(int i = 0; i < 5; i++) {
                delay(100);
                if( CheckStateChange() )
                  goto bottom;
              }

              //turn LED's off in ascendinng order
              for(int i = 0; i < NUM; i++){
                digitalWrite(BASE + i, LOW);
                delay(100);
                if( CheckStateChange() )
                  goto bottom;
              }

              //wait 1 second
              for(int i = 0; i < 10; i++) {
                delay(100);
                if( CheckStateChange() )
                  goto bottom;
              }
            break;
          }



          //running up
          case 3: {
            //turn on every 3rd light
            for (int i = 0; i < 3; i++){
              TurnLEDsOff();
              switch(i){
                case(0): {
                  for (int j = 0; j < NUM; j = j+3)
                    digitalWrite(BASE + j, HIGH);
                  break;
                }
                case(1): {
                  for (int j = 1; j < NUM; j = j+3)
                    digitalWrite(BASE + j, HIGH);
                  break;
                }
                case(2): {
                  for (int j = 2; j < NUM; j = j+3)
                    digitalWrite(BASE + j, HIGH);
                  break;
                }
              }
              delay(100);
              if( CheckStateChange() )
                  goto bottom;
            }
            
            break;
          }



        //2 LED's crossing paths
        case 4: {
          for (int i = 0; i < NUM; i++){
            TurnLEDsOff();
            //if there are an even # of LED's, skip one of 
            //the middle iterations so there is no stall.
            if (NUM%2 == 0 && i == (NUM/2)-1)
              i++;
            digitalWrite(BASE + i, HIGH);
            digitalWrite(BASE + NUM -1 - i, HIGH);

            delay(100);
            if( CheckStateChange() )
                  goto bottom;
          }
          
          break;
        }



        //light from the center out
        case 5: {
          //turn LED's on, starting from the center
          for(int i = 0; i < ceil(NUM/2.0); i++){
            digitalWrite(BASE + (NUM/2) + i, HIGH);
            //if NUM is even
            if(NUM%2 == 0)
              digitalWrite(BASE + (NUM/2) - i - 1, HIGH);
            //if NUM is odd
            else
              digitalWrite(BASE + (NUM/2) - i, HIGH);
            delay(100);
            if( CheckStateChange() )
                  goto bottom;
          }
          
          //turn LED's off, starting from the center
          for(int i = 0; i < ceil(NUM/2.0); i++){
            digitalWrite(BASE + (NUM/2) + i, LOW);
            //if NUM is even
            if(NUM%2 == 0)
              digitalWrite(BASE + (NUM/2) - i - 1, LOW);
            //if NUM is odd
            else
              digitalWrite(BASE + (NUM/2) - i, LOW);
            delay(100); 
            if( CheckStateChange() )
                  goto bottom;
          }
          
          //wait 0.5 seconds
          for(int i = 0; i < 5; i++) {
            delay(100);
            if( CheckStateChange() )
              goto bottom;
          }
          break;
        }



        //turns LED's all on and then all off in a random order
        case 6: {
          //set all LEDs values to false
          for(int i = 0; i < NUM; i++)
            LEDs[i] = false;

          //turn LED's on in random order
          for(int i = 0; i < NUM; i++){
            temp = rand()%NUM;
            //if the LED is already on
            if(LEDs[temp] == true)
              i--;
            else{
              digitalWrite(BASE + temp, HIGH);
              LEDs[temp] = true;
              delay(100);
              if( CheckStateChange() )
                goto bottom;
            }
          }

          //wait 0.5 seconds
          for(int i = 0; i < 5; i++) {
            delay(100);
            if( CheckStateChange() )
              goto bottom;
          }

          //turn LED's off in random order
          for(int i = 0; i < NUM; i++){
            temp = rand()%NUM;
            //if the LED is already off
            if(LEDs[temp] == false)
              i--;
            else{ 
              digitalWrite(BASE + temp, LOW);
              LEDs[temp] = false;
              delay(100);
              if( CheckStateChange() )
                goto bottom;
            }
          }

          //wait 1 second
          for(int i = 0; i < 10; i++) {
            delay(100);
            if( CheckStateChange() )
              goto bottom;
          }
          break;
        }



        //fill up from dropping from the top
        case 7: {
          for(int i = NUM; i > 0; i--){
            for(int j = 0; j < i; j++){
              if(j != 0){
                digitalWrite(BASE + NUM - j, LOW);
              }
              digitalWrite(BASE + NUM -1 - j, HIGH);
              delay(100);
              if( CheckStateChange() )
                goto bottom;
            }

            //wait 0.5 seconds
            for(int j = 0; j < 5; j++) {
              delay(100);
              if( CheckStateChange() )
                goto bottom;
            }
          }
          
          //wait .8 seconds
          for(int j = 0; j < 8; j++) {
              delay(100);
              if( CheckStateChange() )
                goto bottom;
          }
          
          TurnLEDsOff();

          //wait 1 second
          for(int j = 0; j < 10; j++) {
              delay(100);
              if( CheckStateChange() )
                goto bottom;
          }
          
          break;
        }



        //zipper
        case 8: {
          //turn every other LED on
          for(int i = 0; i < ceil(NUM/2.0); i++){
            digitalWrite(BASE + (i*2), HIGH);
            delay(100);
              if( CheckStateChange() )
                goto bottom;
          }
          //turn the rest of the LED's on going the other way
          for(int i = 0; i < NUM/2; i++){
            //if NUM is even
            if(NUM%2 == 0)
              digitalWrite((BASE+NUM-1) - (i*2), HIGH);
            //if NUM is odd
            else
              digitalWrite((BASE+NUM-2) - (i*2), HIGH);
            delay(100);
              if( CheckStateChange() )
                goto bottom;
          }

          //turn every other LED off
          for(int i = 0; i < ceil(NUM/2.0); i++){
            digitalWrite(BASE + (i*2), LOW);
            delay(100);
              if( CheckStateChange() )
                goto bottom;
          }
          //turn the rest of the LED's off going the other way
          for(int i = 0; i < ceil(NUM/2.0); i++){
            //if NUM is even
            if(NUM%2 == 0)
              digitalWrite((BASE+NUM-1) - (i*2), LOW);
            //if NUM is odd
            else
              digitalWrite((BASE+NUM-2) - (i*2), LOW);
            delay(100);
              if( CheckStateChange() )
                goto bottom;
          }
          
          //wait 1 second
          for(int j = 0; j < 10; j++) {
              delay(100);
              if( CheckStateChange() )
                goto bottom;
          }
          break;
        }




        //blinking speeding up & slowing down
        case 9: {

          //blinking speeds up
          for(int i = 300; i >= 20; i -= 10){
            TurnLEDsOn();
            delay(i);
            if( CheckStateChange() )
                goto bottom;
            TurnLEDsOff();
            delay(i);
            if( CheckStateChange() )
                goto bottom;
          }
        

        //blinking slows down
        for(int i = 20; i <= 300; i += 10  ){
            TurnLEDsOn();
            delay(i);
            if( CheckStateChange() )
                goto bottom;
            TurnLEDsOff();
            delay(i);
            if( CheckStateChange() )
                goto bottom;
          }

          break;
        }

        

        default:{
          //do nothing
          break;
        }

        
    }

  
  bottom: currentState = nextState;
}
