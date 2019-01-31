#include "pseudo_code.h"


/**
 * First line of the pseudo code
 */
node *pcode = NULL;
node *current_pcode = NULL;


/**
 * Function definitions
 */

void _pseudo_code_init() {
	/* Creating the node */
	pcode = (node*) malloc(sizeof(node));
	
	/* Filling the first node */
	pcode->line.inst      = NOP;
	pcode->line.parameter = 0;

	/* Setting the current node */
	current_pcode = pcode;
}

void _pseudo_code_add_inst(pcode_inst inst, float param) {
	/* Creating the next instruction */
	current_pcode->next = (node*) malloc(sizeof(node));

	/* Changing the current node */
	current_pcode = current_pcode->next;

	/* Filling the current node */
	current_pcode->line.inst      = inst;
	current_pcode->line.parameter = param;
}

void _pseudo_code_write() {
	node *n = pcode;

	/* Opening the file to write in */
	FILE *f = fopen(output_file_name, "w");

	pcode_line *current_line;
	current_line = malloc(sizeof(pcode_line));

	while(n != NULL) {
		current_line = &(n->line);
		fwrite(current_line, sizeof(pcode_inst), 1, f);
		n = n->next;
	}

	fclose(f);
}

void _pseudo_code_print() {
	/* Creating the node to cycle throw nodes */
	node *n = pcode;

	printf("\n================================\n\tPSEUDO CODE\n\n");

	/* Cycle throw the nodes */
	while(n != NULL) {
		printf("Inst code : %d - %f \n", n->line.inst, n->line.parameter);
		n = n->next;
	}

	printf("\nEND OF PSEUDO CODE\n");
}
