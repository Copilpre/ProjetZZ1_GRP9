#include "table.h"
#include <SDL2/SDL.h>

#define TAILLE 9

typedef struct table {
	int survie[TAILLE][TAILLE] ;
	int naissance[TAILLE][TAILLE] ;
} table_t ;



