#ifndef ANALYSEUR_LEXICAL_H
#define ANALYSEUR_LEXICAL_H

#include "global.h"
#include "errors.h"


void read_word();
void read_number();
void read_special();
void read_separator();
void read_comment();
void read_error();


int is_special();
int is_char();
int is_digit();
int is_separator();
int is_comment();


void next_char();
void next_symbol();


#endif