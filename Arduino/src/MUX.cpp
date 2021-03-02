/*
 * MUX.cpp
 *
 *  Created on: 02/03/2021
 *      Author: Igor Gallon
 */

#include <MUX.h>

static MUX_Context context;

// Control pins output table (See TI 74HC4067 data sheet)
const int muxChannel[MUX_CHANNELS_AMOUNT][4] = {
    {0,0,0,0}, // Channel 0
    {1,0,0,0}, // Channel 1
    {0,1,0,0}, // Channel 2
    {1,1,0,0}, // Channel 3
    {0,0,1,0}, // Channel 4
    {1,0,1,0}, // Channel 5
    {0,1,1,0}, // Channel 6
    {1,1,1,0}, // Channel 7
    {0,0,0,1}, // Channel 8
    {1,0,0,1}, // Channel 9
    {0,1,0,1}, // Channel 10
    {1,1,0,1}, // Channel 11
    {0,0,1,1}, // Channel 12
    {1,0,1,1}, // Channel 13
    {0,1,1,1}, // Channel 14
    {1,1,1,1}  // Channel 15
};

void MUX_Initialize(int commonIO, int s0, int s1, int s2, int s3)
{
    memset(&context, 0x00, sizeof(context));
    context.commonIO = commonIO;
    context.s0 = s0;
    context.s1 = s1;
    context.s2 = s2;
    context.s3 = s3;

    pinMode(commonIO, OUTPUT);

    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    
    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
}

// Select pin on 74HC4067
void MUX_SelectChannel(int channel)
{
    digitalWrite(context.s0, muxChannel[channel][0]);
    digitalWrite(context.s1, muxChannel[channel][1]);
    digitalWrite(context.s2, muxChannel[channel][2]);
    digitalWrite(context.s3, muxChannel[channel][3]);
}

// Get current value from all Pins
void MUX_GetAllChannels(bool *pinValues)
{
    // for(int i = 0; i < MUX_CHANNELS_AMOUNT; i++)
    // {
    //     // Choose a channel on the 74HC4067
    //     MUX_SelectChannel(i);
    //     // Read the value on that channel and store in array
    //     pinValues[i] = digitalRead(context.commonIO);
    // }
    for(int i = 0; i < 5; i++)
    {
        // Choose a channel on the 74HC4067
        MUX_SelectChannel(i);
        // Read the value on that channel and store in array
        digitalWrite(context.commonIO, HIGH);
        delay(1000);
        digitalWrite(context.commonIO, LOW);
        delay(500);
    } 
}