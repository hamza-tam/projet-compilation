all: compilateur

compilateur: compilateur.o analyseur_lexical.o global.o analyseur_synthaxique.o symbol_table.o pseudo_code.o
	gcc -o compilateur compilateur.o analyseur_lexical.o analyseur_synthaxique.o errors.o symbol_table.o pseudo_code.o -g

compilateur.o: compilateur.c analyseur_synthaxique.h global.h analyseur_synthaxique.h symbol_table.h pseudo_code.h
	gcc -o compilateur.o -c compilateur.c -g

analyseur_synthaxique.o: analyseur_synthaxique.c analyseur_synthaxique.h analyseur_lexical.h global.h errors.h symbol_table.h
	gcc -o analyseur_synthaxique.o -c analyseur_synthaxique.c -g

pseudo_code.o: pseudo_code.h pseudo_code.c global.h
	gcc -o pseudo_code.o -c pseudo_code.c -g

symbol_table.o: symbol_table.c symbol_table.h global.h
	gcc -std=c99  -o symbol_table.o -c symbol_table.c -g	

analyseur_lexical.o: analyseur_lexical.c global.h errors.h 
	gcc -o analyseur_lexical.o -c analyseur_lexical.c -g

global.o: errors.c errors.h
	gcc -o errors.o -c errors.c -g

clean:
	rm -rf *.o *.c~ *.h~ *.ada~

bp: clean mrproper clean_output
	rm interpreteur

clean_output: output
	rm output

mrproper:
	rm compilateur

interpreteur: interpreteur.o pile.o pseudo_code.o
	gcc -o interpreteur interpreteur.o pile.o pseudo_code.o -g

interpreteur.o: interpreteur.c interpreteur.h pile.h
	gcc -std=c99 -o interpreteur.o -c interpreteur.c -g

pile.o: pile.c pile.h
	gcc -std=c99 -o pile.o -c pile.c -g


