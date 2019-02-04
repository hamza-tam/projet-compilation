#include "analyseur_synthaxique.h"
#include "errors.h"

/**
 * The start of the syntactic analyzer
 */
 


//PROGRAM := SUBPROGRAM_BODY
boolean PROGRAM() {
	// Initialization
	init_symbol();
	init_symbol_table();
	_pseudo_code_init();

	// Reading the first token
	next_symbol();
	
	boolean result = false;
	address_offset = 0;

	// Trying to find the grammar to execute
	if (SUBPROGRAM_BODY()) result = true;

	_pseudo_code_add_inst(LDA, get_first_procedure_address());
	_pseudo_code_add_inst(JSR, 0);
	_pseudo_code_add_inst(HLT, 0);

	// Showing the symbol table
	show_symbol_table();
	_pseudo_code_write_text();

	return result;
}


//******************************************************
//********************************************************
			
//			SYNTACTIC ANALYZER FUNCTIONS
	
//SUBPROGRAM_BODY := SUBPROGRAM_SPECIFICATION is DECLARATIVE_PART begin HANDLED_STATEMENT_OF_SEQUENCE end  [DESIGNATOR];
static boolean SUBPROGRAM_BODY(){
	
	/* The identifiers declared now are not variables */
	state = PROCEDURE_NAME;
	int symbol_table_start = symbol_table_size;

	if(!SUBPROGRAM_SPECIFICATION()) return false;
	
	if (current_symbol.code != IS_TOKEN) raise_error(IS_EXPECTED_ERROR);
	next_symbol();

	/* The identifiers declared now can be variables */
	state = VARIABLE_NAME;

	if(!DECLARATIVE_PART())	raise_error(DECLARATIVE_PART_ERROR);

	if (current_symbol.code != BEGIN_TOKEN)	raise_error(BEGIN_EXPECTED_ERROR);
	next_symbol();
	
	if(!HANDLED_STATEMENT_OF_SEQUENCE()) raise_error(HANDLED_STATEMENT_OF_SEQUENCE_ERROR);
	
	if (current_symbol.code != END_TOKEN) raise_error(END_EXPECTED_ERROR);
	next_symbol(); 
	
	if (DESIGNATOR()) next_symbol();

	if (current_symbol.code != SEMICOLON_TOKEN) raise_error(SEMICOLON_EXPECTED_ERROR);
	next_symbol();

	/* Clearing the memory spots used by this sybprogram */
	int to_clean_spots = _symbol_table_to_free(symbol_table_start);
	current_address -= to_clean_spots;
	
	_pseudo_code_add_inst(FRE, to_clean_spots);

	address_offset--;

	/* Generating the return instruction to the previous subprogram */
	_pseudo_code_add_inst(RTS, 0);
	_pseudo_code_fix_spd();

	return true;
		
} 

/*
 * DESIGNATOR ::= name
 */
static boolean DESIGNATOR() {
	if (current_symbol.code == ID_TOKEN) return true;
	return false;
}

//SUBPROGRAM_SPECIFICATION := PROCEDURE_SPECIFICATION | FUNCTION_SPECIFICATION
static boolean SUBPROGRAM_SPECIFICATION () {
	
	if (PROCEDURE_SPECIFICATION()) return true;
	//else if (FUNCTION_SPECIFICATION()) return true;
	else return false;
	
}

//PROCEDURE_SPECIFICATION :=  procedure DPUN PARAMETER_PROFILE
static boolean PROCEDURE_SPECIFICATION(){	

	if (current_symbol.code != PROCEDURE_TOKEN)  {return false;}
	next_symbol();

	if(!DPUN()) raise_error(DPUN_ERROR); 
		
	PARAMETER_PROFILE();
		
	return true;	
} 


//DPUN := [PARENT_UNIT_NAME] DEFINING_IDENTIFIER 
static boolean DPUN(){	

	//PARENT_UNIT_NAME();
	
	if(DEFINING_IDENTIFIER()) return true;	
	return false;	
} 


// DEFINING_IDENTIFIER := id
static boolean DEFINING_IDENTIFIER(){	
	
	if (current_symbol.code != ID_TOKEN)  return false;
	
	/**
	 * Ajout dans la table des symboles
	 */
	if (symbol_exists() != -1) {
		raise_error(SYMBOL_EXISTS_ERROR);		
	} else {
		if (state == PROCEDURE_NAME) {
			_pseudo_code_add_inst(SPD, -1);
			address_offset++;
			add_symbol(TPROC);
			set_last_symbol_address(_pseudo_code_current_line());
		}
		else if (state == VARIABLE_NAME) {
			add_symbol(TVAR); 
			_pseudo_code_add_inst(INT, 1);
		}
	}

	next_symbol();
	
	return true;	
} 




//PARAMETER_PROFILE := FORMAT_PART
static boolean PARAMETER_PROFILE() {
	
	if(FORMAT_PART()) return true;
	return false;
}

//FORMAT_PART := (PARAMETER_SPECIFICATION{;PARAMETER_SPECIFICATION})
static boolean FORMAT_PART() {
	if (current_symbol.code != OPEN_PARENTHESIS_TOKEN)  return false;
	next_symbol();

	if (!PARAMETER_SPECIFICATION()) raise_error(PARAMETER_SPECIFICATION_ERROR);


	while (current_symbol.code == SEMICOLON_TOKEN) {
		next_symbol();
		if(!PARAMETER_SPECIFICATION()) raise_error(PARAMETER_SPECIFICATION_ERROR);
	}

	if (current_symbol.code != CLOSE_PARENTHESIS_TOKEN)  raise_error(PF_EXPECTED_ERROR);
	next_symbol();
	
	return true;
	
}


//PARAMETER_SPECIFICATION ::= DEFINING_IDENTIFIER_LIST:MODE 
static boolean PARAMETER_SPECIFICATION() {
	if(!DEFINING_IDENTIFIER_LIST()) return false;
	if (current_symbol.code != DEUXPOINTS_TOKEN) raise_error(DEUXPOINTS_EXPECTED_ERROR);
	next_symbol();
	if(!MODE()) raise_error(MODE_ERROR);
	return true;
}


//DEFINING_IDENTIFIER_LIST :: = DEFINING_IDENTIFIER
static boolean DEFINING_IDENTIFIER_LIST() {
	if(DEFINING_IDENTIFIER()) return true;
	return false;
}

//MODE ::= IN | INOUT |OUT |epsilon
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
	while(DECLARATIVE_ITEM()){}

	return true;
}


/**
 * DECLARATIVE_ITEM ::= BASIC_DECLARATIVE_ITEM | BODY
 */
static boolean DECLARATIVE_ITEM() {
	if(!BASIC_DECLARATIVE_ITEM()){
		if(!BODY()) return false;
	}

	return true;
}


/**
 * BASIC_DECLARATIVE_ITEM ::= BASIC_DECLARATION 
 */
static boolean BASIC_DECLARATIVE_ITEM(){

	if(!BASIC_DECLARATION()) return false;
	
	return true;
}

/**
 * BODY ::= PROPER_BODY | BODY_STUB
 */
static boolean BODY() {
	if(!PROPER_BODY()){
		if(!BODY_STUB()) return false;
	}
	return true;
}

static boolean BODY_STUB(){
	return false;
}

/**
 * PROPER_BODY ::= SUBPROGRAM_BODY | PACKAGE_BODY | PROTECTED_BODY
 */
 
static boolean PROPER_BODY(){
	
 	if(!SUBPROGRAM_BODY()){
		if(!PACKAGE_BODY()){
			if(!PROTECTED_BODY()) return false;
		}
	}
 	return true;
}

/**
 * BASIC_DECLARATION ::= TYPE_DECLARATION | OBJECT_DECLARATION
 */
 
static boolean BASIC_DECLARATION () {
	
	if(!OBJECT_DECLARATION()) return false;
	return true;
}


static boolean  PACKAGE_BODY(){
	return false;
}


static boolean  PROTECTED_BODY(){
	return false;
}


static boolean OBJECT_DECLARATION () {
	
	if(!DEFINING_IDENTIFIER_LIST()){
		return false;
	}

	int address = get_last_symbol_address();
	
	if (current_symbol.code != DEUXPOINTS_TOKEN) {
		raise_error(DEUXPOINTS_EXPECTED_ERROR);
	}

	next_symbol();

	if (current_symbol.code == CONSTANT_TOKEN) {
		set_last_symbol_const();
		next_symbol();
	}
	
	if(!SUBTYPE_INDICATION()){
		raise_error(SUBTYPE_INDICATION_ERROR);
	}

	
	if (current_symbol.code == AFFECTATION_TOKEN) {
		next_symbol();
		_pseudo_code_add_inst(LDA, address);
		if(!EXPRESSION()) raise_error(EXPRESSION_ERROR);
		_pseudo_code_add_inst(STO, 0);
	}

	if (current_symbol.code == SEMICOLON_TOKEN) {
		next_symbol();
	}
		
	return true;
}

// where we will define our types //int..
static boolean SUBTYPE_INDICATION() {
	if (current_symbol.code == INTEGER_TYPE_TOKEN) {
		set_last_symbol_type(TINT);
	} else if (current_symbol.code == CHAR_TYPE_TOKEN) {
		set_last_symbol_type(TCHR);
	} else if (current_symbol.code == FLOAT_TYPE_TOKEN) {
		set_last_symbol_type(TFLT);
	}
	next_symbol();
	return true;
}

/**
 * HANDLED_STATEMENT_OF_SEQUENCE ::= SEQUENCE_OF_STATEMENT
 */
static boolean HANDLED_STATEMENT_OF_SEQUENCE() {
	if (SEQUENCE_OF_STATEMENT()) return true;
	return false;
}


/**
 * SEQUENCE_OF_STATEMENT ::= STATEMENT {STATEMENT} 
 //{LABEL}
 */
static boolean SEQUENCE_OF_STATEMENT() {
	// Reading at least one statement grammar
	if (!STATEMENT()) return false;

	while(STATEMENT()){}
	//while(LABEL()){}

	return true;
}

/**
 * STATEMENT ::= {LABEL} SIMPLE_STATEMENT | {LABEL} COMPOUND_STATEMENT
 //{LABEL}
 */
static boolean STATEMENT() {
	// Reading a simple statement or a compound statement
	//while(LABEL()){}
	if (SIMPLE_STATEMENT()) return true;
	else if (COMPOUND_STATEMENT()) return true;
	else return false;
}


/**
 * SIMPLE_STATEMENT ::= ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT | EXIT_STATEMENT | SIMPLE_RETURN_STATEMENT | IO_STATEMENT
 */
static boolean SIMPLE_STATEMENT() {
	if (ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT()) return true;
	else if (SIMPLE_RETURN_STATEMENT()) return true;
	else if (IO_STATEMENT()) return true;
	else if (EXIT_STATEMENT()) return true;
	else return false;
}


// COMPOUND_STATEMENT ::= IF_STATEMENT | CASE_STATEMENT | LOOP_STATEMENTS
static boolean COMPOUND_STATEMENT() {
	if(IF_STATEMENT()) return true;
	else if(CASE_STATEMENT()) return true;
	else if(LOOP_STATEMENTS()) return true;
	return false;
}

static boolean CASE_STATEMENT() {
	if (current_symbol.code != CASE_TOKEN) return false;
	next_symbol();

	if (current_symbol.code != ID_TOKEN) raise_error(IDENTIFIER_EXPECTED_ERROR);
	if (symbol_exists() == -1) raise_error(SYMBOL_DONT_EXIST);
	_pseudo_code_add_inst(LDA, get_address());
	_pseudo_code_add_inst(LDV, 0);
	next_symbol();

	if (current_symbol.code != IS_TOKEN) raise_error(IS_EXPECTED_ERROR);
	next_symbol();

	int counter = 0;

	while (current_symbol.code == WHEN_TOKEN) {
		counter++;
		next_symbol();

		_pseudo_code_add_inst(DUP, 0);

		if (current_symbol.code != INTEGER_TOKEN) raise_error(INTEGER_EXPECTED_ERROR);
		_pseudo_code_add_inst(LDI, atoi(current_symbol.word));
		_pseudo_code_add_inst(EQL, 0);
		_pseudo_code_add_inst(BZE, -1);

		next_symbol();

		if (current_symbol.code != NEXT_TOKEN) raise_error(NEXT_EXPECTED_ERROR);
		next_symbol();

		if (!SEQUENCE_OF_STATEMENT()) raise_error(SEQUENCE_STATEMENT_ERROR);

		_pseudo_code_add_inst(BRN, -1);
		_pseudo_code_fix_bze();
	}

	for (int i = 0; i < counter; i++) _pseudo_code_fix_brn();

	if (current_symbol.code != END_TOKEN) raise_error(END_EXPECTED_ERROR);
	next_symbol();

	if (current_symbol.code == CASE_TOKEN) next_symbol();

	if (current_symbol.code != SEMICOLON_TOKEN) raise_error(SEMICOLON_EXPECTED_ERROR);
	next_symbol();

	_pseudo_code_add_inst(FRE, 1);

	return true;
}

/*
 * LOOP_STATEMENTS ::= WHILE_LOOP_STATEMENT | FOR_LOOP_STATEMENT | LOOP_STATEMENT;
 */
static boolean LOOP_STATEMENTS() {
	if (WHILE_LOOP_STATEMENT()) return true;
	else if (FOR_LOOP_STATEMENT()) return true;
	else if (LOOP_STATEMENT()) return true;
	else return false;
}

/*
 * WHILE_LOOP_STATEMENT ::= while CONDITION loop SEQUENCE_OF_STATEMENT end [loop];
 */
static boolean WHILE_LOOP_STATEMENT() {
	if (current_symbol.code != WHILE_TOKEN) return false;
	next_symbol();

	if (!CONDITION()) raise_error(CONDITION_ERROR);

	if (current_symbol.code != LOOP_TOKEN) raise_error(LOOP_EXPECTED_ERROR);
	next_symbol();

	if(!SEQUENCE_OF_STATEMENT()) raise_error(SEQUENCE_STATEMENT_ERROR);

	if (current_symbol.code != END_TOKEN) raise_error(END_EXPECTED_ERROR);
	next_symbol();

	if (current_symbol.code == LOOP_TOKEN) next_symbol();

	if (current_symbol.code != SEMICOLON_TOKEN) raise_error(SEMICOLON_EXPECTED_ERROR);
	next_symbol(); 

	return true;
}


/*
 * FOR_LOOP_STATEMENT ::= 
 */
static boolean FOR_LOOP_STATEMENT() {
	return false;
}


/**
 * loop_statement ::= loop sequence_of_statements end loop ;
 */
static boolean LOOP_STATEMENT() {
	if(current_symbol.code!=LOOP_TOKEN) return false;	
	next_symbol();
	

	/**
	 * generate pseudo code
	*/
	
	int indice_brn = line_number;
	if(!SEQUENCE_OF_STATEMENT()){
		raise_error(SEQUENCE_STATEMENT_ERROR);
	}

	/**
	 * generate pseudo code
	*/
	_pseudo_code_add_inst(BRN,indice_brn);
	_pseudo_code_fix_nbz();

	if(current_symbol.code!=END_TOKEN) {
		raise_error(END_EXPECTED_ERROR);
	}

	next_symbol();

	if(current_symbol.code!=LOOP_TOKEN) {
			raise_error(LOOP_EXPECTED_ERROR);
	}
	next_symbol();

	if(current_symbol.code!=SEMICOLON_TOKEN) {
		raise_error(SEMICOLON_EXPECTED_ERROR);
	}

	next_symbol();
		
	return true;
}


/**
 * ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT ::= name ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT
 */
static boolean ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT() {
	if (current_symbol.code != ID_TOKEN) return false;

	/* Checking of the current identifier is a constant */
	if (is_current_symbol_const()) raise_error(ASSIGNEMENT_TO_CONST_ERROR);

	_pseudo_code_add_inst(LDA, get_address());
	next_symbol();
	if (!ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT()) raise_error(ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT_ERROR);

	return true;
}

/**
 * ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT ::= ASSIGNEMENT_STATEMENT | PROCEDURE_CALL_STATEMENT
 */
static boolean ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT() {
	if (ASSIGNEMENT_STATEMENT()) {
		return true;
	} else if (PROCEDURE_CALL_STATEMENT()) 
		return true;
	else 
		return false;
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
	if(!EXPRESSION()) 
		raise_error(EXPRESSION_ERROR);
	
	_pseudo_code_add_inst(STO, 0);

	if (current_symbol.code != SEMICOLON_TOKEN)
		raise_error(SEMICOLON_EXPECTED_ERROR);

	next_symbol();

	return true;
}

static boolean PROCEDURE_CALL_STATEMENT() {
	if (current_symbol.code != SEMICOLON_TOKEN)
		return false;

	_pseudo_code_add_inst(JSR, 0);

	next_symbol();

	return true;
}


/**
 * EXIT_STATEMENT ::= exit [LOOP_NAME] [when CONDITION];
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
		if(!CONDITION()) raise_error(CONDITION_ERROR);
		_pseudo_code_add_inst(NBZ,-1);
	}

	if (current_symbol.code != SEMICOLON_TOKEN) raise_error(SEMICOLON_EXPECTED_ERROR);
	next_symbol(); 

	return true;
}


/**
 * IO_STATEMENT ::= WRITE_STATEMENT | READ_STATEMENT
 */
 static boolean IO_STATEMENT() {
 	if (WRITE_STATEMENT()) return true;
 	else if (READ_STATEMENT()) return true;

 	return false;
 }

/**
 * WRITE_STATEMENT ::= Put(EXPRESSION);
 */
static boolean WRITE_STATEMENT() {

	current_expression_type = TVAR;

	if (current_symbol.code != PUT_TOKEN) return false;
	next_symbol();

	if (current_symbol.code != OPEN_PARENTHESIS_TOKEN) raise_error(PO_EXPECTED_ERROR);
	next_symbol();

	if (current_symbol.code == STRING_TOKEN){
		/*
		 * Here we want to print strings into the screen
		 */
		int s = strlen(current_symbol.word) - 1;
		/* Loading the string ito the memory */
		for (int i = 1; i < s; i++) {
			_pseudo_code_add_inst(LDI, (int) current_symbol.word[i]);
			_pseudo_code_add_inst(PRC, 0);
		}
		next_symbol();
	} else if (current_symbol.code == CHAR_TOKEN) {
		/*
		 * Here we want to print ot the screen a character
		 */
		if (current_symbol.word[1] == '\\') {
			/* It's a special character */
			char to_print;

			switch (current_symbol.word[2]) {
			case 'n':
				to_print = '\n';
				break;

			case 't':
				to_print = '\t';
				break;

			default:
				to_print = '\n';
				break;
			}

			_pseudo_code_add_inst(LDI, to_print);

		} else {
			/* It's not a special character */
			_pseudo_code_add_inst(LDI, current_symbol.word[1]);
		}

		_pseudo_code_add_inst(PRC, 0);
		next_symbol();
	} else {
		if (!EXPRESSION()) raise_error(SIMPLE_EXPRESSION_ERROR);
		/* Choosing which insctruction to use based on type */
		if (current_expression_type == TINT) _pseudo_code_add_inst(PRI, 0);
		else if (current_expression_type == TCHR) _pseudo_code_add_inst(PRC, 0);
		else _pseudo_code_add_inst(PRF, 0);
	}

	if (current_symbol.code != CLOSE_PARENTHESIS_TOKEN) raise_error(PF_EXPECTED_ERROR);
	next_symbol();

	if (current_symbol.code != SEMICOLON_TOKEN) raise_error(SEMICOLON_EXPECTED_ERROR);
	next_symbol();

	return true;
}

/**
 * READ_STATEMENT ::= Get(EXPRESSION);
 */
static boolean READ_STATEMENT() {
	if (current_symbol.code != GET_TOKEN) return false;
	next_symbol();

	if (current_symbol.code != OPEN_PARENTHESIS_TOKEN) raise_error(PO_EXPECTED_ERROR);
	next_symbol();

	if (current_symbol.code != ID_TOKEN) raise_error(IDENTIFIER_EXPECTED_ERROR);
	_pseudo_code_add_inst(LDA, get_address());
	_pseudo_code_add_inst(RDF, 0);
	_pseudo_code_add_inst(STO, 0);
	next_symbol();

	if (current_symbol.code != CLOSE_PARENTHESIS_TOKEN) raise_error(PF_EXPECTED_ERROR);
	next_symbol();

	if (current_symbol.code != SEMICOLON_TOKEN) raise_error(SEMICOLON_EXPECTED_ERROR);
	next_symbol();

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

	return true;
}


/*
 * IF_STATEMENT ::= if CONDITION then SEQUENCE_OF_STATEMENT {elseif CONDITION then SEQUENCE_OF_STATEMENT} [else SEQUENCE_OF_STATEMENT] end if;
 */
 
static boolean IF_STATEMENT(){
//int indice_brn;
	if(current_symbol.code!=IF_TOKEN) return false;
	next_symbol();

	if(!CONDITION()){
		raise_error(CONDITION_ERROR);
	}
	
	_pseudo_code_add_inst(BZE, -1);


	if(current_symbol.code!=THEN_TOKEN) raise_error(THEN_EXPECTED_ERROR);

	next_symbol();

	if(!SEQUENCE_OF_STATEMENT()){
		raise_error(SEQUENCE_STATEMENT_ERROR);
	}
	
	_pseudo_code_add_inst(BRN,-1);
	_pseudo_code_fix_bze();//Mery

	int counter = 1;

	// {else if CONDITION then SEQUENCE_OF_STATEMENT}
	while(current_symbol.code==ELSIF_TOKEN){
		counter++;
		//indice_brn = line_number;
		next_symbol();
		
		if(!CONDITION()){
			raise_error(CONDITION_ERROR);
		}
		_pseudo_code_add_inst(BZE, -1);
	
		if(current_symbol.code!=THEN_TOKEN) 
			raise_error(THEN_EXPECTED_ERROR);		
		next_symbol();
	
		if(!SEQUENCE_OF_STATEMENT()){
			raise_error(SEQUENCE_STATEMENT_ERROR);
		}

		_pseudo_code_add_inst(BRN,-1);
		_pseudo_code_fix_bze();//Mery
	}



	if(current_symbol.code == ELSE_TOKEN) {
		next_symbol();
		if(!SEQUENCE_OF_STATEMENT()){
			raise_error(SEQUENCE_STATEMENT_ERROR);
		}

	}


	if(current_symbol.code!=END_TOKEN) 
		raise_error(END_EXPECTED_ERROR);
	next_symbol();

	if(current_symbol.code!=IF_TOKEN) 
		raise_error(IF_EXPECTED_ERROR);
	next_symbol();

	if(current_symbol.code!=SEMICOLON_TOKEN) 
		raise_error(SEMICOLON_EXPECTED_ERROR);

	//Mery
	
	for (int i = 0; i < counter; i++) _pseudo_code_fix_brn();

	//indice_brn = line_number;
	
	next_symbol();
		
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
			if(!RELATION()) {
					raise_error(RELATION_EXPECTED_ERROR);
			}
			
		}
	
	}

	// { or RELATION }
	else if(current_symbol.code==OR_TOKEN) {
		while (current_symbol.code==OR_TOKEN){
			next_symbol();
			if(!RELATION()) {
					raise_error(RELATION_EXPECTED_ERROR);
			}
			
		}
	
	}

	//{ xor RELATION }
	else if (current_symbol.code==XOR_TOKEN) {
		while (current_symbol.code==XOR_TOKEN){
			next_symbol();
			if(!RELATION()) {
					raise_error(RELATION_EXPECTED_ERROR);
			}
			
		}

	}

	return true;
	
	
}

/*
 * RELATION ::= SIMPLE_EXPRESSION [ RELATION_OPERATOR SIMPLE_EXPRESSION ] 
 */

static boolean RELATION(){
	if(!SIMPLE_EXPRESSION()) return false;
		

	token op;//Mery
	op = current_symbol.code;

	if (RELATION_OPERATOR()){

		if(!SIMPLE_EXPRESSION()) {
			raise_error(SIMPLE_EXPRESSION_ERROR);
		}

		if (op == EQUAL_TOKEN) _pseudo_code_add_inst(EQL, 0);//Mery		
		else if (op == LESS_TOKEN) _pseudo_code_add_inst(LSS, 0);//Mery
		else if (op == LESS_EQUAL_TOKEN) _pseudo_code_add_inst(LEQ, 0);//Mery				
		//else if (op == GREATER_TOKEN) _pseudo_code_add_inst(GRT, 0);//Mery
		else if (op == GREATER_EQUAL_TOKEN) _pseudo_code_add_inst(GEQ, 0);//Mery		
		else if (op == DIFF_TOKEN) _pseudo_code_add_inst(NEQ, 0);//Mery

				
	}

	return true;
}

/*
 * SIMPLE_EXPRESSION ::= [ UNARY_ADDING_OPERATOR ] TERM { BINARY_ADDING_OPERATOR TERM }
 */

static boolean SIMPLE_EXPRESSION(){
	token sig = current_symbol.code;
	boolean add_sig = UNARY_ADDING_OPERATOR();

	if(!TERM()) return false;

	if (add_sig) if (sig == SUBSTRACT_TOKEN) _pseudo_code_add_inst(NEG, 0);

	token op;

	op = current_symbol.code;
	
	while (BINARY_ADDING_OPERATOR()){
		if(!TERM()) raise_error(TERM_ERROR);				
		
		if (op == PLUS_TOKEN) _pseudo_code_add_inst(ADD, 0);
		else _pseudo_code_add_inst(SUB, 0);

		op = current_symbol.code;
	}
	
	return true;
}

/*
 * TERM ::= FACTOR { MULTIPLYING_OPERATOR FACTOR } 
 */

static boolean TERM(){
	if(!FACTOR()) return false;
	
	token op = current_symbol.code;

	while (MULTIPLYING_OPERATOR()){
		if(!FACTOR()) raise_error(FACTOR_ERROR);	
		/* Evaluating the value of the operator */
		if (op == MULTIPLY_TOKEN) _pseudo_code_add_inst(MUL, 0);
		if (op == DIVIDE_TOKEN) _pseudo_code_add_inst(DIV, 0);

		op = current_symbol.code;
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
 * PRIMARY ::= READ_NUMBER  | null | name | STRING_LITERAL | CHARACTER_LITERAL | (EXPRESSION) 
 */

static boolean PRIMARY(){
	if (current_symbol.code == CHAR_TOKEN) {
		/* Changing the type of the expression */
		if (current_expression_type < TCHR) current_expression_type = TCHR;
		/* The case we have characters */
		char to_print;
		if (current_symbol.word[1] == '\\') {
			/* It's a special character */
			char to_print;

			switch (current_symbol.word[2]) {
			case 'n':
				to_print = '\n';
				break;

			case 't':
				to_print = '\t';
				break;

			default:
				to_print = '\n';
				break;
			}
		} else {
			to_print = current_symbol.word[1];
		}

		_pseudo_code_add_inst(LDI, to_print);
		next_symbol(); 
		return true;
	} else if(current_symbol.code==INTEGER_TOKEN || current_symbol.code==REAL_NUMBER_TOKEN) {
		/* Changing the type of the expression */
		if (current_symbol.code == INTEGER_TOKEN) if (current_expression_type < TINT) current_expression_type = TINT;
		else if (current_expression_type == REAL_NUMBER_TOKEN) current_expression_type = TFLT;

		/* The case where we are using numbers */
		_pseudo_code_add_inst(LDI, atoi(current_symbol.word));
		next_symbol(); 
		return true;
	}
	else if(current_symbol.code==NULL_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==ID_TOKEN) {
		/* Checking if the suymbol exists */
		if (symbol_exists() == -1) raise_error(SYMBOL_DONT_EXIST);
		/* Getting the type of the variable */
		if (current_expression_type < get_type()) current_expression_type = get_type();

		/* Generating the code to load the varaiable */
		_pseudo_code_add_inst(LDA, get_address());
		_pseudo_code_add_inst(LDV, 0);
		next_symbol();
		return true;
	}
	else if(current_symbol.code==STRING_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==CHAR_TOKEN) { next_symbol(); return true;}

	else if(current_symbol.code==OPEN_PARENTHESIS_TOKEN) { 
		next_symbol(); 
		if(!EXPRESSION()){
			raise_error(EXPRESSION_ERROR);
		} 		
		if(current_symbol.code!=CLOSE_PARENTHESIS_TOKEN){
			raise_error(CLOSE_PARENTHESIS_TOKEN_ERROR);
		}
		else {
			next_symbol();
		}
		return true;
	}

	else return false;
}

/*
 * UNARY_ADDING_OPERATOR ::= + | -
 */

static boolean UNARY_ADDING_OPERATOR(){
	if(current_symbol.code==PLUS_TOKEN) { next_symbol();  true;}
	else if(current_symbol.code==SUBSTRACT_TOKEN) { next_symbol();  true;}
	else return false;
}

/*
 * BINARY_ADDING_OPERATOR ::= + | - | &
 */

static boolean BINARY_ADDING_OPERATOR(){
	if(current_symbol.code==PLUS_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==SUBSTRACT_TOKEN) {next_symbol(); return true;}
	// TODO FIND THE THE NAME OF TOKEN &   else if(current_symbol.code=="&") { return true;}
	else return false;

}

/*
 * MULTIPLYING_OPERATOR ::= * | / | mod / rem
 */

static boolean MULTIPLYING_OPERATOR(){

	if(current_symbol.code==MULTIPLY_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==DIVIDE_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==MOD_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==REM_TOKEN) { next_symbol(); return true;}
	else return false;
	
}

/*
 * CONDITION ::= EXPRESSION
 */
static boolean CONDITION() {
	if(EXPRESSION()) return true;
	return false;

}


/*
 * RELATION_OPERATOR ::=  = | /=  | < | <= | > | >=
 */

static boolean  RELATION_OPERATOR(){
	if(current_symbol.code==EQUAL_TOKEN) { next_symbol(); return true;}
    else if(current_symbol.code==DIFF_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==LESS_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==LESS_EQUAL_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==GREATER_TOKEN) { next_symbol(); return true;}
	else if(current_symbol.code==GREATER_EQUAL_TOKEN) { next_symbol(); return true;}
	else return false;
	
}

