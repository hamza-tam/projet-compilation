#ifndef INTERPRETEUR_H
#define INTERPRETEUR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "pseudo_code.h"
#include "pile.h"


/* The instruction counter */
node *current_node;

void _interpret_pseudo_code();
void _interpreter_get_current_node();


#endif
