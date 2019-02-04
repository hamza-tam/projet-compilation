#include "symbol_table.h"


/*
 * Initializing the symbol table
 */
void init_symbol_table() {
	symbol_table_size = 0;
	symbol_table_max_size = 10;
	current_address = 0;

	symbol_table = malloc(symbol_table_max_size * sizeof(struct _stored_symbol));
}


/*
 * Change the size of the symbol table
 */
static void change_size() {
	symbol_table_max_size += 10;
	symbol_table = realloc(symbol_table, symbol_table_max_size * sizeof(struct _stored_symbol));
} 


/*
 * Adds the symbol to the symbol table
 */
boolean add_symbol(symbol_type t) {
	// Checking first that the symbol extsts in the symbol table
	if (symbol_exists() == -1) {
		// If there are no more space in the symbol table
		if (symbol_table_size > symbol_table_max_size) {
			change_size();
		}
		// adding the symbol to the table
		strcpy(symbol_table[symbol_table_size].word, current_symbol.word);
		symbol_table[symbol_table_size].type = t;
		symbol_table[symbol_table_size].is_const = false;
		symbol_table[symbol_table_size].offset = address_offset;

		if (t == TVAR) symbol_table[symbol_table_size].address = address_offset + current_address++;
		
		// Incrementing the symbol table size
		symbol_table_size++;
	} 
	else 
		return false;
}


/*
 * Check if the current symbol already exists in the symbol table
 * return the index of the symbol in the table if it exists
 * or return -1 if the symbol does not exists in the table 
 */
int symbol_exists() {
	for (int i = 0; i < symbol_table_size; i++) {
		if ( strcmp(symbol_table[i].word, current_symbol.word) == 0 ) 
			return i;
	}

	return -1;
}

/*
 * Get the adress of the current symbol
 */
int get_address() {
	for (int i = 0; i < symbol_table_size; i++) {
		if ( strcmp(symbol_table[i].word, current_symbol.word) == 0 ) 
			return symbol_table[i].address;
	}

	return -1;
}


symbol_type get_type() {
	for (int i = 0; i < symbol_table_size; i++) {
		if ( strcmp(symbol_table[i].word, current_symbol.word) == 0 ) 
			return symbol_table[i].type;
	}

	return -1;
}

/*
 * Check if a specific symbol already exists in the symbol table
 * return the index of the symbol in the table if it exists
 * or return -1 if the symbol does not exists in the table 
 */
int _specific_symbol_exists(char *symbol) {
	for (int i = 0; i < symbol_table_size; i++) {
		if ( strcmp(symbol_table[i].word, symbol) == 0 ) 
			return i;
	}

	return -1;
}


/*
 * Printing into the screen the symbol table
 */
void show_symbol_table() {
	printf("\n\n");
	printf("===============================\n");
	printf("=== Table des symboles ========\n");
	printf("===============================\n");
	printf("  Symbole  | Tp |  @ | Of | Ct\n");
	printf("-------------------------------\n");

	for(int i = 0; i < symbol_table_size; i++) {
		printf("%10s | %2i | %2i | %2i | %2i \n", symbol_table[i].word, symbol_table[i].type, symbol_table[i].address, symbol_table[i].offset, symbol_table[i].is_const);
	}
}

/*
 * Changing the last symbol typ
 */
void set_last_symbol_type(symbol_type t) {
	symbol_table[symbol_table_size - 1].type = t;
}


/*
 * Setting the last symbol address
 */
void set_last_symbol_address(int address) {
	symbol_table[symbol_table_size - 1].address = address;
}

/*
 * Set the last symbol to const
 */
void set_last_symbol_const() {
	symbol_table[symbol_table_size - 1].is_const = true;
}

/*
 * Getting the address of the last inserted symbol in the table
 */
int get_last_symbol_address() {
	return symbol_table[symbol_table_size - 1].address;
}

/* Retrieving the information if he is a constatnt */
boolean is_current_symbol_const() {
	return symbol_table[symbol_exists()].is_const;
}

/*
 * Getting the address of the first procedure in the symbol table
 */
int get_first_procedure_address() {
	int i = 0;
	while(symbol_table[i].type != TPROC) i++;
	return symbol_table[i].address;
}

/*
 * Get the number of variables to clean
 */
int _symbol_table_to_free(int start) {
	int i = start;
	int n = 0;

	while (symbol_table[i].offset >= address_offset && i <= symbol_table_size) {
		if ( (symbol_table[i].type == TVAR || symbol_table[i].type == TINT || symbol_table[i].type == TFLT || symbol_table[i].type == TCHR) && (symbol_table[i].offset == address_offset) ) n++;
		i++;
	}

	return n;
}