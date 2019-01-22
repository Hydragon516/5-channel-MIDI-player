/**
 * \file 5_channel_MIDI_player_master.ino
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
#include <MIDIUSB.h> //https://github.com/arduino-libraries/MIDIUSB

//you can change this I2C adress. 
#define channel1_address 8
#define channel2_address 9
#define channel3_address 10
#define channel4_address 11
#define channel5_address 12

void setup() {
  Serial.begin(115200); 
  Wire.begin();
}

void loop() {
  midiEventPacket_t rx = MidiUSB.read();
  byte buffer[4];
  buffer[0]=rx.header;
  buffer[1]=rx.byte1 & 0xF;
  buffer[2]=rx.byte2;
  buffer[3]=rx.byte3;
  for (int i = 0; i <= 3; i++) {
    Serial.print(buffer[i]);
    Serial.print(" ");
  }  
  Serial.println(" ");
  
  Wire.beginTransmission(channel1_address);
  Wire.write(buffer, 4);
  Wire.endTransmission();

  Wire.beginTransmission(channel2_address);
  Wire.write(buffer, 4);
  Wire.endTransmission();

  Wire.beginTransmission(channel3_address);
  Wire.write(buffer, 4);
  Wire.endTransmission();

  Wire.beginTransmission(channel4_address);
  Wire.write(buffer, 4);
  Wire.endTransmission();

  Wire.beginTransmission(channel5_address);
  Wire.write(buffer, 4);
  Wire.endTransmission();
}
