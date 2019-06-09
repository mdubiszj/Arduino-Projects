


/*  "Eventually.h" & "Eventually.cpp"  */

#ifndef EVENTUALLY_H
#define EVENTUALLY_H

#include <limits.h>
#include <Arduino.h>

#define EVENTUALLY_MAX_CONTEXTS 10
#define EVENTUALLY_MAX_LISTENERS 20

class EvtManager;
class EvtContext;
class EvtListener;

typedef bool (*EvtAction)(EvtListener *, EvtContext *);

class EvtManager {

  public:

  EvtManager();
  void loopIteration();
  EvtContext *pushContext();
  EvtContext *resetContext();
  EvtContext *popContext();
  EvtContext *currentContext();
  void addListener(EvtListener *lstn);
  void removeListener(EvtListener *lstn);

  private:
  EvtContext *contextStack = 0;
  int contextOffset = 0;
  int contextDepth = 0;
};

// Note - should probably expand the number of available listeners by chaining contexts
class EvtContext {
  public:
  void *data = 0;

  EvtContext();
  void setupContext();
  void loopIteration();
  void addListener(EvtListener *lstn);
  void removeListener(EvtListener *lstn);

  private:
  EvtListener **listeners = 0;
  int listenerCount;
};


class EvtListener {
  public:
  void *extraData = 0; // Anything you want to store here
  EvtAction triggerAction;

  virtual void setupListener();
  virtual bool isEventTriggered();
  virtual bool performTriggerAction(EvtContext *); // return false if I should stop the current chain

  protected:
};

class EvtPinListener : public EvtListener {
  public:
  EvtPinListener();
  EvtPinListener(int pin, EvtAction trigger);
  EvtPinListener(int pin, int debounce, EvtAction action);
  EvtPinListener(int pin, int debounce, bool targetValue, EvtAction action);
  int pin = 0;
  int debounce = 40;  
  bool targetValue = HIGH;
  bool mustStartOpposite = true;
  bool startState;
  unsigned long firstNoticed = 0;

  void setupListener();
  bool isEventTriggered();
};

class EvtTimeListener : public EvtListener {
  public:
  EvtTimeListener();
  EvtTimeListener(unsigned long time, bool multiFire, EvtAction trigger);
  unsigned long millis;
  void setupListener();
  bool isEventTriggered();
  bool performTriggerAction(EvtContext *);
  private:
  unsigned long startMillis;
  bool multiFire = false;
  int numFires = 0;
};

//Added to handle time listeners in microsecond range
class EvtTimeMicroListener : public EvtListener {
  public:
  EvtTimeMicroListener();
  EvtTimeMicroListener(unsigned long time_in_micros, bool multiFire, EvtAction trigger);
  unsigned long micros;
  void setupListener();
  bool isEventTriggered();
  bool performTriggerAction(EvtContext *);
  private:
  unsigned long startMicros;
  bool multiFire = false;
  int numFires = 0;
};

#define USE_EVENTUALLY_LOOP(mgr) void loop() { mgr.loopIteration(); }

#endif




/*  "Eventually.cpp"    */

/*
 * This program is copyright 2016 by Jonathan Bartlett.  See LICENSING
 * file for information on usage (MIT License).  
 * Be sure to check out my books at www.bplearning.net!
 */

//#include <Eventually.h>

/* *** EVT MANAGER *** */
EvtManager::EvtManager() {
  contextStack = new EvtContext[EVENTUALLY_MAX_CONTEXTS];
  contextStack[contextOffset].setupContext();
}

void EvtManager::addListener(EvtListener *lstn) {
  contextStack[contextOffset].addListener(lstn);
}

void EvtManager::removeListener(EvtListener *lstn) {
    contextStack[contextOffset].removeListener(lstn);
}

EvtContext *EvtManager::currentContext () {
  return &contextStack[contextOffset];
}

EvtContext *EvtManager::pushContext() {
  contextOffset++;
  contextStack[contextOffset].setupContext();
  return &contextStack[contextOffset];
}

EvtContext *EvtManager::resetContext() {
  contextStack[contextOffset].setupContext();
  return &contextStack[contextOffset];
}

EvtContext *EvtManager::popContext() {
  contextOffset--;
  return &contextStack[contextOffset];
}

void EvtManager::loopIteration() {
  contextStack[contextOffset].loopIteration();
}

/* *** EVT CONTEXT *** */

EvtContext::EvtContext() {
}

void EvtContext::loopIteration() {
  for(int i = 0; i < listenerCount; i++) {
    if(listeners[i]) { // Make sure it isn't deleted  
      if(listeners[i]->isEventTriggered()) { // If we are triggered, run the action
        if(listeners[i]->performTriggerAction(this)) { // If the action returns true, stop the chain
          return;
        }
      }
    }
  }
}

void EvtContext::setupContext() {
  if(data){
    delete data;
  }
  if(listeners) {
    for(int i = 0; i < listenerCount; i++) {
      if(listeners[i]) {
        delete listeners[i];
      }
    }
    delete listeners;
  }

  listeners = new EvtListener *[EVENTUALLY_MAX_LISTENERS];
  listenerCount = 0;
}
  
void EvtContext::addListener(EvtListener *lstn) {
  for(int i = 0; i < listenerCount; i++) { // Try to add in empty slot
    if(listeners[listenerCount] == 0) { 
      listeners[listenerCount] = lstn;
      return;
    }
  }

  // No empty slot, just add it
  listeners[listenerCount] = lstn;
  lstn->setupListener();
  listenerCount++;
}

void EvtContext::removeListener(EvtListener *lstn) {
  for(int i = 0; i < listenerCount; i++) {
    if(listeners[i] == lstn) {
      delete lstn;
      listeners[i] = 0;      
    }
  }
}

/* *** EVT LISTENER *** */

void EvtListener::setupListener() {
  
}

bool EvtListener::isEventTriggered() {
  return false;
}

bool EvtListener::performTriggerAction(EvtContext *ctx) {
  return (*triggerAction)(this, ctx);
}

/* *** EVT PIN LISTENER *** */

EvtPinListener::EvtPinListener() {
  
}

EvtPinListener::EvtPinListener(int pin, int debounce, bool targetValue, EvtAction action) {
  this->pin = pin;
  this->debounce = debounce;
  this->targetValue = targetValue;
  this->triggerAction = action;
}

EvtPinListener::EvtPinListener(int pin, int debounce, EvtAction action) {
  this->pin = pin;
  this->debounce = debounce;
  this->triggerAction = action;
}

EvtPinListener::EvtPinListener(int pin, EvtAction action) {
  this->pin = pin;
  this->triggerAction = action;
}

void EvtPinListener::setupListener() {
  startState = digitalRead(pin);
}

bool EvtPinListener::isEventTriggered() {
  bool val = digitalRead(pin); 

  // Debounce check if we were triggered earlier
  if(firstNoticed) {
    unsigned long curMillis = millis();
    if(curMillis > firstNoticed + debounce) {
      // Debounce time expired, check again

      // Reset Watcher
      firstNoticed = 0;

      // Check
      if(val == targetValue) {
        return true;
      } else {
        return false;
      }
    } else {
      // Waiting for debouncer to finish
      return false;
    }
  }
  
  if(mustStartOpposite && (startState == targetValue)) {
    /* This is a waiting loop to wait for the pin to change to the opposite state before sensing */
    /* Q - do I need to debounce mustStartOpposite? */
    if(val == startState) {
      // Do nothing
    } else {
      startState = val;
    }

    return false;
  } else {
    /* This is the real deal */
    if(val == targetValue) {
      if(debounce == 0) {
        return true;
      } else {
        firstNoticed = millis();
        return false;
      }
    } else {
      return false;
    }
  }
}

/* *** EVT TIME LISTENER *** */
EvtTimeListener::EvtTimeListener() {
  
}

EvtTimeListener::EvtTimeListener(unsigned long time, bool multiFire, EvtAction t) {
  this->millis = time;
  this->triggerAction = t;
  this->multiFire = multiFire;
}

void EvtTimeListener::setupListener() {
  startMillis = ::millis();
}

bool EvtTimeListener::isEventTriggered() {
  unsigned long curTime = ::millis();
  bool shouldFire = false;
  if(curTime >= startMillis) {
    /* Normal */
    if(curTime - startMillis > this->millis) {
      shouldFire = true;
    }
  } else {
    /* Wrap-Around! */
    if(((ULONG_MAX - startMillis) + curTime) > this->millis) {
      shouldFire = true;
    }
  }

  return shouldFire;  
}

bool EvtTimeListener::performTriggerAction(EvtContext *c) {
  bool returnval = (*triggerAction)(this, c);
  if(multiFire) {
    // On multifire, setup to receive the event again
    setupListener();
    // On multifire, we shouldn't stop the event chain no matter what, since we are just restarting in this context
    return false;
  } else {
    return returnval;
  }
}

/**/
//Added to handle time listeners in microsecond range
/* *** EVT TIME MICRO LISTENER *** */
EvtTimeMicroListener::EvtTimeMicroListener() {
  
}

EvtTimeMicroListener::EvtTimeMicroListener(unsigned long time_in_micros, bool multiFire, EvtAction t) {
  this->micros = time_in_micros;
  this->triggerAction = t;
  this->multiFire = multiFire;
}

void EvtTimeMicroListener::setupListener() {
  startMicros = ::micros();
}

bool EvtTimeMicroListener::isEventTriggered() {
  unsigned long curTime = ::micros();
  bool shouldFire = false;
  if(curTime >= startMicros) {
    /* Normal */
    if(curTime - startMicros > this->micros) {
      shouldFire = true;
    }
  } else {
    /* Wrap-Around! */
    if(((ULONG_MAX - startMicros) + curTime) > this->micros) {
      shouldFire = true;
    }
  }

  return shouldFire;  
}

bool EvtTimeMicroListener::performTriggerAction(EvtContext *c) {
  bool returnval = (*triggerAction)(this, c);
  if(multiFire) {
    // On multifire, setup to receive the event again
    setupListener();
    // On multifire, we shouldn't stop the event chain no matter what, since we are just restarting in this context
    return false;
  } else {
    return returnval;
  }
}




/* Program */

#define BUZZER1_PIN     8
#define BUZZER2_PIN     9
//when adding a thrid buzzer, the pitch dropped a little & it got wobbly
#define BUZZER3_PIN     10
#define BUTTON_PIN      2

bool playMusic = false;
EvtManager mgr;
bool pin1State = LOW;
bool pin2State = LOW;
bool pin3State = LOW;

//create a square wave on first pin
bool PlayTone1(){
    pin1State = !pin1State;
    digitalWrite(BUZZER1_PIN, pin1State);
    
    return true;
}

//create a square wave on second pin
bool PlayTone2(){
    pin2State = !pin2State;
    digitalWrite(BUZZER2_PIN, pin2State);
    
    return true;
}

//create a square wave on third pin
bool PlayTone3(){
    pin3State = !pin3State;
    digitalWrite(BUZZER3_PIN, pin3State);
    
    return true;
}



//switch whether a tone is being played or not
bool ToggleTone(){
    //reset the context & add back the pin listener for the button
    mgr.resetContext();
    mgr.addListener(new EvtPinListener(BUTTON_PIN, (EvtAction)ToggleTone));
    
    //if a tone is not currently playing, add a timer to play the tone
    if(!playMusic){
        mgr.addListener(new EvtTimeMicroListener(1136, true, (EvtAction)PlayTone1));
        mgr.addListener(new EvtTimeMicroListener(758, true, (EvtAction)PlayTone2));
        mgr.addListener(new EvtTimeMicroListener(758, true, (EvtAction)PlayTone3));
    }
    //otherwise, stop playing the tone
    else{
        digitalWrite(BUZZER1_PIN, LOW);
        digitalWrite(BUZZER2_PIN, LOW);
        digitalWrite(BUZZER3_PIN, LOW);
    }

   //adjust playMusic to match what's currently happening
    playMusic = !playMusic;
    return false;
}

void setup() {
  pinMode(BUZZER1_PIN, OUTPUT);
  pinMode(BUZZER2_PIN, OUTPUT);
  pinMode(BUZZER3_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  mgr.addListener(new EvtPinListener(BUTTON_PIN, (EvtAction)ToggleTone));
}

USE_EVENTUALLY_LOOP(mgr)
