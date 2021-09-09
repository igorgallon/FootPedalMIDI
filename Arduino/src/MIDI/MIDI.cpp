/*
 * MIDI.cpp
 *
 *  Created on: 03/03/2021
 *      Author: Igor Gallon
 */

#include <MIDI/MIDI.h>

MIDI::MIDI()
{
    // Do nothing
}

void MIDI::initialize()
{
    // Initialize Serial Communication using
    // Baud Rate specified by MIDI protocol
    Serial.begin(BAUD_RATE);
    
    for(int i = 0; i < 13; i++)
        PlayingNote[i] = false;

    // Set to default configurations
    IsSustainEnable = true;
    setChannel(0);
    setInstrument(DrawbarOrgan);
    setVolume(Vol4f);
    setHarmonyMode(Monophonic);
    setSustain();
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

void MIDI::setVolume(VolumeLevels volume)
{
    if(volume >= Vol4p && volume <= Vol4f)
    {
        VolumeIndex = volume;

        Serial.write(Controller|Channel);
        Serial.write(VolumeLevel);
        Serial.write(Volumes[VolumeIndex].value);
    }
}

void MIDI::increaseVolume()
{
    int newVolume = 0;

    if(VolumeIndex < Vol4f)
    {
        newVolume = VolumeIndex + 1;
        setVolume((MIDI::VolumeLevels)newVolume);
    }
}

void MIDI::decreaseVolume()
{
    int newVolume = 0;

    if(VolumeIndex > Vol4p)
    {
        newVolume = VolumeIndex - 1;
        setVolume((MIDI::VolumeLevels)newVolume);
    }
}

void MIDI::setSustain()
{
    SustainValue sustainVal;

    IsSustainEnable = !IsSustainEnable;

    if(IsSustainEnable)
        sustainVal = SustainOn;
    else
        sustainVal = SustainOff;

    // Send Controller Message
    Serial.write(Controller|Channel);
    Serial.write(SustainPedal);
    Serial.write(sustainVal);
}

void MIDI::setHarmonyMode(Harmony mode)
{
    HarmonyMode = mode;
}

void MIDI::playNote(int index)
{
    Pitch pitch = Notes[index];

    if(pitch >= C2 && pitch <= C3)
    {
        if(HarmonyMode == Monophonic && LastPlayedPitch != NoPitch)
            stopNote(LastPlayedPitch);

        if(!PlayingNote[index])
        {
            // Serial.print("Play note: ");
            // Serial.println(NotesName[index]);
            Serial.write(NoteOn|Channel);
            Serial.write(pitch);
            Serial.write(Volumes[VolumeIndex].value);
            LastPlayedPitch = pitch;

            PlayingNote[index] = true;
        }
    }
}

void MIDI::stopNote(int index)
{
    Pitch pitch = Notes[index];

    if(pitch >= C2 && pitch <= C3)
    {
        if(PlayingNote[index])
        {
            Serial.write(NoteOff|Channel);
            Serial.write(pitch);
            Serial.write(Volumes[VolumeIndex].value);
            PlayingNote[index] = false;
        }
    }
}