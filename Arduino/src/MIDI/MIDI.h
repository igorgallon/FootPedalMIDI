/*
 * MIDI.h
 *
 *  Created on: 03/03/2021
 *      Author: Igor Gallon
 * 
 * MIDI Messages Controller
 */

#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>

class MIDI
{
    public:
        const int MIDI_KEYS_AMOUNT = 13;
        enum Command
        {
            NoteOff         = 0x80,
            NoteOn          = 0x90,
            Controller      = 0xB0,
            ProgramChange   = 0xC0,
            SystemMessage   = 0xF0
        };

        // Specify the Controller (0xB0) command
        enum ControllerNumber
        {
            BankMSB         = 0x00,
            BankLSB         = 0x20,
            VolumeLevel     = 0x07,
            SustainPedal    = 0x40,
        };

        enum SustainValue
        {
            SustainOff      = 0x00,
            SustainOn       = 0x20
        };

        enum Pitch
        {
            NoPitch = 0x00,
            C2      = 0x24,     // Do2
            C2S     = 0x25,     // Do#/Reb
            D2      = 0x26,     // Re
            D2S     = 0x27,     // Re#/Mib
            E2      = 0x28,     // Mi
            F2      = 0x29,     // Fa
            F2S     = 0x2A,     // Fa#/Solb
            G2      = 0x2B,     // Sol
            G2S     = 0x2C,     // Sol#/Lab
            A2      = 0x2D,     // La
            A2S     = 0x2E,     // La#/Sib
            B2      = 0x2F,     // Si
            C3      = 0x30      // Do3
        };

        enum Voices
        {
            GrandPiano          = 0x00,
            BrightPiano         = 0x01,
            ElectricGrandPiano  = 0x02,
            HonkyTonkPiano      = 0x03,
            ElectricPiano1      = 0x04,
            ElectricPiano2      = 0x05,
            Harpischord         = 0x06,
            Clavi               = 0x07,
            DrawbarOrgan        = 0x10,
            PercussiveOrgan     = 0x11,
            RockOrgan           = 0x12,
            ChurchOrgan         = 0x13,
            ReedOrgan           = 0x14
        };
        
        enum VolumeLevels
        {
            Vol4p,
            Vol3p,
            Vol2p,
            Vol1p,
            Volmp,
            Volmf,
            Volf ,
            Vol2f,
            Vol3f,
            Vol4f
        };

        typedef struct
        {
            VolumeLevels volume;
            int value; 
        } Volume;

        const Volume Volumes [10] = { 
            {Vol4p, 0x08},
            {Vol3p, 0x14},
            {Vol2p, 0x1F},
            {Vol1p, 0x2A},
            {Volmp, 0x35},
            {Volmf, 0x40},
            {Volf,  0x50},
            {Vol2f, 0x60},
            {Vol3f, 0x70},
            {Vol4f, 0x7F}
        };
        
        enum Harmony
        {
            Monophonic,
            Polyphonic
        };

        const Pitch Notes[13] = { C2, C2S, D2, D2S, E2, F2, F2S, G2, G2S, A2, A2S, B2, C3 };
        
        const char* NotesName[13] = { "Do2", "Do2#", "Re", "Re#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si", "Do3" };

        bool PlayingNote[13] = { 0 };

        // Constructor
        MIDI();
        void initialize();
        void setChannel(int channel);
        void setInstrument(int instrument);
        void setVolume(VolumeLevels volume);
        void increaseVolume();
        void decreaseVolume();
        void setSustain();
        void setHarmonyMode(Harmony mode);

        void playNote(int index);
        void stopNote(int index);

    private:
        const int BAUD_RATE = 31250;
        
        int Channel = 0;
        int Instrument;
        int VolumeIndex;
        bool IsSustainEnable;
        int HarmonyMode;

        Pitch LastPlayedPitch = NoPitch;
};

#endif