/*  This project uses an attiny2313 driving two max7219 led display drivers to make two different
8x8 arrays of leds light up.  Each column of 8 leds represents an index of an array filled with random
numbers from 0 to 8.  One 8x8 array is in a simple rectangular pattern while the other is presented
in eight different groups and in different shapes and will show chase sequences and stuff for visual 
interest.  Began on Dec 1, 2013 by Alex Carmichael (shovelHand)*/
/*Dec. 25:  Merry Christmas, you are out of program space.  I made need to port this to a attiny84 which has 8k space*/
//Feb 13. 2014 just ported it over to an attiny4313 for double the program space.  Now works with merge sort!
/*INCLUDES*/
#include "sortLeds.h"

const uint8_t insertionsrt[] PROGMEM="sort: insertion";
const uint8_t bubblesrt[] PROGMEM="sort: bubble";
const uint8_t selectionsrt[] PROGMEM="sort: selection";
const uint8_t mergesrt[] PROGMEM="sort: merge";

/*FUNCTIONS*/
//control the bitwise specifics of sending serial data to the max7219
void putByte (uint8_t value, char val){
	if(val == 1){
	uint8_t i = 8;
	uint8_t mask;
	while(i > 0){
		mask = 0x01 << (i -1);
		cbi (MAX_PORT, clock);//...tick
		if(value & mask){
	 		sbi(MAX_PORT, data);
	 	}
	else{
		cbi(MAX_PORT, data);
		}
	 sbi(MAX_PORT, clock); //tock
	 --i;
	 }
	 }
}

//update the leds by sending a byte to the max7219
void maxSingle(uint8_t reg, uint8_t col, char val){
	if(val ==1){		//if we want to pass data to the first max7219
	cbi(MAX_PORT, latch);  //set latch low, start new byte
	putByte(reg, 1);		//which register?
	putByte(col, 1);		//which column?
	sbi(MAX_PORT, latch);  //latch up, parallel data out
	}
	}
//	initialize the MAX7219
void MAXInit(){
	//set the concerned pins as outputs
   sbi(MAX_DDR, data);
   sbi(MAX_DDR, clock);//first one 
   sbi(MAX_DDR, latch);


	//set modes
  maxSingle(max7219_reg_scanLimit, 0x07, 1);      
  maxSingle(max7219_reg_decodeMode, 0x00, 1);  // using an led matrix (not digits)
  maxSingle(max7219_reg_shutdown, 0x01, 1);    // not in shutdown mode
  maxSingle(max7219_reg_displayTest, 0x00, 1); // no display test.  If this is passed the value 0x01, it forces every led to be on. 
  maxSingle(max7219_reg_intensity, 0x08 & 0x0f, 1);    // the first 0x0f is the value you can set
  // range: 0x00 to 0x0f 

  maxSingle(max7219_reg_scanLimit, 0x07, 2);      
  maxSingle(max7219_reg_decodeMode, 0x00, 2);  
  maxSingle(max7219_reg_shutdown, 0x01, 2);    
  maxSingle(max7219_reg_displayTest, 0x00, 2);  
  maxSingle(max7219_reg_intensity, 0x08 & 0x0f, 2);    
}

//fill the array to be sorted with random integers
void randInts(){
	for (int i = 0; i < sizeof(A); i++){
		A[i] = 0;
		A[i] = rand() / (RAND_MAX / 9);
	}
	updateMatrix();
}


/*for every led lit in a row, we have to add its row register value to the to the second argument passed to maxSingle. For  
example, if we want to light the leds in the first row and first column (whose index value is 128), the third column (32)
and the  fifth (8), then we need to call then maxSingle is called with 1 as it's first arg and (128+32+8) as its second.  
making three calls to leds in the same row just overwrites the last call, turning the previous led off.*/
//light the appropriate leds based on the number of each index of A
void lightCols(){
	for(int j = 0; j < 8; j++){
		int ledsInRow = 0;				
		for (int i = 0; i < sizeof(A); i ++){		   //for each column...
			if(matrix[i][j] == 1){			   //if the led in the jth row and the ith column is to be lit... 
			ledsInRow += columns[i];           //then add the column's register number to the second argument of maxSingle		
			}
	
			maxSingle(j+1 , ledsInRow, 1);		   //leds are lit row by row
			maxSingle(j+1 , ledsInRow, 2);
		}
			
	}//end for loop
}

//turn the random integer indices of A into a grid matrix of ones and zeros to help with updating the led matrix.
void makeMatrix(){
	//reset the matrix to all zeros		so there's no overlap from the last iterationh
	for(int i = 0; i < sizeof(A); i++){
		for (int j = 0; j < 8; j++){
		matrix[i][j] = 0;
		}
	}
	for(int i = 0; i < sizeof(A); i++){		//go through one column at a time
	int j = 0;
		while(j < 8- A[i]){					//leds to remain dark stay at 0;
		j++;									
		}
		while(j<=7){							//leds to be lit get a value of one
		matrix[i][j] = 1;
		j++;
		}
	}
}
void updateMatrix(){
	makeMatrix();
	lightCols();
}

/************At the moment, all this does is cycle trhough the various sorting algorithms endlessly
		At some point, making the sorts represent some real world data would be cool, and I'd like to get a 
		truer rand sequence of sorts.  Seed off of a noisy pin?****************************/




int main(){

   //Initialize MAX system
   MAXInit();
	_delay_ms(100);
	LCDinit();
	_delay_ms(100);
	LCDclr();
	_delay_ms(100);

   //our endless loop
   for(;;){
   
   _delay_ms(300);
  
   	randInts();
	LCDclr();
	CopyStringtoLCD(insertionsrt, 0, 0);
	_delay_ms(100);
	sortInsertion();
	_delay_ms(1000);

	randInts();
	LCDclr();
	CopyStringtoLCD(bubblesrt, 0, 0);
	_delay_ms(100);
	sortBubble();
	_delay_ms(1000);

	randInts();
	LCDclr();
	CopyStringtoLCD(selectionsrt, 0, 0);
	_delay_ms(100);
	sortSelection();
	_delay_ms(1000);

	randInts();
	LCDclr();
	CopyStringtoLCD(mergesrt, 0, 0);
	_delay_ms(100);
	sortMerge();
	_delay_ms(1000);


			
	}
	return 1;		//the end, which is never reached, so it's kinda arbitrary.
}
