#include "pile.h"


void _pile_init() {
	pile_index = 0;				
	pile_max_index = INIT_PILE_SIZE - 1;

	pile = malloc((pile_max_index + 1) * sizeof(float));
}

void _pile_add(float e) {
	if (pile_index == pile_max_index) {
		printf("Pile size changed ! \n");
		pile_max_index += 10;
		/* We need to resize the pile  */
		pile = realloc(pile, (pile_max_index + 1) * sizeof(float));
	}

	pile[pile_index++] = e;
}

float _pile_top() {
	return pile[--pile_index];
}


void _pile_show() {
	printf("Pile content : ");
	for (int i = 0; i < pile_index; i++) {
		printf(" - %f", pile[i]);
	}
	printf("\n\n");
}

float _pile_get(int i) {
	return pile[i];
}

void _pile_set(int i, float e) {
	pile[i] = e;
}