/*
 * MIDI.cpp
 *
 *  Created on: 03/03/2021
 *      Author: Igor Gallon
 */

#include <Arduino.h>
#include <MIDI/MIDI.h>

MIDI::MIDI()
{
    Channel     = 0;
    Instrument  = GrandPiano;
    Volume      = Volmf;   
    Sustain     = true;
    HarmonyMode = Polyphonic;
}

void MIDI::initialize()
{
    // Initialize Serial Communication using
    // Baud Rate specified by MIDI protocol
    Serial.begin(BAUD_RATE);
} 


void MIDI::setChannel(int channel)
{
    if(channel >= 0 && channel <= 10)
        Channel = channel;
}

void MIDI::setInstrument(int instrument)
{
    if(instrument >= GrandPiano && instrument <= ReedOrgan)
    {
        Instrument = instrument;

        // Send Program Change Message
        if(Instrument == GrandPiano)
        {
            Serial.write(Controller|Channel);
            Serial.write(BankLSB);
            Serial.write(0x70); // See PSR-E203 Manual
        }
        else
        {
            Serial.write(Controller|Channel);
            Serial.write(BankLSB);
            Serial.write(0x00);
        }

        Serial.write(ProgramChange|Channel);
        Serial.write(Instrument);
    }
}

void MIDI::setVolume(int volume)
{
    if(volume >= Vol4p && volume <= Vol4f)
    {
        Volume = volume;

        Serial.write(Controller|Channel);
        Serial.write(VolumeLevel);
        Serial.write(Volume);
    }
}

void MIDI::setSustain(bool sustain)
{
    if(sustain)
        Sustain = SustainOn;
    else
        Sustain = SustainOff;

    // Send Controller Message
    Serial.write(Controller|Channel);
    Serial.write(SustainPedal);
    Serial.write(Sustain);
}

void MIDI::setHarmonyMode(Harmony mode)
{
    HarmonyMode = mode;
}

void MIDI::playNote(Pitch pitch)
{
    if(pitch >= C2 && pitch <= C3)
    {
        if(HarmonyMode == Monophonic && LastPlayedPitch != NoPitch)
            stopNote(LastPlayedPitch);

        Serial.write(NoteOn|Channel);
        Serial.write(pitch);
        Serial.write(Volume);

        LastPlayedPitch = pitch;
    }
}

void MIDI::stopNote(Pitch pitch)
{
    if(pitch >= C2 && pitch <= C3)
    {
        Serial.write(NoteOff|Channel);
        Serial.write(pitch);
        Serial.write(Volume);
    }
}