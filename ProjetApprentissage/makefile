
GC = gcc -c 
OBJ = main.o pile.o qtable.o
CLFAGS = -Wall -Wextra -g

main : $(OBJ)
	$(GC) $(CFLAGS) $(OBJ) -o main

main.o : main.c pile.h pile.h qtable.h
	$(GC) main.c $(CFLAGS) -o main.o 

pile.o : pile.c pile.h
	$(GC) pile.c $(CFLAGS) -o pile.o  

qtable.o : qtable.c qtable.h pile.h
	$(GC) qtable.c $(CFLAGS) -o pile.o
	
clean :
	rm -f $(OBJ) 
