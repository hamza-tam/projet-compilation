#include "interpreteur.h"


int pc = 1;

int main(int argc, char** argv) {
	/* Loading the file containing the Pcode */
	strcpy(interpreter_input_file_name,"output");

	_pseudo_code_init();
	_pile_init();

	_pseudo_code_read_text();

	_pseudo_code_print_text();

	_interpret_pseudo_code();

	return 0;
}


void _interpret_pseudo_code() {
	/* The list of instructions to interpret 
	 * ADD, Perform addition on the top spots of the stack 
	 * SUB, Perform substration on the top spots of the stack 
	 * MUL, Perform multiplication on the top spots of the stack 
	 * DIV, Perform division on the top spots of the stack 
	 * EQL, Check if the the two spots on the top of the stack are equal 
	 * NEQ, Check if the the two spots on the top of the stack are not equal 
	 * GTR,
	 * LSS, 
	 * GEQ, 
	 * LEQ, 
	 * PRN, 
	 * INN, 
	 * INT, Asks for a number of memory spots to be reserved 
	 * LDI, 
	 * LDA, // Chargement de l'adresse
	 * LDV, // Chargement de la valeur
	 * STO, // Stockage de la valeur dans une adresse
	 * BRN, 
	 * BZE, 
	 * HLT, End of the program 
	 * PRI, Print an int
	 * PRC, Print char 
	 * NOP, No operation 
	 */

	 /* Init the interpreter parameters */
	pc = 1;
	boolean end = false;
	current_node = pcode;

	/* Varaibles that will be needed during the interpretation */
	float hold;

	while(!end) {
		/* Getting the current instruction */
		_interpreter_get_current_node();

		/* processing the instruction */
		switch (current_node->line.inst) {

		case LDI:
			_pile_add(current_node->line.parameter);
			pc++;
			break;

		case ADD:
			hold = _pile_top();
			hold += _pile_top();
			_pile_add(hold);
			pc++;
			break;

		case SUB:
			hold = _pile_top();
			hold = _pile_top() - hold;
			_pile_add(hold);
			pc++;
			break;

		case MUL:
			hold = _pile_top();
			hold *= _pile_top();
			_pile_add(hold);
			pc++;
			break;

		case DIV:
			hold = _pile_top();
			hold = _pile_top() / hold;
			_pile_add(hold);
			pc++;
			break;

		case EQL:
			hold = _pile_top();
			if (hold == _pile_top()) _pile_add(1);
			else _pile_add(0);
			pc++;
			break;

		case NEQ:
			hold = _pile_top();
			if (hold != _pile_top()) _pile_add(1);
			else _pile_add(0);
			pc++;
			break;

		case GTR:
			hold = _pile_top();
			if (hold > _pile_top()) _pile_add(1);
			else _pile_add(0);
			pc++;
			break;

		case LSS:
			hold = _pile_top();
			if (hold < _pile_top()) _pile_add(1);
			else _pile_add(0);
			pc++;
			break;

		case GEQ:
			hold = _pile_top();
			if (hold >= _pile_top()) _pile_add(1);
			else _pile_add(0);
			pc++;
			break;

		case LEQ:
			hold = _pile_top();
			if (hold <= _pile_top()) _pile_add(1);
			else _pile_add(0);
			pc++;
			break;

		case PRF:
			printf("%f", _pile_top());
			pc++;
			break;

		case RDF:
			scanf("%f", &hold);
			_pile_add(hold);
			pc++;
			break;

		case INT:
			hold = current_node->line.parameter; 
			for (int i = 0; i < (int) hold; i++) _pile_add(0);
			pc++;
			break;

		case LDA:
			_pile_add(current_node->line.parameter);
			pc++;
			break;

		case LDV:
			_pile_add(_pile_get((int) _pile_top()));
			pc++;
			break;

		case STO:
			hold = _pile_top();
			_pile_set((int) _pile_top(), hold);
			pc++;
			break;

		case BZE:
			if (_pile_top() == 0) pc = (int) current_node->line.parameter;
			else pc++;
			break;

		case BRN:
			pc = (int) current_node->line.parameter;
			break;

		case HLT:
			end = true;
			break;

		case PRI:
			printf("%i", (int) _pile_top());
			pc++;
			break;

		case PRC:
			printf("%c", (char) _pile_top());
			pc++;
			break;

		case NEG:
			_pile_add((-1) * _pile_top());
			pc++;
			break;

		case NBZ:
			if (_pile_top() != 0) pc = (int) current_node->line.parameter;
			else pc++;
			break;

		default:
			end = true;
			break;
		
		}
		_pile_show();
	}

}


void _interpreter_get_current_node() {
	while (pc != current_node->line.line_number) {
		if (pc > current_node->line.line_number) current_node = current_node->next; 
		else current_node = current_node->previous;
	}
}
