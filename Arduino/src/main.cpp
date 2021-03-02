#include <Arduino.h>
#include <MUX.h>

#define C1        0x18
#define C2        0x24
#define C3        0x30
#define C4        0x3C
#define Pin_C1    10

#define MUX_S0        7
#define MUX_S1        6
#define MUX_S2        5
#define MUX_S3        4
#define MUX_CommonIO  3

// Holds incoming values from 74HC4067
bool muxValues[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {

  // Initialize Serial for MIDI Communication
  // Serial.begin(31250);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  // Initialize MUX to read Keyboard values
  MUX_Initialize(MUX_CommonIO, MUX_S0, MUX_S1, MUX_S2, MUX_S3);
}

void loop() {
  // checkButton();
  MUX_GetAllChannels(muxValues);
}

// void checkButton()
// {
//   if(digitalRead(Pin_C1) == LOW)
//   {
//     playNotes();
//   }
// }

// void playNotes() {
//   if(Serial.availableForWrite() > 0)
//   {
//     noteOn(0x90, C2, 0x50);
//     delay(500);
//     noteOn(0x90, C2, 0x00);
//   }
// }

// // Plays a MIDI note
// void noteOn(int cmd, int pitch, int velocity)
// {
//   Serial.write(cmd);
//   Serial.write(pitch);
//   Serial.write(velocity);
// }