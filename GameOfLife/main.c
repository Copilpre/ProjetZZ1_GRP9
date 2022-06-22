#include "menuT.h"
#include "affichageSDL.h"

#include <SDL2/SDL.h>






#define TAILLE 20

void affichageTableau(int ligne, int col,int ** tab,SDL_Renderer * renderer,SDL_Window * window){
    int i,j;
	
    SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
    SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
    
    SDL_Rect window_dimensions;

    SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);
	int dimCase = window_dimensions.h/ligne;
    SDL_Rect position = {0,0,window_dimensions.h/col,window_dimensions.w/ligne};

    for (i=0;i<ligne;i++){
        position.y = i*dimCase;
        for (j=0;j<col;j++){
            position.x=j*dimCase;
            if(tab[j][i]==1){
				
				printf("(%d %d)",position.x,position.y);
				SDL_RenderFillRect(renderer,&position);
        	}
        }
    }

	SDL_RenderPresent(renderer);
}

int main()
{
     //faire toute l'initialisation

	int masqueNaissance[9],masqueSurvie[9];
	int ** Tableau1,**Tableau2;

    int nbrLigne=TAILLE;
	int nbrCol=TAILLE;
    //char mode = menu(masqueNaissance,masqueSurvie,Tableau1);

	Tableau2=initTab(TAILLE);

	Tableau2[0][1]=1;
	
	int w, h, i = 0, j = 0, vitesse = 100;

	char type;
    SDL_Event event;
    SDL_bool keepLoop = SDL_FALSE;

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
	SDL_Rect rect ; 
	window_1 = SDL_CreateWindow("Menu",window.w/2,window.y,window.w,window.w,SDL_WINDOW_RESIZABLE);

	SDL_Renderer * renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );

	//FIN INIT

	affichageTableau(20,20,Tableau2,renderer,window_1);
	SDL_Delay(2000);

    while (keepLoop) {

		while (SDL_PollEvent(&event)) 
		{
			printf("coicou");
			switch (event.type) 
			{
				case SDL_BUTTON_LEFT :
					vitesse = (vitesse < 100) ? vitesse+10 : 100 ;
					break ;
				case SDL_BUTTON_RIGHT :
					vitesse =  (vitesse > 10) ? vitesse-10 : 10;
					break ;
				case SDL_MOUSEBUTTONDOWN :

					if(event.button.button == SDL_BUTTON_LEFT){
						type = 1;
					}
					else{
						if(event.button.button == SDL_BUTTON_RIGHT){
							type = 0;
						}
					}

					SDL_GetMouseState(&i, &j) ;
					i = (int)(i / rect.w) ;
					j = (int)(j / rect.h) ;
					clic(type,i,j,TAILLE,Tableau2);
					
					break ;
				case SDL_WINDOWEVENT_CLOSE :
					keepLoop = SDL_FALSE ;
					break ;
				case SDL_QUIT :
					keepLoop = SDL_FALSE ;
					break ;
				case SDL_WINDOWEVENT_LEAVE :
					keepLoop = SDL_FALSE ;
					break ;
				default :
					break ;
			}
            int compteurDifferences=0;
            int nbrColonnes =20;
            int nbrLignes=20;
            /*for(int i;i<nbrLignes;i++)
                {
                    for(int j;j < nbrColonnes; j++)
                        {
                        if (mode=='i') //mettre la bonne variable
                            {
                            if (Tableau1[i][j]==1){
								Tableau2[i][j]= masqueSurvie[nb_voisins_torrique(Tableau1 , i, j, nbrLignes, nbrColonnes)];}
                            else
                                {Tableau2[i][j]= masqueNaissance[nb_voisins_torrique(Tableau1 , i, j, nbrLignes, nbrColonnes)];}
                            } 
                        else
                        {
                            if (Tableau1[i][j]==1)        
                                {Tableau2[i][j]= masqueSurvie[nb_voisins_delimite(Tableau1 , i, j, nbrLignes, nbrColonnes)];}
                            else
                                {Tableau2[i][j]= masqueNaissance[nb_voisins_delimite(Tableau1 , i, j, nbrLignes, nbrColonnes)];}
                            } 
                        if (Tableau1[i][j]!=Tableau2[i][j])
                            compteurDifferences += 1;
                        } 
                } 

            if (compteurDifferences == 0)
                {printf("Etat stable atteind");} 
			*/
            //il faut rentrer les bonnes variables
            affichageTableau(nbrLigne, nbrCol,Tableau2,renderer, window_1);
			SDL_Delay(vitesse) ;
		}
	}

}