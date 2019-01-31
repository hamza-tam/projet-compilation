#include "pile.h"


void _pile_init() {
	pile_index = 0;				
}

void _pile_add(float e) {
	pile[pile_index++] = e;
}

float _pile_top() {
	return pile[pile_index--];
}
