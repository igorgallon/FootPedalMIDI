/*
 * MUX.cpp
 *
 *  Created on: 02/03/2021
 *      Author: Igor Gallon
 */

#include <MUX/MUX.h>

MUX::MUX()
{
    // Do nothing
}

void MUX::initialize(int commonIO, int s0, int s1, int s2, int s3)
{
    CommonIO = commonIO;
    S0 = s0;
    S1 = s1;
    S2 = s2;
    S3 = s3;

    pinMode(CommonIO, INPUT);
    // pinMode(EnablePin, OUTPUT);
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    
    // digitalWrite(EnablePin, LOW);
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
}

// Select pin on 74HC4067
void MUX::selectChannel(int channel)
{
    digitalWrite(S0, ChannelSelector[channel][0]);
    digitalWrite(S1, ChannelSelector[channel][1]);
    digitalWrite(S2, ChannelSelector[channel][2]);
    digitalWrite(S3, ChannelSelector[channel][3]);
}

// Get current value from all Pins and return in <channelValues> array
void MUX::getAllChannels(bool *channelValues, int length)
{
    int len = (length <= CHANNELS_AMOUNT) ? length : CHANNELS_AMOUNT;

    for(int i = 0; i < len; i++)
    {
        // Choose a channel on the 74HC4067
        selectChannel(i);
        // Read the value on that channel and store in array
        channelValues[i] = digitalRead(CommonIO);
    }
    delay(100);
}