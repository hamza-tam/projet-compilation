#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "analyseur_synthaxique.h"


int main() {
	/* The name of the output file */
	strcpy(output_file_name, "output");

	file = fopen("test2.ada", "r");
	PROGRAM();
	fclose(file);

	return 0;
}
