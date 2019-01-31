#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define WORD_LENGTH 200+1
#define TOKEN_LIST_SIZE 88


/**
 * Definition of states
 */
#define PROCEDURE_NAME 		0
#define VARIABLE_NAME 		1
#define OTHER_NAME 			2

// Declaring a boolean
typedef enum _boolean {
	false, true
} boolean;


// Token list
typedef enum _token_list {
	// special token for value that are not
	// a keyword of the language
	NOTHING = -1,

	// Tokens for real keywords of the language
	ABORT_TOKEN, //0
	ABS_TOKEN , 
	ABSTRACT_TOKEN , 
	ACCEPT_TOKEN,
	ACCESS_TOKEN ,
	ALIASED_TOKEN ,//5
	ALL_TOKEN ,
	AND_TOKEN ,
	ARRAY_TOKEN ,
	AT_TOKEN , 
	BEGIN_TOKEN,//10
	BODY_TOKEN ,
	CASE_TOKEN ,
	CONSTANT_TOKEN ,
	DECLARE_TOKEN , 
	DELAY_TOKEN , //15
	DELTA_TOKEN , 
	DIGITS_TOKEN , 
	DO_TOKEN , 
	ELSE_TOKEN , 
	ELSIF_TOKEN , //20
	END_TOKEN , 
	ENTRY_TOKEN , 
	EXCEPTION_TOKEN , 
	EXIT_TOKEN , 
	FOR_TOKEN , //25
	FUNCTION_TOKEN , 
	GENERIC_TOKEN , 
	GOTO_TOKEN , 
	IF_TOKEN , 
	IN_TOKEN , //30
	INOUT_TOKEN ,
	INTERFACE_TOKEN , 
	IS_TOKEN , 
	LIMITED_TOKEN , 
	LOOP_TOKEN , //35
	MOD_TOKEN , 
	NEW_TOKEN , 
	NOT_TOKEN , 
	NULL_TOKEN , 
	OF_TOKEN , 
	OR_TOKEN , 
	OTHERS_TOKEN , 
	OUT_TOKEN , 
	OVERRIDING_TOKEN , 
	PACKAGE_TOKEN , //45
	PRAGMA_TOKEN , 
	PRIVATE_TOKEN , 
	PROCEDURE_TOKEN , 
	PROTECTED_TOKEN ,
	RAISE_TOKEN , 
	RANGE_TOKEN , 
	RECORD_TOKEN , 
	REM_TOKEN , 
	RENAMES_TOKEN , 
	REQUEUE_TOKEN, //55
	RETURN_TOKEN , 
	REVERSE_TOKEN , 
	SELECT_TOKEN , 
	SEPARATE_TOKEN , 
	SOME_TOKEN , 
	SUBTYPE_TOKEN , 
	SYNCHRONIZED_TOKEN , 
	TAGGED_TOKEN , 
	TASK_TOKEN , 
	TERMINATE_TOKEN , //65
	THEN_TOKEN , 
	TYPE_TOKEN , 
	UNTIL_TOKEN , 
	USE_TOKEN , 
	WHEN_TOKEN , //70
	WHILE_TOKEN , 
	WITH_TOKEN , 
	XOR_TOKEN,

	// Token used for the symbols of the language
	EQUAL_TOKEN, 
	PLUS_TOKEN,//75 
	SUBSTRACT_TOKEN,
	MULTIPLY_TOKEN,
	DIVIDE_TOKEN,
	AFFECTATION_TOKEN, 
	GREATER_TOKEN,//80
	GREATER_EQUAL_TOKEN,
	LESS_TOKEN,
	LESS_EQUAL_TOKEN,
	OPEN_PARENTHESIS_TOKEN,
	CLOSE_PARENTHESIS_TOKEN,//85
	SEMICOLON_TOKEN,
	DEUXPOINTS_TOKEN,


	// Special tokens
	ID_TOKEN,
	STRING_TOKEN,
	ATTRIBUTE_TOKEN, //90
	REAL_NUMBER_TOKEN,
	INTEGER_TOKEN,
	CHAR_TOKEN,

	// SEPARATOR TOKEN
	SEPARATOR_TOKEN,
	EOF_TOKEN,//95
} token;


// Symbol struct
struct _symbol {
	token code;
	char word[WORD_LENGTH];
};


// Type of the symbols that will be stored in the tanle of symbols
typedef enum _symbol_type {
	TVAR,
	TPROC,
	TOTH,
} symbol_type;


// Symbol structure that will be stored in the table of symbols
struct _stored_symbol {
	char word[WORD_LENGTH];
	enum _symbol_type type;
	int address;
	int length;
};


// Variable declaration
FILE* file;
char output_file_name[20];
char interpreter_input_file_name[20];


char current_char;
struct _symbol current_symbol;

int symbol_table_size;
int symbol_table_max_size;
struct _stored_symbol *symbol_table;

int current_line;
int offset;

int state;
int current_address;

#endif
