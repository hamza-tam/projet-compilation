
all: compilateur

compilateur: compilateur.o analyseur_lexical.o
	gcc -o compilateur compilateur.o analyseur_lexical.o

compilateur.o: compilateur.c analyseur_lexical.h
	gcc -o compilateur.o -c compilateur.c  

analyseur_lexical.o: analyseur_lexical.c
	gcc -o analyseur_lexical.o -c analyseur_lexical.c 

clean:
	rm -rf *.o

mrproper:
	rm compilateur