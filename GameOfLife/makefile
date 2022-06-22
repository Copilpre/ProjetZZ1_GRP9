# Notre makefile pour le jeu de la vie

OBJ = main.o dessin.o rechercheVoisin.o menuT.o
	
CFLAGS = -Wall -Wextra -g

prog : main.o dessin.o rechercheVoisin.o menuT.o
	gcc $(OBJ) -o prog

main.o : main.c dessin.o rechercheVoisin.o menuT.o
	gcc -c main.c $(CFLAGS)

dessin.o : dessin.c dessin.h
	gcc -c dessin.c $(CFLAGS) 

rechercheVoisin.o : rechercheVoisin.c rechercheVoisin.o
	gcc -c rechercheVoisin.c $(CFLAGS)

menuT.o : menuT.c menuT.o
	gcc -c menuT.c $(CFLAGS)

clean : 
	rm -f $(OBJ) 
