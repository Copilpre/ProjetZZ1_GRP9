
GC = gcc
OBJ = main.o pile.o qtable.o
CLFAGS = -Wall -Wextra -g 

prog : $(OBJ)
	$(GC) $(OBJ) -o prog  -g -lm

main.o : main.c pile.h qtable.h
	$(GC) main.c -c $(CFLAGS) -o main.o 

qtable.o : qtable.c qtable.h pile.h
	$(GC) qtable.c -c $(CFLAGS) -lm -o qtable.o

pile.o : pile.c pile.h
	$(GC) pile.c -c $(CFLAGS) -o pile.o  	
	
clean :
	rm -f $(OBJ) prog 
