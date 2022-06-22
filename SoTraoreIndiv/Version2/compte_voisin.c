#include "compte_voisin.h"
#define TAILLE 20

// Cas de la grille limitée

int nbVoisinLimit(int ** tab, int i, int j) {
	int compteur = 0 ;
	if ((i-1 > -1 && j-1 > -1) && (tab[i-1][j-1] == 1))
		compteur++ ; // Haut + Gauche

	if ((i-1 > -1) && (tab[i-1][j] == 1))
		compteur++ ; // Haut

	if ((i-1 > -1 && j+1 < TAILLE) && (tab[i-1][j+1] == 1))
		compteur++ ; // Haut + Droite

	if ((j+1 < TAILLE) && (tab[i][j+1] == 1))
		compteur++ ; // Droite

	if ((j-1 > -1) && (tab[i][j-1] == 1))
		compteur++ ; // Gauche

	if ((i+1 < TAILLE && j-1 > -1) && (tab[i+1][j-1] == 1))
		compteur++ ; // Bas + Gauche

	if ((i+1 < TAILLE) && (tab[i+1][j] == 1))
		compteur++ ; // Bas

	if ((i+1 < TAILLE && j+1 < TAILLE) && (tab[i+1][j+1] == 1))
		compteur++ ; // Bas + Droite

	return compteur ;
}

// Cas de la grille sous forme de thor

int nbVoisinTore(int ** tab, int i, int j) {
	int compteur = 0 ;
	
	if (i-1 > -1) {
		if (j-1 > -1) {
			if (tab[i-1][j-1] == 1)
				compteur++ ; // Haut + Gauche
		} else {
			if (tab[i-1][TAILLE-1] == 1)
				compteur++ ;
		}
	} else {
		if (j-1 > -1) {
			if (tab[TAILLE-1][j-1] == 1) compteur++ ;
		} else {
			if (tab[TAILLE-1][TAILLE-1] == 1) 
				compteur++ ;
		}
	}

	if (i-1 > -1) { 
		if ((tab[i-1][j] == 1)) 
			compteur++ ; // Haut
	} else {
		if (tab[TAILLE-1][j] == 1) compteur++ ;
	}

	if (i-1 > -1) { 
		if (j+1 < TAILLE) {
			if (tab[i-1][j+1] == 1)
				compteur++ ; // Haut + Droite
		} else {
			if (tab[i-1][0] == 1) 
				compteur++ ;
		}
	} else {
		if (j+1 < TAILLE) {
			if (tab[TAILLE-1][j+1] == 1) 
				compteur++ ;
		} else {
			if (tab[TAILLE-1][0] == 1) 
				compteur++ ;
		}
	}

	if (j+1 < TAILLE) {
		if (tab[i][j+1] == 1)
			compteur++ ; // Droite
	} else {
		if (tab[i][0] == 1) compteur++ ;
	}

	if (i-1 > -1) {
		if (tab[i-1][j] == 1)
			compteur++ ; // Gauche
	} else {
		if (tab[TAILLE-1][j] == 1) compteur++ ;
	}

	if (i+1 < TAILLE) {
		if (j-1 > -1) {
			if (tab[i+1][j-1] == 1) compteur++ ;
		} else {
			if (tab[i+1][TAILLE-1] == 1)
				compteur++ ; // Bas + Gauche
		}
	} else {
		if (j-1 > -1) {
			if (tab[0][j-1] == 1)  compteur++ ;
		} else {
			if (tab[0][TAILLE-1] == 1) 
				compteur++ ;
		}
	}

	if (i+1 < TAILLE) {
		if (tab[i+1][j] == 1) 
			compteur++ ; // Bas
	} else {
		if (tab[0][j] == 1) compteur++ ;
	}

	if (i+1 < TAILLE) {
		if (j+1 < TAILLE) {
			if (tab[i+1][j+1] == 1)
				compteur++ ; // Bas + Droite
		} else {
			if (tab[i+1][0] == 1) 
				compteur++ ;
		}
	} else {
		if (j+1 < TAILLE) {
			if (tab[0][j+1] == 1)
				compteur++ ; // Bas + Droite
		} else {
			if (tab[0][0] == 1) 
				compteur++ ;
		}
	}

	return compteur ;
}
