#ifndef GLOBAL_H
#define GLOBAL_H


// Token list
typedef enum _token {
	FIRST_TOKEN,
} token;



// Symbol struct
struct _symbol {
	token code;
	char* word;
};



// Variable declaration
char current_char;
struct _symbol symbol;

#endif