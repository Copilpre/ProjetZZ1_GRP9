# Notre makefile pour le jeu de la vie

OBJ = main.o grille.o recherche_voisins.o menuT.o
	
CFLAGS = -Wall -Wextra -g -lSDL2 

prog : main.o grille.o recherche_voisins.o menuT.o affichageSDL.o
	gcc $(OBJ) -o prog $(CFLAGS)

main.o : main.c menuT.h affichageSDL.h
	gcc -c main.c -o main.o 

menuT.o : menuT.c menuT.h grille.h
	gcc -c menuT.c -o menuT.o 

grille.o : grille.c grille.h recherche_voisins.h
	gcc -c grille.c -o grille.o 

recherche_voisins.o : recherche_voisins.c recherche_voisins.h affichageSDL.h
	gcc -c recherche_voisins.c -o recherche_voisins.o 

affichageSDL.o : affichageSDL.c affichageSDL.h
	gcc -c affichageSDL.c -o affichageSDL.o 
clean : 
	rm -f $(OBJ)
