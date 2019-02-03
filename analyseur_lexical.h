#ifndef ANALYSEUR_LEXICAL_H
#define ANALYSEUR_LEXICAL_H


#include "global.h"
#include "errors.h"


static char keywords[TOKEN_LIST_SIZE][20] = {

	// Real key words of the language
	"abort",
	"abs", 
	"abstract", 
	"accept",
	"access",
	"aliased",
	"all",
	"and",
	"array",
	"at", 
	"begin", 
	"body",
	"case",
	"constant",
	"declare", 
	"delay", 
	"delta",
	"digits", 
	"do", 
	"else", 
	"elsif", 
	"end", 
	"entry", 
	"exception", 
	"exit", 
	"for", 
	"function", 
	"generic", 
	"goto", 
	"if", 
	"in", 
	"inout",
	"interface", 
	"is", 
	"limited", 
	"loop", 
	"mod", 
	"new", 
	"not", 
	"null", 
	"of", 
	"or", 
	"others", 
	"out", 
	"overriding", 
	"package", 
	"pragma", 
	"private", 
	"procedure", 
	"protected", 
	"raise", 
	"range", 
	"record", 
	"rem",
	"renames", 
	"requeue", 
	"return", 
	"reverse", 
	"select", 
	"separate", 
	"some", 
	"subtype", 
	"synchronized", 
	"tagged", 
	"task", 
	"terminate", 
	"then", 
	"type", 
	"until", 
	"use", 
	"when", 
	"while", 
	"with", 
	"xor",

	// Symbols used in the language

	"=",
	"+",
	"-",
	"*",
	"/",
	":=",
	">",
	">=",
	"<",
	"<=",
	"(",
	")",
	";",
	":",
	"/=",

	// Added keywords
	"Put",
	"Get",
	"Integer",
};


 void read_word();
static void read_number();
static void read_special();
static void read_separator();
static void read_comment();
static void read_error();
static void read_string();
static void read_character();
static void read_end_of_file();
static void read_new_line();


static boolean is_special();
static boolean is_char();
static boolean is_numeric();
static boolean is_separator();
static boolean is_comment();
static boolean is_double_quote();
static boolean is_single_quote();
static boolean is_end_of_file();
static boolean is_new_line();
static boolean is_point_char();
static boolean is_second_special();


static void assign_token(token);
static void next_char();
static void flush_word();

void next_symbol();
void init_symbol();

/*
*functions relative to a read_number function
*/
static void read_numeral();
static void read_decimal_literal();



#endif
