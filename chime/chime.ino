/*  Example of playing a sampled sound,
    using Mozzi sonification library.

    Demonstrates one-shot samples scheduled
    with EventDelay.

    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
    check the README or http://sensorium.github.com/Mozzi/

    Mozzi documentation/API
    https://sensorium.github.io/Mozzi/doc/html/index.html

    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Tim Barrass 2012, CC by-nc-sa.
*/

#include <MozziGuts.h>
#include <Sample.h> // Sample template
#include "chime_int8.h"
#include <EventDelay.h>

// use: Sample <table_size, update_rate> SampleName (wavetable)
Sample <CHIME_NUM_CELLS, AUDIO_RATE> aSample(CHIME_DATA);

// for scheduling sample start
EventDelay kTriggerDelay;

void setup(){
  startMozzi();
  aSample.setFreq((float) CHIME_SAMPLERATE / (float) CHIME_NUM_CELLS); // play at the speed it was recorded
  kTriggerDelay.set(5000); // 5000 msec countdown, within resolution of CONTROL_RATE
}

void updateControl(){
  if(kTriggerDelay.ready()){
    aSample.start();
    kTriggerDelay.start();
  }
}

int updateAudio(){
  return (int) aSample.next();
}

void loop(){
  audioHook();
}
