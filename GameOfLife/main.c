#include "dessin.h"
#include "menuT.h"
#include "recherche_voisins.h"




int main()
{
    //faire toute l'initialisation

    int masqueSurvie[9]={0,0,1,1,0,0,0,0,0};
    int masqueNaissance[9]={0,0,1,1,0,0,0,0,0};


    
    
    menu(SDL_bool * masqueNaissance, SDL_bool * masqueSurvie);


    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    
    while (!quit) {

		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
				case SDL_BUTTON_LEFT :
					vitesse = (vitesse < 100) ? vitesse+10 : 100 ;
					break ;
				case SDL_BUTTON_RIGHT :
					vitesse =  (vitesse > 10) ? vitesse-10 : 10;
					break ;
				case SDL_MOUSEBUTTONDOWN :
					SDL_GetMouseState(&i, &j) ;
					i = (int)(i / rect.w) ;
					j = (int)(j / rect.h) ;
					rect.x = i * rect.w ;
					rect.y = j * rect.h ;
					// Ici on doit prendre en compte certains 
					// changement au niveau de l'ecran et de la grille 
					newColor = SDL_TRUE ;
					SDL_ChangeColor(renderer, rect, newColor) ;
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
            for(int i;i<nbrLignes;i++)
                {
                    for(int j;j < nbrColonnes; j++)
                        {
                        if (mode==torrique) //mettre la bonne variable
                            {
                            if (Tableau1[i][j]==1)        
                                {Tableau2[i][j]= masqueSurvie[nb_voisins_torrique(**tab , i, j, nrbLignes, int nbrColonnes)];}
                            else
                                {Tableau2[i][j]= masqueNaissance[nb_voisins_torrique(**tab , i, j, nrbLignes, int nbrColonnes)];}
                            } 
                        else
                        {
                            if (Tableau1[i][j]==1)        
                                {Tableau2[i][j]= masqueSurvie[nb_voisins_delimite(**tab , i, j, nrbLignes, int nbrColonnes)];}
                            else
                                {Tableau2[i][j]= masqueNaissance[nb_voisins_delimite(**tab , i, j, nrbLignes, int nbrColonnes)];}
                            } 
                        if (Tableau1[i][j]!=Tableau2[i][j])
                            compteurDifferences += 1;
                        } 
                } 

            if (compteurDifferences == 0)
                {printf("Etat stable atteind");} 
			SDL_RenderPresent(renderer) ;
			SDL_Delay(vitesse) ;
		}
	}

}






