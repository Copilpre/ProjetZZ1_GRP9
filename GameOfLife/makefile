# Notre makefile pour le jeu de la vie

OBJ = main.o dessin.o recherche_voisins.o menuT.o
	
CFLAGS = -Wall -Wextra -g

prog : main.o dessin.o recherche_voisins.o menuT.o
	gcc $(OBJ) -o prog

main.o : main.c dessin.h recherche_voisins.o menuT.h
	gcc -c main.c $(CFLAGS)

dessin.o : dessin.c dessin.h
	gcc -c dessin.c $(CFLAGS) 

recherche_voisins.o : recherche_voisins.c recherche_voisins.h
	gcc -c recherche_voisins.c $(CFLAGS)

menuT.o : menuT.c menuT.h
	gcc -c menuT.c $(CFLAGS)

clean : 
	rm -f $(OBJ) 
