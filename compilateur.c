#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "global.h"
#include "analyseur_synthaxique.h"


int main(int argc, char** argv) {
	/* Open the file */
	assert(argc == 2);
	file = fopen(argv[1], "r");

	/* The name of the output file */
	if (argc == 3) strcpy(argv[2], "output");
	else strcpy(output_file_name, "output");

	/* Starting compilation */
	PROGRAM();
	fclose(file);
	
	printf("Compiler Finished \n");

	return 0;
}
