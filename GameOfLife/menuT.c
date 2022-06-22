#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

char menu(int * masqueNaissance, int * masqueSurvie,int ** tab){

    for (int i = 0; i<9;i++){
        masqueNaissance[i]= 0;
        masqueSurvie[i] = 0;
    }
    char tor;
    char config;
    int i;
    char  survie[9];
    char naissance[9];
    
    while(tor != 'i'&&tor!='d'){
        printf("Monde torique (i) ou délimité (d) ?\n");
        scanf("%c",&tor);
        getchar();
    }
    printf("Choisir entre configuration à la main (c), chargement d'un fichier (f)\n");
    
    printf("Entrez à la suite le masque survie (ex : 02536)\n");
    scanf("%s",survie);
    printf("Entrez à la suite le masque naissance (ex : 1456)\n");//problème si un nombre est présent dans les 2 masques
    scanf("%s",naissance);
    for (i = 0;i<strlen(survie);i++){
        masqueSurvie[survie[i]-'0']= 1;
    }
    for (i = 0;i<strlen(naissance);i++){
        masqueNaissance[naissance[i]-'0'] = 1;
    }

    
    return tor;
}

int main(){

    int masqueSurvie[9];
    int masqueNaissance[9];
    int ** matrice;

    char mode;

    mode = menu(masqueNaissance,masqueSurvie,matrice);
    printf("%c",mode);
    return 0;
}