#ifndef SORTLEDS_H
#define SORTLEDS_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
//DEFINES
//define attiny2313 ports
#define MAX_PORT   PORTD		//first max7219 driven by PORT D
#define MAX_DDR    DDRD

#define MAX2_PORT  PORTB
//some slang 
#define sbi(a, b) (a) |= (1 << (b));  //my preferred way of setting or clearing one bit at a time
#define cbi(a, b) (a) &= ~(1 << (b)); 

//define pins for MAX1
#define data PD0      //Data pin (DS) pin location
#define clock PD1      //Shift Clock (SH_CP) pin location 
#define latch PD2      //Store Clock (ST_CP) pin location
//The second max's pins
#define data2  PB0	
#define clock2 PB1
#define latch2 PB2
/*GLOBAL VARIABLES*/
//define the registers of the max7219
const uint8_t max7219_reg_decodeMode  = 0x09;
const uint8_t max7219_reg_intensity   = 0x0a;  //intensity determined by the low nibble.  0xXa is a duty cycle of 21/32
const uint8_t max7219_reg_scanLimit   = 0x0b;
const uint8_t max7219_reg_shutdown    = 0x0c;
const uint8_t max7219_reg_displayTest = 0x0f;

const uint8_t columns[] = {128,64,32,16,8,4,2,1}; //an array of column indices, easier this way since columns are called by 2^n
uint8_t A[7];  //the array to be filled with random integers from 0 to 8 and then sorted
uint8_t temp[sizeof(A)];
uint8_t matrix[7][8];  // a 2d matrix we use to help update the lighting function

//extern uint8_t A[];
//*****FUNCTION PROTOTYPES*********
void putByte(uint8_t, char);
void maxSingle(uint8_t, uint8_t, char);
void MAXInit(void);
void randInts(void);
void lightCols(void);
void makeMatrix(void);
void updateMatrix(void);


#endif
