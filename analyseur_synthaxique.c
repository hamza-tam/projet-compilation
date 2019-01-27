#include "analyseur_synthaxique.h"

/**
 * The start of the syntactic analyzer
 */
boolean PROGRAM() {
	// Initialization
	init_symbol();
	init_symbol_table();
	_pseudo_code_init();

	// Reading the first token
	next_symbol();

	boolean result = false;

	// Trying to find the grammar to execute
	if (HANDLED_STATEMENT_OF_SEQUENCE()) result = true;

	// Showing the symbol table
	show_symbol_table();

	/* showing the pseudo code */
	_pseudo_code_add_inst(MUL, 2);
	_pseudo_code_print();
	_pseudo_code_write();

	return result;
}


/*******************************************************
********************************************************
			
			SYNTACTIC ANALYZER FUNCTIONS

********************************************************
*******************************************************/

/**
 * DECLARATIVE_PART ::= {DECLARATIVE ITEM}
 */
static boolean DECLARATIVE_PART() {
	DECLARATIVE_ITEM();

	return false;
}


/**
 * DECLARATIVE_ITEM ::= BASIC_DECLARATIVE_ITEM | BODY
 */
static boolean DECLARATIVE_ITEM() {
	BASIC_DECLARATIVE_ITEM();

	return false;
}


/**
 * DECLARATIVE_ITEM ::= BASIC_DECLARATIVE_ITEM | BODY
 */
static boolean BASIC_DECLARATIVE_ITEM() {
	BASIC_DECLARATIVE_ITEM();

	return false;
}


// TOFO Writing the grammar
static boolean BODY() {
	return false;
}


/**
 * HANDLED_STATEMENT_OF_SEQUENCE ::= SEQUENCE_OF_STATEMENT
 */
static boolean HANDLED_STATEMENT_OF_SEQUENCE() {
	if (SEQUENCE_OF_STATEMENT()) return true;
	return false;
}


/**
 * SEQUENCE_OF_STATEMENT ::= STATEMENT {STATEMENT} {LABEL}
 */
static boolean SEQUENCE_OF_STATEMENT() {
	// Reading at least one statement grammar
	if (!STATEMENT()) return false;

	while(STATEMENT());

	return true;
}

/**
 * STATEMENT ::= {LABEL} SIMPLE_STATEMENT | {LABEL} COMPOUND_STATEMENT
 */
static boolean STATEMENT() {
	// Reading a simple statement or a compound statement
	if (SIMPLE_STATEMENT()) return true;
	else if (COMPOUND_STATEMENT()) return true;
	else return false;
}


/**
 * SIMPLE_STATEMENT ::= ASSIGNEMENT_STATEMENT | PRECEDURE_CALL_STATEMENT | EXIT_STATEMENT | SIMPLE_RETURN_STATEMENT
 */
static boolean SIMPLE_STATEMENT() {
	if (ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT()) return true;
	else if (SIMPLE_RETURN_STATEMENT()) return true;
	else return false;
}


// TODO 
static boolean COMPOUND_STATEMENT() {
	return false;
}


/**
 * ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT ::= name ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT
 */
static boolean ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT() {
	if (current_symbol.code != ID_TOKEN)
		return false;

	if (symbol_exists() == -1) {
		raise_error(SYMBOL_NOT_FOUND_ERROR);
	}
	
	add_symbol(TVAR);
	next_symbol();

	// reading the next grammar
	ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT();

	return true;
}

/**
 * ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT ::= ASSIGNEMENT_STATEMENT | PROCEDURE_CALL_STATEMENT
 */
static boolean ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT() {
	if (ASSIGNEMENT_STATEMENT()) return true;
	else if (PROCEDURE_CALL_STATEMENT()) return true;
	else return false;
}

/**
 * ASSIGNEMENT_STATEMENT ::= := EXPRESSION
 */
static boolean ASSIGNEMENT_STATEMENT() {
	// Reaading the affectation symbol
	if (current_symbol.code != AFFECTATION_TOKEN) 
		return false;

	next_symbol();

	// Reading an expression
	EXPRESSION();

	if (current_symbol.code != SEMICOLON_TOKEN)
		raise_error(SEMICOLON_EXPECTED_ERROR);

	next_symbol();

	printf("Finished reading an assignement statement \n");

	return true;
}

static boolean PROCEDURE_CALL_STATEMENT() {
	if (current_symbol.code != SEMICOLON_TOKEN)
		return false;

	next_symbol();

	printf("Finished reading a procedure call \n");

	return true;
}


/**
 * EXIT_STATEMENT ::= exit [LOOP_NAME] [when CONDITION]
 */
static boolean EXIT_STATEMENT() {
	// Reading the exit keyword 
	if (current_symbol.code != EXIT_TOKEN) return false;
	next_symbol();

	// Checking if there is a loop name and reading it
	if (current_symbol.code == ID_TOKEN) next_symbol();

	// Checking if there is a when + condition
	if (current_symbol.code == WHEN_TOKEN) {
		next_symbol();
		CONDITION();
	}

	return true;
}


/*
 * SIMPLE_RETURN_STATEMENT ::= return [EXPRESSION] ;
 */
static boolean SIMPLE_RETURN_STATEMENT() {
	if (current_symbol.code != RETURN_TOKEN) return false;
	next_symbol();

	EXPRESSION();

	if (current_symbol.code != SEMICOLON_TOKEN) raise_error(SEMICOLON_EXPECTED_ERROR);
	next_symbol();

	printf("Finished reading return statement \n");	

	return true;
}


// TODO coding the condition grammar
static boolean EXPRESSION() {
	next_symbol();
	return false;
}


// TODO coding the condition grammar
static boolean CONDITION() {
	next_symbol();
	return false;
}