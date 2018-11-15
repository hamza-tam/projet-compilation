#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


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
FILE* file;

char current_char;
struct _symbol current_symbol;

int current_line;


#endif