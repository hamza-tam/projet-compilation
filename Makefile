
all: compilateur

compilateur: compilateur.o analyseur_lexical.o global.o analyseur_synthaxique.o
	gcc -o compilateur compilateur.o analyseur_lexical.o errors.o -g

compilateur.o: compilateur.c analyseur_lexical.h global.h analyseur_synthaxique.h
	gcc -o compilateur.o -c compilateur.c -g

analyseur_synthaxique.o: analyseur_synthaxique.c analyseur_lexical.h global.h errors.h 
	gcc -o analyseur_synthaxique.o -c analyseur_synthaxique.c -g

analyseur_lexical.o: analyseur_lexical.c global.h errors.h 
	gcc -o analyseur_lexical.o -c analyseur_lexical.c -g

global.o: errors.c errors.h
	gcc -o errors.o -c errors.c -g


clean:
	rm -rf *.o

mrproper:
	rm compilateur