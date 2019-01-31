#ifndef TABLE_SYMBOLS_H
#define TABLE_SYMBOLS_H

#include "global.h"


void init_symbol_table();
boolean add_symbol(symbol_type t);
int symbol_exists();
int specific_symbol_exists(char *symbol);
void show_symbol_table();
int get_address();


static void change_size();

#endif 