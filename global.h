#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>


#define WORD_LENGTH 200+1

// Declaring a boolean
typedef enum _boolean {
	false, true
} boolean;



// Token list
typedef enum _token {
	FIRST_TOKEN,
} token;



// Symbol struct
struct _symbol {
	token code;
	char word[WORD_LENGTH];
};



// Variable declaration
static FILE* file;

static char current_char;
static struct _symbol current_symbol;

#endif