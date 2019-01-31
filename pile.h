#ifndef PILE_H
#define PILE_H

#include <stdlib.h>
#include <stdio.h>

#define INIT_PILE_SIZE	10

/* Creating the pile structure */
float 	*pile;
int 	pile_index;
int 	pile_max_index;

/* Init */
void _pile_init();

/* Adding an element */
void _pile_add(float e);

/* Getting the top element */
float _pile_top();

/* Showing the content of the pile */
void _pile_show();

/* Getting a special memory spot */
float _pile_get(int i);

/* Set a value in a special spot in memory */
void _pile_set(int i, float e);


#endif 
