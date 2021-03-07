#include <Arduino.h>

// #include <LiquidCrystal_I2C.h>
// #include <IRremote.h>

#include <MUX/MUX.h>
#include <MIDI/MIDI.h>

#define KEYS_AMOUNT   13
#define MUX_S0        7
#define MUX_S1        6
#define MUX_S2        5
#define MUX_S3        4
#define MUX_CommonIO  3
#define MUX_Enable    2

// Holds incoming values from 74HC4067
bool muxValues[13] = {0};

MUX mux;
MIDI midi;
// IRrecv irrecv(11);
// LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  // Initialize Serial for MIDI Communication
  midi.initialize();
  midi.setChannel(0);
  midi.setHarmonyMode(MIDI::Monophonic);

  // Initialize multiplexer 74HC4067 to obtain information from all 13 keys
  mux.initialize(MUX_CommonIO, MUX_Enable, MUX_S0, MUX_S1, MUX_S2, MUX_S3);

  // irrecv.enableIRIn();
  // lcd.init();

  // Initialize MUX to read Keyboard values
  // MUX_Initialize(MUX_CommonIO, MUX_Enable, MUX_S0, MUX_S1, MUX_S2, MUX_S3);
}

void loop()
{

  midi.setInstrument(MIDI::DrawbarOrgan);
  midi.setSustain(false);

  midi.playNote(MIDI::C2);
  delay(1000);
  midi.playNote(MIDI::D2);
  delay(1000);
  midi.playNote(MIDI::E2);
  delay(1000);
  midi.playNote(MIDI::F2);
  delay(1000);
  midi.playNote(MIDI::G2);
  delay(1000);

}