#include "analyseur_synthaxique.h"


/**
 * The start of the syntactic analyzer
 */
boolean PROGRAM() {
	// Initialization
	init_symbol();
	init_symbol_table();

	// Reading the first token
	next_symbol();

	boolean result = false;

	// Trying to find the grammar to execute
	if (SUBPROGRAM_BODY()) result = true;

	// Showing the symbol table
	show_symbol_table();

	return result;
}


//******************************************************
//********************************************************
			
//			SYNTACTIC ANALYZER FUNCTIONS
	
//SUBPROGRAM_BODY := SUBPROGRAM_SPECIFICATION is DECLARATIVE_PART begin HANDLED_STATEMENT_OF_SEQUENCE end  [DESIGNATOR];
static boolean SUBPROGRAM_BODY(){
	
	if(!SUBPROGRAM_SPECIFICATION()) return false;
	
	if (current_symbol.code != IS_TOKEN) raise_error(IS_EXPECTED_ERROR);
	next_symbol();

	if(!DECLARATIVE_PART())	return false;

	if (current_symbol.code != BEGIN_TOKEN)	raise_error(BEGIN_EXPECTED_ERROR);
	next_symbol();
	
	if(!HANDLED_STATEMENT_OF_SEQUENCE()) return false;
	
	if (current_symbol.code != END_TOKEN) raise_error(END_EXPECTED_ERROR);
	next_symbol(); 
	
	DESIGNATOR();
	return true;
		
} 

//SUBPROGRAM_SPECIFICATION := PROCEDURE_SPECIFICATION | FUNCTION_SPECIFICATION
static boolean SUBPROGRAM_SPECIFICATION () {
	
	if (PROCEDURE_SPECIFICATION()) return true;
	else if (SUBPROGRAM_SPECIFICATION()) return true;
	else return false;
	
}

//PROCEDURE_SPECIFICATION :=  procudure DPUN PARAMETER_PROFILE
static boolean PROCEDURE_SPECIFICATION(){	

	if (current_symbol.code != PROCEDURE_TOKEN)  raise_error(PROCEDURE_EXPECTED_ERROR);
	next_symbol();

	if(DPUN()){
		if(PARAMETER_PROFILE()) return true;
	}
		
	return false;	
} 


//DPUN := [PARENT_UNIT_NAME] DEFINING_IDENTIFIER 
static boolean DPUN(){	

	PARENT_UNIT_NAME();
	
	if(DEFINING_IDENTIFIER()) return true;	
	return false;	
} 


// DEFINING_IDENTIFIER := IDENTIFIER
static boolean DEFINING_IDENTIFIER(){	

	if(IDENTIFIER()) return true;	
	return false;	
} 


//PARAMETER_PROFILE := FORMAT_PART
static boolean PARAMETER_PROFILE() {
	if(FORMAT_PART(); return true;
	return false;
}

//FORMAT_PART := (PARAMETER_SPECIFICATION{;PARAMETER_SPECIFICATION})
static boolean FORMAT_PART() {

	if (current_symbol.code != PO_TOKEN)  raise_error(PO_EXPECTED_ERROR);
	next_symbol();
	
	if (!PARAMETER_SPECIFICATION()) return false;

	while(PARAMETER_SPECIFICATION());

	if (current_symbol.code != PF_TOKEN)  raise_error(PF_EXPECTED_ERROR);
	next_symbol();
	
	return true;
	
}


//PARAMETER_SPECIFICATION ::= DEFINING_IDENTIFIER_LIST:MODE 
static boolean PARAMETER_SPECIFICATION() {
	if(!DEFINING_IDENTIFIER_LIST()) return false;
	
	if (current_symbol.code != DEUXPOINT_TOKEN) raise_error(DEUXPOINT_EXPECTED_ERROR) ;
	next_symbol();

	if(!MODE()) return false;
	return true;
}


//DEFINING_IDENTIFIER_LIST :: = DEFINING_IDENTIFIER
static boolean DEFINING_IDENTIFIER_LIST() {
	if(DEFINING_IDENTIFIER()) return true;
	return false;
}

//MODE ::= IN | INOUT|OUT |epsilon
static boolean MODE() {
	
	if (current_symbol.code != IN_TOKEN) {
			if (current_symbol.code != INOUT_TOKEN) {
					if (current_symbol.code != OUT_TOKEN) {
						return true;
					}
			}
	}

	next_symbol();
	return true;
}


/********************************************************
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


// COMPOUND_STATEMENT ::= IF_STATEMENT
static boolean COMPOUND_STATEMENT() {
	
	if(IF_STATEMENT()) return true;
	return false;
}


/**
 * ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT ::= name ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT
 */
static boolean ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT() {
	if (current_symbol.code != ID_TOKEN)
		return false;

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

	printf("Finished reading an assignement statement \n");

	next_symbol();

	return true;
}

static boolean PROCEDURE_CALL_STATEMENT() {
	if (current_symbol.code != SEMICOLON_TOKEN)
		return false;

	printf("Finished reading a procedure call \n");

	next_symbol();

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









/*
 * IF_STATEMENT ::= if CONDITION then SEQUENCE_OF_STATEMENT {elseif CONDITION then SEQUENCE_OF_STATEMENT} [else SEQUENCE_OF_STATEMENT] end if;
 */
 
static boolean IF_STATEMENT(){
	
	if(current_symbol.code!=IF_TOKEN) return false;
	next_symbol();
	
	CONDITION();
	
	if(current_symbol.code!=THEN_TOKEN) 
		raise_error(THEN_EXPECTED_ERROR);

	next_symbol();

	// TODO a revoir ??
	SEQUENCE_OF_STATEMENT();
	
	
	// {elseif CONDITION then SEQUENCE_OF_STATEMENT}
	while(current_symbol.code==ELSIF_TOKEN){
		next_symbol();

		CONDITION();
		
		if(current_symbol.code!=THEN_TOKEN) 
			raise_error(THEN_EXPECTED_ERROR);
		
		next_symbol();
		
	
	}

	if(current_symbol.code == ELSE_TOKEN) {
		next_symbol();
		SEQUENCE_OF_STATEMENT();
	}
		
	if(current_symbol.code!=END_TOKEN) 
		raise_error(END_EXPECTED_ERROR);
	next_symbol();
	
	if(current_symbol.code!=IF_TOKEN) 
		raise_error(IF_EXPECTED_ERROR);
	next_symbol();

	if(current_symbol.code!=SEMICOLON_TOKEN) 
		raise_error(SEMICOLON_EXPECTED_ERROR);
	next_symbol();
	
	
	printf(" fin de if statement \n " );
	return true;
	
	
		

}

/*
 * EXPRESSION ::= RELATION { and RELATION } | RELATION { or RELATION } | RELATION { xor RELATION }
 */

static boolean EXPRESSION(){
	
	if(!RELATION()) return false;	
	
	// { and RELATION }
	if(current_symbol.code==AND_TOKEN) {

		while (current_symbol.code==AND_TOKEN){
			next_symbol();
			if(!RELATION()) return false;	
			
		}
	
	}

	// { or RELATION }
	else if(current_symbol.code==OR_TOKEN) {
		while (current_symbol.code==OR_TOKEN){
			next_symbol();
			if(!RELATION()) return false;	
			
		}
	
	}

	//{ xor RELATION }
	else if (current_symbol.code==XOR_TOKEN) {
		while (current_symbol.code==XOR_TOKEN){
			next_symbol();
			if(!RELATION()) return false;	
			
		}

	}

	return true;
	
	
}

/*
 * RELATION ::= SIMPLE_EXPRESSION [ RELATION_OPERATOR SIMPLE_EXPRESSION ] 
 */

static boolean RELATION(){

	if(!SIMPLE_EXPRESSION()) return false;
		
	if (RELATION_OPERATOR() ){
		next_symbol();
		if(!SIMPLE_EXPRESSION()) return false;	
			
	}
	

	return true;
	
	
}

/*
 * SIMPLE_EXPRESSION ::= [ UNARY_ADDING_OPERATOR ] TERM { BINARY_ADDING_OPERATOR TERM }
 */

static boolean SIMPLE_EXPRESSION(){
	
	if(UNARY_ADDING_OPERATOR()){
		next_symbol();
	}
	if(!TERM()) return false;

	while (BINARY_ADDING_OPERATOR()){
		next_symbol();
		if(!TERM()) return false;	
			
	}
	

	
	return true;
	
}

/*
 * TERM ::= FACTOR { MULTIPLYING_OPERATOR FACTOR } 
 */

static boolean TERM(){
	if(!FACTOR()) return false;
		
	while (MULTIPLYING_OPERATOR()){
		next_symbol();
		if(!FACTOR()) return false;	
			
	}
	

	return true;
	
	
}

/*
 * FACTOR ::= PRIMARY [** PRIMARY] 
 */

static boolean FACTOR() {
	if(!PRIMARY()) return false;
		
	//TODO  [** PRIMARY] 
	/*
	if(current_symbol.code==exponentiate){
		next_symbol();
		if(!PRIMARY()) return false;		
	}
	*/

	return true;
	
}

/*
 * PRIMARY ::= READ_NUMBER  | null | name | STRING_LITERAL | (EXPRESSION) 
 */

static boolean PRIMARY(){

	if(current_symbol.code==INTEGER_TOKEN || current_symbol.code==REAL_NUMBER_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==NULL_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==ID_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==STRING_TOKEN) { next_symbol(); return true;}

	else if(current_symbol.code==OPEN_PARENTHESIS_TOKEN) { 
		next_symbol(); 
		if(EXPRESSION() && current_symbol.code==CLOSE_PARENTHESIS_TOKEN){
			next_symbol();
			return true;
		}
		else return false;
	}

	else return false;
	
}

/*
 * UNARY_ADDING_OPERATOR ::= + | -
 */

static boolean UNARY_ADDING_OPERATOR(){

	if(current_symbol.code==PLUS_TOKEN) { return true;}
	else if(current_symbol.code==SUBSTRACT_TOKEN) { return true;}
	else return false;
}

/*
 * BINARY_ADDING_OPERATOR ::= + | - | &
 */

static boolean BINARY_ADDING_OPERATOR(){
	
	if(current_symbol.code==PLUS_TOKEN) { return true;}
	else if(current_symbol.code==SUBSTRACT_TOKEN) { return true;}
	// TODO FIND THE THE NAME OF TOKEN &   else if(current_symbol.code=="&") { return true;}
	else return false;

}

/*
 * MULTIPLYING_OPERATOR ::= * | / | mod / rem
 */

static boolean MULTIPLYING_OPERATOR(){

	if(current_symbol.code==MULTIPLY_TOKEN) {  return true;}
	else if(current_symbol.code==DIVIDE_TOKEN) {  return true;}
	else if(current_symbol.code==MOD_TOKEN) {  return true;}
	else if(current_symbol.code==REM_TOKEN) {  return true;}
	else return false;
	
}

/*
 * CONDITION ::= EXPRESSION
 */
static boolean  CONDITION() {
	
	return EXPRESSION();

}


/*
 * RELATION_OPERATOR ::=  = | /=  | < | <= | > | >=
 */

static boolean  RELATION_OPERATOR(){

	if(current_symbol.code==EQUAL_TOKEN) { return true;}
	// TODO FIND THE THE NAME OF TOKEN /=       else if(current_symbol.code=="/=") { return true;}
	else if(current_symbol.code==LESS_TOKEN) { return true;}
	else if(current_symbol.code==LESS_EQUAL_TOKEN) { return true;}
	else if(current_symbol.code==GREATER_TOKEN) {  return true;}
	else if(current_symbol.code==GREATER_EQUAL_TOKEN) {  return true;}
	else return false;
	
}
static boolean  _NAME(){return false;}
