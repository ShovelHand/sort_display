#include "sortAlgos.h"

extern uint8_t A[7];

//make two columns blink off and on again.  can make one column blink by using same index for both arguments
void blink(int i, int j){
	uint8_t temp1 = A[i];
	uint8_t temp2 = A[j];
	A[i] = 0;
	A[j] = 0;
	updateMatrix();
	_delay_ms(300);
	A[i] = temp1;
	A[j] = temp2;
	updateMatrix();
	_delay_ms(500);
}

//the value at the index of the first argument is exchanged with the index value at the second
void exchange(int i, int j){
	uint8_t temp = A[i];
	A[i] = A[j];
	A[j] = temp;
	updateMatrix();
}


//insertion sort
void sortInsertion(){
	_delay_ms(500);
	for(int i = 0; i < sizeof(A); i++){
		uint8_t val = A[i];
		blink(i,i);
		int holePos = i;
		while(holePos > 0 && val < A[holePos -1]){
			exchange(holePos, holePos-1);
			holePos -=1;
			blink(holePos, holePos);
			_delay_ms(300);
		}
		A[holePos] = val;
	}
		updateMatrix();
		_delay_ms(300);
}

//bubble sort algorithm
void sortBubble(){
_delay_ms(50);
int j = 1;
	while(j <= sizeof(A)){
	for(int i = 0; i < sizeof(A)-j; i++){
			blink(i, i+1);
			if(A[i] > A[i+1]){
				exchange(i, i+1);
				_delay_ms(300);
				}
				else{
				_delay_ms(100);
				}			
			}
			j++;
			_delay_ms(300);
		}
		updateMatrix();
}

void sortSelection(){
	for(int i = 0; i < sizeof(A); i++){
		int min = i;
		for (int j = i+1; j< 7; j++){
			if(A[j] < A[min]){
				min = j;				
				}
			}
			blink(i, min);
				_delay_ms(300);
				exchange(i, min);
			_delay_ms(300);
		}
}

