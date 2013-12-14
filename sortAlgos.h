#ifndef SORTALGOS_H
#define SORTALGOS_H


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


//FUNCTION PROTOTYPES**********************
void blink(int, int);
void exchange(int, int);
void sortSelection(void);
void sortBubble(void);
void sortInsertion(void);


#endif 
