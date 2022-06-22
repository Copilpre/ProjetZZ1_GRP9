# Notre makefile pour le jeu de la vie

OBJ = default_main.o compte_voisin.o grille.o
	
CFLAGS = -lSDL2

Test : $(OBJ)  
	gcc $(OBJ) -o Test

default_main.o : default_main.c compte_voisin.h grille.h 
	gcc -c default_main.c $(CFLAGS)

grille.o : grille.c grille.h
	gcc -c grille.c $(CFLAGS) 

compte_voisin.o : compte_voisin.c compte_voisin.h
	gcc -c compte_voisin.c $(CFLAGS)

clean : 
	rm -f $(OBJ) 
