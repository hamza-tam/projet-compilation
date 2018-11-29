#ifndef ANALYSEUR_SYNTHAXIQUE_H
#define ANALYSEUR_SYNTHAXIQUE_H


#include "analyseur_lexical.h"

boolean PROGRAM();


static boolean DECLARATIVE_PART();
static boolean DECLARATIVE_ITEM();
static boolean BASIC_DECLARATIVE_ITEM();
static boolean BODY();
static boolean HANDLED_STATEMENT_OF_SEQUENCE();
static boolean SEQUENCE_OF_STATEMENT();
static boolean STATEMENT();
static boolean SIMPLE_STATEMENT();
static boolean ASSIGNEMENT_STATEMENT();
static boolean EXIT_STATEMENT();
static boolean COMPOUND_STATEMENT();
static boolean EXPRESSION();
static boolean CONDITION();


#endif