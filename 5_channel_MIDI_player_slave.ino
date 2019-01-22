/**
 * \file 5_channel_MIDI_player_slave.ino
 * \author Hydragon516 <hydragon516@gmail.com>
 * \date 9 January 2019
 *
 * \brief Send and run MIDI signals to Arduino through MIDI communications.
 *
 * \section License
 * The author has placed this work in the Public Domain, thereby relinquishing
 * all copyrights. Everyone is free to use, modify, republish, sell or give away
 * this work without prior consent from anybody.
 */

#include <Wire.h>
#include <math.h>
 
#define BUZZ_PIN 4

#define your_midi_channel 0 // Please chane this value. (channel number start with 0)
#define your_midi_address 8 // Please chane this value. (I2C address should same with master adress)

int a = 440;
 
void noteOn(byte channel, float pitch, byte velocity) { 
  if (channel==your_midi_channel){
    float Frequency = (a / 32) * pow(2, float((pitch - 9) / 12)); // Formula to convert pitch to frequency
    tone(BUZZ_PIN, Frequency);
    } 
 
} 
 
void noteOff(byte channel, byte pitch, byte velocity) {  
  if (channel==your_midi_channel){
    noTone(BUZZ_PIN); 
    } 
 
} 
 
 
void controlChange(byte channel, byte control, byte value) { 
 
}  
 
byte Midi[4];
 
void setup() {
  Wire.begin(your_midi_address);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}
 
void loop() {
}
 
void receiveEvent(int howMany) {
  for (int i = 0; i < 4; i++) {
    Midi[i]=Wire.read();
  }
  
  switch (Midi[0]) { 
    case 0: 
     break;
       
    case 0x9: 
      noteOn( 
        Midi[1], 
        Midi[2], 
        Midi[3]
      ); 
     break; 
       
    case 0x8: 
      noteOff( 
        Midi[1], 
        Midi[2],
        Midi[3]
      ); 
      break;
        
    case 0xB: 
      controlChange( 
        Midi[1], 
        Midi[2],
        Midi[3] 
      ); 
      break; 
  } 
}
