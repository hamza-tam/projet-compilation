#ifndef TABLE_SYMBOLS_H
#define TABLE_SYMBOLS_H

#include "global.h"


void init_symbol_table();
boolean add_symbol(symbol_type t);
int symbol_exists();
int specific_symbol_exists(char *symbol);
void show_symbol_table();
int get_address();
symbol_type get_type();

void set_last_symbol_type(symbol_type t);
void set_last_symbol_const();
void set_last_symbol_address(int address);

int _symbol_table_to_free(int start);

boolean is_current_symbol_const();
symbol_type get_current_symbol_type();
int get_last_symbol_address();
int get_first_procedure_address();


static void change_size();

#endif 