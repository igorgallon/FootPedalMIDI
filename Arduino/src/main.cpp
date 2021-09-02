#include <Arduino.h>

#include <Config.h>
// #include <LiquidCrystal_I2C.h>
// #include <IRremote.h>
#include <MUX/MUX.h>
#include <MIDI/MIDI.h>

// Holds incoming values from 74HC4067
bool muxValues[KEYS_AMOUNT] = {0};

// char* NotesName[13] = { "Do2", "Do2#", "Re", "Re#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si", "Do3" };

MUX mux;
MIDI midi;
// LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setup()
{
  // Serial.begin(9600);
  
  // Initialize Serial for MIDI Communication
  midi.initialize();
  midi.setChannel(0);
  midi.setHarmonyMode(MIDI::Monophonic);
  midi.setInstrument(MIDI::DrawbarOrgan);
  // Initialize multiplexer 74HC4067 to obtain information from all 13 keys
  mux.initialize(MUX_CommonIO, MUX_S0, MUX_S1, MUX_S2, MUX_S3);

  // IrReceiver.begin(IR_RCV_PIN, DISABLE_LED_FEEDBACK);
  // lcd.init();
  // lcd.backlight();
  // lcd.autoscroll();
}

void loop()
{
  // if(IrReceiver.decode())
  // {
  //   Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
  //   //mapping();
  //   delay(300);
  //   IrReceiver.resume(); // Receive the next value
  // }

  mux.getAllChannels(muxValues, KEYS_AMOUNT);

  // Serial.println("-----");
  for(int i = 0; i < KEYS_AMOUNT; i++)
    if(muxValues[i] == true)
      midi.playNote(i);
    else
      midi.stopNote(i);
      
  // Serial.println("-----");
  // delay(500);
  // LCD routine
  // lcd.setCursor(0,0);
  // lcd.print("Amu!");
  // delay(1000);
  // lcd.setCursor(0,1);
  // lcd.print("Eu te amo!!!");
  // delay(1000);
  // lcd.setCursor(0,2);
  // lcd.print("       <3<3<3       ");
  // delay(1000);
  // lcd.clear();
  // delay(1000);
}