#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#define taille 10

void affichageTableau(int ligne, int col,int **tab,SDL_Renderer * renderer,int tailleCase){
    int i,j;
    SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0,0,0, 0);

    SDL_Rect position = {0,0,tailleCase,tailleCase};
    for (i=0;i<ligne;i++){
        position.y = i*tailleCase;
        for (j=0;j<col;j++){
            position.x=j*tailleCase;
            if(tab[i][j]==1){
            SDL_RenderFillRect(renderer,&position);
        }
        }
    }
}

int compteVoisin(int ** tab, int n,int m, int i, int j)
{
  int nb_voisins = 0; //On initialise le nombre de voisins de la cellule à zéro
 
 
    if (i - 1 >= 0 && j - 1 >= 0 && tab[i-1][j-1] == 1) //voisin haut gauche
        nb_voisins += 1;
 
    if (i - 1 >= 0 && tab[i-1][j] == 1) // voisin haut
        nb_voisins += 1;
 
    if (i - 1 >= 0 && j + 1 < n && tab[i-1][j+1] == 1) //voisin haut droite
        nb_voisins += 1;
 
    if (j - 1 >= 0 && tab[i][j-1] == 1) //voisin gauche
        nb_voisins += 1;
 
    if (j + 1 < n && tab[i][j+1] == 1) //voisin droite
        nb_voisins += 1;
 
    if (i + 1 < n && j - 1 >= 0 && tab[i+1][j-1] == 1) //voisin bas gauche
        nb_voisins += 1;

    if (i + 1 < n && tab[i+1][j] == 1) //voisin bas
        nb_voisins += 1;
 
    if (i + 1 < n && j + 1 < n && tab[i+1][j+1]) //voisin bas droite
        nb_voisins += 1;
    
    return nb_voisins;
}

int compteVoisinTorrique(int ** tab, int n,int m, int i, int j)
{
  int nb_voisins_torrique = 0; //On initialise le nombre de voisins de la cellule à zéro
    
    if (tab[(i-1+n)%n][(j-1+m)%m] == 1) //voisin haut gauche
        nb_voisins_torrique += 1;

    if (tab[(i-1+n)%n][j%m] == 1) // voisin haut
        nb_voisins_torrique += 1;
 
    if (tab[(i-1+n)%n][(j+1+m)%m] == 1) //voisin haut droite
        nb_voisins_torrique += 1;
 
    if (tab[i][(j-1+m)%m] == 1) //voisin gauche
        nb_voisins_torrique += 1;
 
    if (tab[i][(j+1+m)%m] == 1) //voisin droite
        nb_voisins_torrique += 1;
 
    if (tab[(i+1)%n][(j-1+m)%m] == 1) //voisin bas gauche
        nb_voisins_torrique += 1;

    if (tab[(i+1+n)%n][j%m] == 1) //voisin bas
        nb_voisins_torrique += 1;
 
    if (tab[(i+1)%n][(j+1+m)%m]==1) //voisin bas droite
        nb_voisins_torrique += 1;

    return nb_voisins_torrique;
}

void initFichier(int ** tab,char * nomF){
    

}


int main(){

    /*				INIT 
					SDL				*/

	SDL_Window 
       *window_1 = NULL;

    SDL_DisplayMode current;
	

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
            SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
	SDL_GetCurrentDisplayMode(0, &current);
	SDL_Rect window = {0,0,current.h, current.h};
	
    
	//FIN INIT

    int ligne = taille,colonne =taille;
    char mode = 'f';
    char type = 'c';
    int masqueSurvie[9] = {0,0,1,1,0,0,0,0,0};
    int masqueNaissance[9] = {0,0,0,1,0,0,0,0,0};

    char * nomF = "";
    int i,j,mouseX,mouseY,vitesse = 250,nbVoisins;
    int ** plateau;

    int ** plateau2 = calloc(ligne,sizeof(int *));
        for (i = 0; i < ligne; i++){
            plateau2[i] = calloc(colonne,sizeof(int));
        }
    if(type=='c'){
        plateau = calloc(ligne,sizeof(int *));
        for (i = 0; i < ligne; i++){
            plateau[i] = calloc(colonne,sizeof(int));
        }
    }
    else{
        nomF="matrice.txt";
        FILE * fichier = fopen(nomF,"r");
        fscanf(fichier,"%d %d",&ligne,&colonne);
        plateau = calloc(ligne,sizeof(int *));
        for (i = 0; i < ligne; i++){
            plateau[i] = calloc(colonne,sizeof(int));
        }


    }


    int tailleCase = (current.h-window.y)/ligne;

    window_1 = SDL_CreateWindow("Menu",window.w/2,window.y,colonne*tailleCase,ligne*tailleCase,SDL_WINDOW_RESIZABLE);

	SDL_Renderer * renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );

    SDL_Event event;
    SDL_bool keepLoop = SDL_FALSE, program_on = SDL_TRUE;

    while(program_on){
        affichageTableau(ligne,colonne,plateau2,renderer,tailleCase);
        SDL_RenderPresent(renderer);
        if(SDL_WaitEvent(&event)){
            switch (event.type) 
                {
                    case SDL_QUIT :
                        keepLoop = SDL_FALSE ;
                        program_on = SDL_FALSE;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        SDL_GetMouseState(&mouseX,&mouseY);
                        i = mouseY/tailleCase;
                        j = mouseX/tailleCase;
                        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) ) {
                            plateau[i][j] = 1;
                        }
                        else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT) ){
                            plateau[i][j] = 0;
                        }
                        break;
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym==SDLK_SPACE){
                            keepLoop=SDL_TRUE;
                        }
                }
        }
        while (keepLoop) {
            while (SDL_PollEvent(&event)) 
            {
                switch (event.type) 
                {
                    case SDL_QUIT :
                        keepLoop = SDL_FALSE ;
                        program_on = SDL_FALSE;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:
                                    vitesse = (vitesse > 1000) ? 1000 :vitesse+20;
                                    break;
                                case SDLK_RIGHT:
                                    vitesse = (vitesse < 100) ?  100 : vitesse-20;
                                    break;
                                case SDLK_SPACE:
                                    keepLoop=SDL_FALSE;
                                    break;
                                    
                            }
                            break;


                }
            }
            for(i = 0;i<ligne;i++){
                for(j=0;j<colonne;j++){
                    switch(mode){
                        case 'f':
                            nbVoisins = compteVoisin(plateau,ligne,colonne,i,j);
                            break;
                        case 'i':
                            nbVoisins = compteVoisinTorrique(plateau,ligne,colonne,i,j);
                            break;
                    }
                    switch (plateau2[i][j])
                    {
                        case 1:
                            plateau2[i][j]=masqueSurvie[nbVoisins];
                            break;
                        case 0:
                            printf("%d (%d,%d)\n",nbVoisins,i,j);
                            plateau2[i][j]=masqueNaissance[nbVoisins];
                            break;
                    
                    default:
                        break;
                    }
                }
            }

            affichageTableau(ligne,colonne,plateau2,renderer,tailleCase);
            SDL_RenderPresent(renderer);
            SDL_Delay(vitesse);
            plateau = plateau2;
        }
    }
    
    for (i = 0;i<ligne;i++){
        free(plateau[i]);
    }
    free(plateau);

    SDL_DestroyWindow(window_1);
    return 0;
}