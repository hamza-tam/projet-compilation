#include <stdio.h>
#include <stdlib.h>
#include "analyseur_lexical.h"
#include "global.h"

int main() {

	file = fopen("test2.ada", "r");
	next_symbol();
	fclose(file);

	return 0;
}
