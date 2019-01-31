#ifndef PSEUDO_CODE_H
#define PSEUDO_CODE_H

#include "global.h"


typedef enum _pcode_inst {
	ADD, /* Perform addition on the top spots of the stack */
	SUB, /* Perform substration on the top spots of the stack */
	MUL, /* Perform multiplication on the top spots of the stack */
	DIV, /* Perform division on the top spots of the stack */
	EQL, /* Check if the the two spots on the top of the stack are equal */
	NEQ, /* Check if the the two spots on the top of the stack are not equal */
	GTR,
	LSS, 
	GEQ, 
	LEQ, 
	PRN, 
	INN, 
	INT, /* Asks for a number of memory spots to be reserved */
	LDI, 
	LDA, // Chargement de l'adresse
	LDV, // Chargement de la valeur
	STO, // Stockage de la valeur dans une adresse
	BRN, 
	BZE, 
	HLT, /* End of the program */
	NOP, /* No operation */
} pcode_inst;


/**
 * The structure that stores the a line of the pseudo code
 */
typedef struct _pcode_line {
	pcode_inst inst;
	float parameter;
} pcode_line;

/**
 * The struct to store the linked list of Pcode instructions
 */
typedef struct _node {
	pcode_line line;
	struct _node *next; 
} node;


/**
 * Function prototypes
 */

/* init pseudo code structure */
void _pseudo_code_init();

/**
 * add inst with parameter 
 * to add an instruction that doesn't need a parameter
 * fill the parameter option with '0'
 */
void _pseudo_code_add_inst(pcode_inst inst, float param);

/* Writing pseudo code into a file */
void _pseudo_code_write();

/* Printing the pseudo code */
void _pseudo_code_print();

#endif
