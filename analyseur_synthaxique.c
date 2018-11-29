#include "analyseur_synthaxique.h"


/**
 * The start of the syntactic analyzer
 */
boolean PROGRAM() {
	// Initialization
	init_symbol();

	// Reading the first token
	next_symbol();

	// Trying to find the grammar to execute
	if (HANDLED_STATEMENT_OF_SEQUENCE()) return true;

	return false;
}


/*******************************************************
********************************************************
			
			SYNTACTIC ANALYZER FUNCTIONS

********************************************************
*******************************************************/

/**
 * DECLARATIVE_PART ::= {DECLARATIVE ITEM}
 */
boolean DECLARATIVE_PART() {
	DECLARATIVE_ITEM();

	return false;
}


/**
 * DECLARATIVE_ITEM ::= BASIC_DECLARATIVE_ITEM | BODY
 */
boolean DECLARATIVE_ITEM() {
	BASIC_DECLARATIVE_ITEM();

	return false;
}


/**
 * DECLARATIVE_ITEM ::= BASIC_DECLARATIVE_ITEM | BODY
 */
boolean BASIC_DECLARATIVE_ITEM() {
	BASIC_DECLARATIVE_ITEM();

	return false;
}


// TOFO Writing the grammar
boolean BODY() {
	return false;
}


/**
 * HANDLED_STATEMENT_OF_SEQUENCE ::= SEQUENCE_OF_STATEMENT
 */
boolean HANDLED_STATEMENT_OF_SEQUENCE() {
	if (SEQUENCE_OF_STATEMENT()) return true;
	return false;
}


/**
 * SEQUENCE_OF_STATEMENT ::= STATEMENT {STATEMENT} {LABEL}
 */
boolean SEQUENCE_OF_STATEMENT() {
	// Reading at least one statement grammar
	if (!STATEMENT()) return false;

	return true;
}

/**
 * STATEMENT ::= {LABEL} SIMPLE_STATEMENT | {LABEL} COMPOUND_STATEMENT
 */
boolean STATEMENT() {
	// Reading a simple statement or a compound statement
	if (SIMPLE_STATEMENT()) return true;
	else if (COMPOUND_STATEMENT()) return true;
	else return false;
}


/**
 * SIMPLE_STATEMENT ::= ASSIGNEMENT_STATEMENT | EXIT_STATEMENT | PRECEDURE_CALL_STATEMENT | SIMPLE_RETURN_STATEMENT | GOTO_STATEMENT | RAISE_STATEMENT
 */
boolean SIMPLE_STATEMENT() {
	if (ASSIGNEMENT_STATEMENT()) return true;
	else return false;
}


// TODO 
boolean COMPOUND_STATEMENT() {
	return false;
}


/**
 * ASSIGNEMENT_STATEMENT ::= name := EXPRESSION
 */
boolean ASSIGNEMENT_STATEMENT() {
	// Reading an identifier
	if (current_symbol.code != ID_TOKEN) 
		return false;
	
	next_symbol();

	// Reaading the affectation symbol
	if (current_symbol.code != AFFECTATION_TOKEN) 
		raise_error(AFFECTATION_SYMBOL_EXPECTED_ERROR);

	next_symbol();

	// Reading an expression
	EXPRESSION();

	return true;
}


/**
 * EXIT_STATEMENT ::= exit [LOOP_NAME] [WHEN CONDITION]
 */
boolean EXIT_STATEMENT() {
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


// TODO coding the condition grammar
boolean EXPRESSION() {
	next_symbol();
	return false;
}


// TODO coding the condition grammar
boolean CONDITION() {
	next_symbol();
	return false;
}