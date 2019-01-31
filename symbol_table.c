#include "symbol_table.h"


/*
 * Initializing the symbol table
 */
void init_symbol_table() {
	symbol_table_size = 0;
	symbol_table_max_size = 10;

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
		symbol_table[symbol_table_size].address = symbol_table_size;

		
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
 * Printing into the screen the symbol table
 */
void show_symbol_table() {
	printf("===============================\n");
	printf("Symbol table \n");
	printf("===============================\n");

	for(int i = 0; i < symbol_table_size; i++) {
		printf("--> %s \n", symbol_table[i].word);
	}
}
