/*
 * Config.h
 *
 *  Created on: 24/05/2021
 *      Author: Igor Gallon
 * 
 * Declare the map of pins used by Arduino, constants
 * and global definitions regarding to initial setup.
 */

/* PINs */
extern const int MUX_S0       = 5;
extern const int MUX_S1       = 6;
extern const int MUX_S2       = 4;
extern const int MUX_S3       = 3;
extern const int MUX_CommonIO = 2;
extern const int MIDI_OUT     = 1;
extern const int IR_RCV_PIN   = 7;
extern const int BUZ_OUT      = 9;

/* MIDI Constants */
extern const int KEYS_AMOUNT  = 13;

/* LCD Constants */
extern const int LCD_ADDR     = 0x27;
extern const int LCD_COLS     = 20;
extern const int LCD_ROWS     = 4;
