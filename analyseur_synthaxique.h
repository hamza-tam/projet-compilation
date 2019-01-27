#ifndef ANALYSEUR_SYNTHAXIQUE_H
#define ANALYSEUR_SYNTHAXIQUE_H


#include "analyseur_lexical.h"
#include "symbol_table.h"
#include "pseudo_code.h"


boolean PROGRAM();


static boolean DECLARATIVE_PART();
static boolean DECLARATIVE_ITEM();
static boolean BASIC_DECLARATIVE_ITEM();
static boolean BODY();

static boolean HANDLED_STATEMENT_OF_SEQUENCE();
static boolean SEQUENCE_OF_STATEMENT();
static boolean STATEMENT();
static boolean SIMPLE_STATEMENT();
static boolean COMPOUND_STATEMENT();

static boolean ASSIGNEMENT_OR_PROCEDURE_CALL_STATEMENT();
static boolean ASSIGNEMENT_OR_PROCEDURE_CALL_END_STATEMENT();
static boolean ASSIGNEMENT_STATEMENT();
static boolean PROCEDURE_CALL_STATEMENT();
static boolean EXIT_STATEMENT();
static boolean SIMPLE_RETURN_STATEMENT();

static boolean EXPRESSION();
static boolean CONDITION();


#endif