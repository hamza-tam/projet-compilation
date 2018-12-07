#ifndef ANALYSEUR_LEXICAL_H
#define ANALYSEUR_LEXICAL_H


#include "global.h"
#include "analyseur_lexical.h"
#include "errors.h"

static boolean ASSIGNEMENT_STATEMENT();
static boolean EXIT_STATEMENT();
static boolean PROCEDURE_CALL_STATEMENT();
static boolean SIMPLE_RETURN_STATEMENT();
static boolean IF_STATEMENT();
static boolean EXPRESSION();
static boolean RELATION();
static boolean SIMPLE_EXPRESSION();
static boolean TERM();
static boolean FACTOR();
static boolean PRIMARY();
static boolean UNARY_ADDING_OPERATOR();
static boolean BINARY_ADDING_OPERATOR();
static boolean MULTIPLYING_OPERATOR();
static boolean CONDITION();
static boolean RELATION_OPERATOR();
static boolean _NAME();
#endif
