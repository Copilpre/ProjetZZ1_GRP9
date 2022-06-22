#include "dessin.h"
#include "menuT.h"
#include "recherche_voisins.h"




int main()
{
     //faire toute l'initialisation

	int masqueNaissance[9],masqueSurvie[9];
	int ** Tableau1,**Tableau2;

    
    
    char mode = menu(masqueNaissance,masqueSurvie,Tableau1);

	int w, h, i = 0, j = 0, vitesse = 0, taille ;

	char type;
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
					clic(i,j,Tableau1,type);
					
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
            for(int i;i<nbrLignes;i++)
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
			
            //il faut rentrer les bonnes variables
            affichageTableau(nbrLigne, nbrCol,tab[nbrLigne][nbrCol],renderer, window);
            SDL_RenderPresent(renderer) ;
			SDL_Delay(vitesse) ;
		}
	}

}