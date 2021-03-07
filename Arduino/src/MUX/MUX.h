/*
 * MUX.h
 *
 *  Created on: 02/03/2021
 *      Author: Igor Gallon
 * 
 * 74HC4067 MUX (16-to-1)
 * See truth table on page 2 of TI 74HC4067 data sheet
 * Connect 74HC4067 S0~S3 to Arduino D7~D4 respectively
 * Connect 74HC4067 pin 1 to Arduino D3
 */

#include <Arduino.h>

class MUX
{
    public:
    // Constructor
    MUX();
    // Initialize essential pins from 74HC4067
    void initialize(int commonIO, int enable, int s0, int s1, int s2, int s3);
    // Select channel on 74HC4067
    void selectChannel(int channel);
    // Get current value from all Pins and return in <channelValues> array
    void getAllChannels(bool *channelValues, int length);

    private:
        int CommonIO;       // Common I/O pin
        int EnablePin;      // Enable pin
        int S0, S1, S2, S3; // Selector pins

        const int CHANNELS_AMOUNT = 16;

        // Control pins output table (See TI 74HC4067 data sheet)
        const int ChannelSelector[16][4] = {
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
};