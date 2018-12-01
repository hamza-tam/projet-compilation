
all: compilateur

compilateur: compilateur.o analyseur_lexical.o global.o analyseur_synthaxique.o symbol_table.o
	gcc -o compilateur compilateur.o analyseur_lexical.o analyseur_synthaxique.o errors.o symbol_table.o -g

compilateur.o: compilateur.c analyseur_synthaxique.h global.h analyseur_synthaxique.h
	gcc -o compilateur.o -c compilateur.c -g

analyseur_synthaxique.o: analyseur_synthaxique.c analyseur_synthaxique.h analyseur_lexical.h global.h errors.h symbol_table.h
	gcc -o analyseur_synthaxique.o -c analyseur_synthaxique.c -g

analyseur_lexical.o: analyseur_lexical.c global.h errors.h 
	gcc -o analyseur_lexical.o -c analyseur_lexical.c -g

global.o: errors.c errors.h
	gcc -o errors.o -c errors.c -g

symbol_table.o: symbol_table.c symbol_table.h global.h
	gcc -o symbol_table.o -c symbol_table.c -g	

clean:
	rm -rf *.o *.c~ *.h~ *.ada~

mrproper:
	rm compilateur