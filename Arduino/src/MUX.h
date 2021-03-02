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

#define MUX_CHANNELS_AMOUNT      16

// External reference for Selected Pins from 74HC4067
typedef enum MUX_Pins
{
    MUX_I0,
    MUX_I1,
    MUX_I2,
    MUX_I3,
    MUX_I4,
    MUX_I5,
    MUX_I6,
    MUX_I7,
    MUX_I8,
    MUX_I9,
    MUX_I10,
    MUX_I11,
    MUX_I12,
    MUX_I13,
    MUX_I14,
    MUX_I15
} MUX_Pins;

typedef struct MUX_Context
{
    int commonIO;
    int s0;
    int s1;
    int s2;
    int s3;
    int enablePin;
} MUX_Context;

// Initialize essential pins from 74HC4067
void MUX_Initialize(int commonIO, int enable, int s0, int s1, int s2, int s3);

// Select channel on 74HC4067
void MUX_SelectChannel(int channel);

// Get current value from all channels
void MUX_GetAllChannels(bool *pinValues);