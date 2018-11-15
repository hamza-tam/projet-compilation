#include "analyseur_lexical.h"


int current_index = 0;


/*
 * Retrieving the next word
 */
void next_symbol() {
	// Initialiwing the line count
	current_line = 1;

	// Read the first character of the file
	next_char();
	
	// search for the grammar
	do {

		if (is_char()) read_word();
		else if (is_double_quote()) read_string();
		else if (is_end_of_file()) read_end_of_file();
		else if (is_new_line()) read_new_line();
		else if (is_single_quote()) read_character();
		else if (is_separator()) read_separator();
		else if (is_special()) read_special();
		else read_error();

		flush_word();

	} while(current_char != EOF);
}


/*
 * Reading the next character
 */
static void next_char() {
	current_char = fgetc(file);

	// Storing the current character
	current_symbol.word[current_index] = current_char;
	current_index++;
	current_symbol.word[current_index] = '\0';

	// Verifying not to exceed the buffer
	current_index %= WORD_LENGTH - 1;
}


/*
 * Function to flush the buffer
 */
static void flush_word() {
	current_index = 1;
	current_symbol.word[0] = current_char;
	current_symbol.word[1] = '\0';
}

/*
 * Assigning the token to the current word
 */
static void assign_token() {
	// Do not include the current character in the
	// word used to generate the token
	current_symbol.word[current_index-1] = '\0';

	// TODO assign the token to this word
	printf("%s \n", current_symbol.word);
}



/*************************************************************
**************************************************************
				
					CHECK FUNCTIONS

**************************************************************
*************************************************************/

/*
 * Checking if a character is a character
 */
static boolean is_char() {
	if ( (current_char >= 'a' && current_char <= 'z') || (current_char >= 'A' && current_char <= 'Z') ) {
		return true;
	} else {
		return false;
	}
}

/*
 * Checking if a character is a Numeric
 */
static boolean is_numeric() {
	if (current_char >= '0' && current_char <= '9') {
		return true;
	} else {
		return false;
	}
}

/*
 * Checking if a character is a special character
 */
static boolean is_special() {
	switch (current_char) {
		case ':':
		case '=':
		case '+':
		case '-':
		case '*':
		case ';':
		case '(':
		case ')':
			return true; break;

		default: return false; break;
	}
}


/*
 * Checking if a character is a separator
 */
static boolean is_separator() {
	switch (current_char) {
		case ' ' :
		case '\n':
		case '\t':
		case '\r':
			return true; break;
			
		default: 
			return false; break;
	}
}


/*
 * Checking if it's an acceptable character in a string
 */
static boolean is_acceptable_char() {
	switch (current_char) {
		case '_':
			return true; break;

		default:
			return false; break;
	}
}


/*
 * Checking if it's a double quote
 */
static boolean is_double_quote() {
	if (current_char == '"') 
		return true;

	return false;
}



/*
 * Checking if it's a double quote
 */
static boolean is_single_quote() {
	if (current_char == '\'') 
		return true;

	return false;
}


/*
 * Checking if it's a new line
 */
static boolean is_new_line() {
	if (current_char == '\n') 
		return true;

	return false;
}

/*
 * Checking if we have reached the end of the file
 */
static boolean is_end_of_file() {
	if (current_char == EOF) 
		return true;

	return false;
}

/*
 * Checking if a character is a separator
 */
static boolean is_comment() {
	
}



/*************************************************************
**************************************************************
				
				FUNCTIONS TO ANALYSE THE CODE

**************************************************************
*************************************************************/

/*
 * Starting reading a word
 */
static void read_word() {

	// Moving to the next character
	next_char();

	// Looping through the characters
	while (is_acceptable_char() || is_char() || is_numeric()) {
		next_char();
	}

	// Assigning the token
	assign_token();

}


/*
 * Starting reading a string
 */
static void read_string() {

	// Moving to the next character
	next_char();

	// Looping throught the characters
	while(!is_double_quote()) {
		next_char();
	}

	next_char();

	assign_token();
}


/*
 * Reading special characters
 */
static void read_special() {

	// Moving to the next character
	next_char();

	assign_token();
}


/*
 * Start reading a character
 */
static void read_character() {
	// moving to the next character
	next_char();

	if (is_char()) next_char();
	else {
		raise_error(CHARACTER_EXPECTED_ERROR);
		next_char();
		return;
	}

	// Reading the next single quote
	if (is_single_quote()) {
		next_char();
		assign_token();
	} else {
		raise_error(SINGLE_QUOTE_EXPECTED_ERROR);
	}
}


/*
 * Reading the end of file
 */
static void read_end_of_file() {
	strcpy(current_symbol.word, "END OF FILE");
	assign_token();
}


/*
 * Reading separators
 */
static void read_separator() {
	next_char();
}


/*
 * Reading a new line
 */
static void read_new_line() {
	current_line++;
	next_char();
}

/*
 * Reading an unrocognized character
 */
static void read_error() {
	raise_error(UNRECOGNIZED_CHARACTER_ERROR);
	next_char();
}