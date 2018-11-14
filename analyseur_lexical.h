#ifndef ANALYSEUR_LEXICAL_H
#define ANALYSEUR_LEXICAL_H

#include "global.h"
#include "errors.h"

static void read_word();
static void read_number();
static void read_special();
static void read_separator();
static void read_comment();
static void read_error();


static boolean is_special();
static boolean is_char();
static boolean is_numeric();
static boolean is_separator();
static boolean is_comment();


static void next_char();
static void flush_word();

void next_symbol();


#endif