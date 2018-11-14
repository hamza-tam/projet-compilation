
all: compilateur

compilateur: compilateur.o analyseur_lexical.o
	gcc -o compilateur compilateur.o analyseur_lexical.o -g

compilateur.o: compilateur.c analyseur_lexical.h global.h
	gcc -o compilateur.o -c compilateur.c -g

analyseur_lexical.o: analyseur_lexical.c global.h errors.h
	gcc -o analyseur_lexical.o -c analyseur_lexical.c -g

errors.o: errors.c errors.h
	gcc -o errors.o -c errors.c -g

clean:
	rm -rf *.o

mrproper:
	rm compilateur