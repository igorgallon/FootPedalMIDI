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
    {LOW,LOW,LOW,LOW}, // Channel 0
    {HIGH,LOW,LOW,LOW}, // Channel 1
    {LOW,HIGH,LOW,LOW}, // Channel 2
    {HIGH,HIGH,LOW,LOW}, // Channel 3
    {LOW,LOW,HIGH,LOW}, // Channel 4
    {HIGH,LOW,HIGH,LOW}, // Channel 5
    {LOW,HIGH,HIGH,LOW}, // Channel 6
    {HIGH,HIGH,HIGH,LOW}, // Channel 7
    {LOW,LOW,LOW,HIGH}, // Channel 8
    {HIGH,LOW,LOW,HIGH}, // Channel 9
    {LOW,HIGH,LOW,HIGH}, // Channel 10
    {HIGH,HIGH,LOW,HIGH}, // Channel 11
    {LOW,LOW,HIGH,HIGH}, // Channel 12
    {HIGH,LOW,HIGH,HIGH}, // Channel 13
    {LOW,HIGH,HIGH,HIGH}, // Channel 14
    {HIGH,HIGH,HIGH,HIGH}  // Channel 15
};

void MUX_Initialize(int commonIO, int enable, int s0, int s1, int s2, int s3)
{
    memset(&context, 0x00, sizeof(context));
    context.commonIO = commonIO;
    context.s0 = s0;
    context.s1 = s1;
    context.s2 = s2;
    context.s3 = s3;

    pinMode(commonIO, OUTPUT);
    pinMode(enable, OUTPUT);
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    
    digitalWrite(enable, LOW);
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
    for(int i = 0; i < 6; i++)
    {
        // Choose a channel on the 74HC4067
        MUX_SelectChannel(i);
        // Read the value on that channel and store in array
        digitalWrite(context.commonIO, HIGH);
        delay(250);
        digitalWrite(context.commonIO, LOW);
        delay(250);
    }
}