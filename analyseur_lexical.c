#include "analyseur_lexical.h"


int current_index = 0;

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
	current_index = 0;
	current_symbol.word[current_index] = '\0';
}


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
			return true; break;
			
		default: return false; break;
	}
}


/*
 * Checking if a character is a separator
 */
static boolean is_comment() {
	
}


/*
 * Retrieving the next word
 */
void next_symbol() {
	// Read the first character of the file
	next_char();
	
	// search for the grammar
	do {

	} while(current_char != EOF);
}