Jeu: main.o matriceensql.o jeudelavie.o figuresjeudelavie.o
	gcc -o Jeu jeudelavie.o main.o matriceensql.o figuresjeudelavie.o `sdl-config --cflags --libs` 

matriceensql.o:matriceensql.c 
	gcc -c matriceensql.c -Wall -Wextra -o matriceensql.o `sdl-config --cflags --libs`

jeudelavie.o : jeudelavie.c
	gcc -c jeudelavie.c -Wall -Wextra -o jeudelavie.o

main.o : main.c matriceensql.h jeudelavie.h figuresjeudelavie.h
	gcc -c main.c -Wall -Wextra -o main.o `sdl-config --cflags --libs`

figuresjeudelavie.o : figuresjeudelavie.c
	gcc -c figuresjeudelavie.c -Wall -Wextra -o figuresjeudelavie.o

