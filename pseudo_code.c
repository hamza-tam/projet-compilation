#include "pseudo_code.h"


/**
 * Function definitions
 */

void _pseudo_code_init() {
	/* Init the line number */
	line_number = 0;

	pcode = NULL;
	current_pcode = NULL;

	/* Creating the node */
	pcode = (node*) malloc(sizeof(node));
	
	/* Filling the first node */
	pcode->line.line_number = line_number++;
	pcode->line.inst        = NOP;
	pcode->line.parameter   = 0;
	pcode->previous         = NULL;
	pcode->next             = NULL;

	/* Setting the current node */
	current_pcode = pcode;
}

void _pseudo_code_add_inst(pcode_inst inst, float param) {
	/* Creating the next instruction */
	current_pcode->next = (node*) malloc(sizeof(node));

	/* Setting this node as the previous of the next */
	current_pcode->next->previous = current_pcode;

	/* Changing the current node */
	current_pcode = current_pcode->next;

	/* Filling the current node */
	current_pcode->line.line_number = line_number++;
	current_pcode->line.inst        = inst;
	current_pcode->line.parameter   = param;
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

void _pseudo_code_write_text() {
	node *n = pcode->next;

	/* Opening the file */
	FILE *f = fopen(output_file_name, "w");

	pcode_line *current_line = malloc(sizeof(pcode_line));

	while(n != NULL) {
		current_line = &(n->line);
		fprintf(f, "%i %i %f \n", current_line->line_number, current_line->inst, current_line->parameter);
		n = n->next;
	} 

	fclose(f);
}


void _pseudo_code_read_text() {
	/* This is the root node of the list */
	node *n = pcode;

	/* The file that contains the pcode */
	FILE *f = fopen(interpreter_input_file_name, "r");

	pcode_line *current_line = malloc(sizeof(pcode_line));

	/* Reading all the file */
	while(fscanf(f, "%i %i %f \n", &(current_line->line_number), &(current_line->inst), &(current_line->parameter)) != EOF) {
		/* Storing the line */
		_pseudo_code_add_inst(current_line->inst, current_line->parameter);
	}

}

void _pseudo_code_print() {
	/* Creating the node to cycle throw nodes */
	node *n = pcode;

	printf("\n================================\n\tPSEUDO CODE\n\n");

	/* Cycle throw the nodes */
	while(n != NULL) {
		printf("Inst code : %2.d -- %d - %f \n", n->line.line_number, n->line.inst, n->line.parameter);
		n = n->next;
	}

	printf("\nEND OF PSEUDO CODE\n");
}


void _pseudo_code_fix_bze() {
	boolean fixed = false;

	node *n = current_pcode;

	/* looking for a BZE with a missing argument */
	while (n != NULL && !fixed) {
		if (n->line.inst == BZE && n->line.parameter == -1) {
			fixed = true;
			n->line.parameter = line_number;
		}
		/* Going to the previous instruction */
		n = n->previous;
	}	
}

void _pseudo_code_fix_brn() {
	boolean fixed = false;

	node *n = current_pcode;

	/* looking for a BZE with a missing argument */
	while (n != NULL && !fixed) {
		if (n->line.inst == BRN && n->line.parameter == -1) {
			fixed = true;
			n->line.parameter = line_number;
		}
		/* Going to the previous instruction */
		n = n->previous;
	}	
}


void _pseudo_code_fix_nbz() {
	boolean fixed = false;

	node *n = current_pcode;

	/* looking for a BZE with a missing argument */
	while (n != NULL && !fixed) {
		if (n->line.inst == NBZ && n->line.parameter == -1) {
			fixed = true;
			n->line.parameter = line_number;
		}
		/* Going to the previous instruction */
		n = n->previous;
	}	
}
