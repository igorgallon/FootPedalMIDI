#include <Config.h>
#include <Arduino.h>

// #include <LiquidCrystal_I2C.h>
#include <MUX/MUX.h>
#include <MIDI/MIDI.h>
#include <IRremote.h>
#include <RemoteControl/RemoteControl.h>

// Holds incoming values from 74HC4067
bool muxValues[KEYS_AMOUNT] = { 0 };
MUX mux;
MIDI midi;
RemoteControl remoteCtr(&IrReceiver);
RemoteControl::Key pressedKey = RemoteControl::Key::Unknown;

// LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setup()
{
  pinMode(BUZZER_OUT, OUTPUT);

  // Initialize Serial for MIDI Communication
  midi.initialize();

  // Initialize multiplexer 74HC4067 to obtain information from all 13 keys
  mux.initialize(MUX_CommonIO, MUX_S0, MUX_S1, MUX_S2, MUX_S3);

  // Initialize IR Remote Controller
  remoteCtr.initialize(IR_RCV_PIN);
}

void beepTone()
{
  tone(BUZZER_OUT, 784);
  delay(100);
  noTone(BUZZER_OUT);
}

void checkRemoteControl()
{
  // Check if a key from Remote Controller is pressed
  if(remoteCtr.receive(&pressedKey))
  {
    if(pressedKey == RemoteControl::Key::Num1)
    {
      midi.setInstrument(MIDI::DrawbarOrgan);
      beepTone();
    }
    else if(pressedKey == RemoteControl::Key::Num2)
    {
      midi.setInstrument(MIDI::GrandPiano);
      beepTone();
    }
    if(pressedKey == RemoteControl::Key::Right)
    {
      midi.increaseVolume();
      beepTone();
    }
    else if(pressedKey == RemoteControl::Key::Left)
    {
      midi.decreaseVolume();
      beepTone();
    }
    else if(pressedKey == RemoteControl::Key::Super)
    {
      midi.setSustain();
      beepTone();
    }
    else if(pressedKey == RemoteControl::Key::Clock)
    {
      midi.initialize();
      beepTone();
    }
  }
}

void runKeyboard()
{
  // Identify which key from keyboard is pressed
  mux.getAllChannels(muxValues, KEYS_AMOUNT);
  
  // Send PLAY or STOP MIDI Command
  for(int i = 0; i < KEYS_AMOUNT; i++)
    if(muxValues[i] == true)
      midi.playNote(i);
    else
      midi.stopNote(i);
}

void loop()
{
  // Check if any recognized key from Remote Controller is pressed
  checkRemoteControl();
  // Run MIDI keyboard mechanism
  runKeyboard();
}