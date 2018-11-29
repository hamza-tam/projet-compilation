#include <stdio.h>
#include <stdlib.h>
#include "analyseur_synthaxique.h"
#include "global.h"

int main() {

	file = fopen("test2.ada", "r");
	PROGRAM();
	fclose(file);

	return 0;
}
