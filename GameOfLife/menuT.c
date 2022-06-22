#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

int menu(SDL_bool * masqueNaissance, SDL_bool * masqueSurvie){

    for (int i = 0; i<9;i++){
        masqueNaissance[i]=SDL_FALSE;
        masqueSurvie[i]=SDL_FALSE;
    }
    char tor;
    int i;
    char  survie[9];
    char naissance[9];
    printf("Monde torique (i) ou délimité (d) ?\n");
    scanf("%c",&tor);
    printf("Entrez à la suite le masque survie (ex : 02536)\n");
    scanf("%s",survie);
    printf("Entrez à la suite le masque naissance (ex : 1456)\n");//problème si un nombre est présent dans les 2 masques
    scanf("%s",naissance);
    for (i = 0;i<strlen(survie);i++){
        masqueSurvie[survie[i]-'0']=SDL_TRUE;
    }
    for (i = 0;i<strlen(naissance);i++){
        masqueNaissance[naissance[i]-'0']=SDL_TRUE;
    }
    return 0;
}

int main(){

    SDL_bool masqueSurvie[9];
    SDL_bool masqueNaissance[9];

    menu(masqueNaissance,masqueSurvie);
    

    
    return 0;
}