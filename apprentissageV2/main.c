#include "sceneSDL.h"
#include <time.h>

#define FLOAT_TO_INT(x) ((x)>= 0?(int)((x)+0.5):(int)((x)-0.5)) 

void manger(float * barreD, float * barreM,float * barreJ,int currentRoom,float drain){
    printf("Tama mange.\n");
    if(currentRoom == 0){
        *barreD -= drain;
        *barreJ -= drain;
        *barreM = 1.0;
    }
    /*else{
        *barreD -= drain;
        *barreJ -= drain;
        *barreM += drain;
    }
    if(*barreM>=1.0){
        *barreM=1.0;
    }*/
}

void dormir(float * barreD, float * barreM,float * barreJ,int currentRoom,float drain){
    printf("Tama dort.\n");
    if(currentRoom == 2){
        *barreM -= drain;
        *barreJ -= drain;
        *barreD = 1.0;
    }
    /*else{
        *barreM -= drain;
        *barreJ -= drain;
        *barreD += drain;
    }
    if(*barreD>=1.0){
        *barreD=1.0;
    }*/
}

void jouer(float * barreD, float * barreM,float * barreJ,int currentRoom,float drain){
    printf("Tama joue.\n");
    if(currentRoom == 4){
        *barreM -= drain;
        *barreD -= drain;
        *barreJ = 1.0;
    }
    /*else{
        *barreM -= drain;
        *barreD -= drain;
        *barreJ += drain;
    }
    if(*barreJ>=1.0){
        *barreJ=1.0;
    }*/
}

void deplaceDroite(float * barreD, float * barreM,float * barreJ,int * currentRoom,float drain){
    
    *currentRoom=(*currentRoom+1+7)%7;
    *barreM -= drain;
    *barreD -= drain;
    *barreJ -= drain;
};

void deplaceGauche(float * barreD, float * barreM,float * barreJ,int * currentRoom,float drain){
    
    *currentRoom=(*currentRoom-1+7)%7;
    *barreM -= drain;
    *barreD -= drain;
    *barreJ -= drain;
};

int main(){
    //init sdl
    SDL_Window 
       *window_1 = NULL;

    SDL_DisplayMode current;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
            SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
    int ticks = 0;
    SDL_GetCurrentDisplayMode(0, &current);
    int curX,curY;
    int currMood = 0;
    int WindowW = current.w;
    int WindowH = current.h;

    window_1 = SDL_CreateWindow("Tama!Go!CHI!",0,0,WindowW,WindowH,SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );
    //fin init

    SDL_bool actionUser = SDL_TRUE;

    srand( time( NULL ) );
    
    /*float barreD = (rand()%6);
    printf("%f\n",barreD);
    barreD = barreD/10+0.2;
    
    float barreM = (rand()%6);
    printf("%f\n",barreM);
    barreM = barreM/10+0.2;
    
    float barreJ = (rand()%6);
    printf("%f\n",barreJ);
    barreJ = barreJ/10+0.2;*/
    
    
    float barreD = 0.9;
    float barreJ = 0.9;
    float barreM = 0.9;

    printf("etat des barres manger : %f dormir :%f jouer :%f\n", barreM, barreD, barreJ);

    float probaEtat[3][3] ={{0.1, 0.4, 0.5},
                            {0.4, 0.2, 0.4},
                            {0.5, 0.4, 0.1}};
    SDL_Event event;

    SDL_Rect source;
    SDL_Texture * texture = IMG_LoadTexture(renderer,"./image/hotbar.png");
    SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
    int posXicone = WindowW/2-(WindowW*0.3)/2;
    int posYicone = WindowH*0.8;
    SDL_Rect position;
    position.x = WindowW*0.15;
    position.y = WindowH*(-0.7);
    position.w = WindowW*0.7;
    position.h = WindowH*1.6;
    int etatPause = 0;
    int currentRoom = 0;
    int program_on = 1;
    int etat = 1;
    float drain = 0.1;
    int nextState=0;
    int probaCumul[3][3];
    int i,j,k,a,l,outil;
    int delai = 200;
    // variable pour faire fonctionner l'IA
    float Qmax;
    int ActionMax;
    int tempM, tempJ, tempD;
    float Qtable[11][11][11][7][5];  
    FILE *fichier = fopen ("Qtable.txt", "r" );
    if (fichier == NULL){
        printf("erreur lors de l'ouverture du fichier");
        }
    else{
        for(i = 0; i<11; i++){
            for(j = 0; j<11; j++){
                for(k = 0; k<11; k++){
                    for(l = 0; l<7; l++){
                        fscanf(fichier,"%*d %*d %*d %*d %f %f %f %f %f", &Qtable[i][j][k][l][0], &Qtable[i][j][k][l][1], &Qtable[i][j][k][l][2], &Qtable[i][j][k][l][3], &Qtable[i][j][k][l][4]);
                        }
                    } 
                } 
            } 
        }
    fclose(fichier);


    printf("qtable qui eifpozfp :%f\n ",Qtable[8][6][6][2][1]);
    /*for(i = 0; i < 11; i++){
        for (j = 0; j < 11 ; j++){
            for (k = 0; k < 11 ; k++){
                for (a = 0; a < 3 ; a++){
                    printf("%f",Qtable[i][j][k][a]); 
                }
                printf("\n");
            } 
        }*currentRoom--;
    }*/
    
    for (i = 0;i<3;i++){
        for (j = 0; j<3;j++){
            probaCumul[i][j]=probaEtat[i][j]*10;
            if(i>0){
                probaCumul[i][j]+=probaCumul[i-1][j];
            }
        }
    }

    //ECRAN DE DEBUT
    //eclosion(renderer,WindowW,WindowH);

    //BOUCLE DE JEU
    while(program_on){
            
            while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            deplaceGauche(&barreD,&barreM,&barreJ,&currentRoom,drain);
                            while(currentRoom!=0&&currentRoom!=2&&currentRoom!=4){
                                afficheTama(renderer,position,currMood,currentRoom,barreM,barreJ,barreD,WindowW,WindowH,etatPause);
                                SDL_Delay(500);
                                deplaceGauche(&barreD,&barreM,&barreJ,&currentRoom,drain);
                            }
                            break;
                        case SDLK_RIGHT:
                            deplaceDroite(&barreD,&barreM,&barreJ,&currentRoom,drain);
                            while(currentRoom!=0&&currentRoom!=2&&currentRoom!=4){
                                afficheTama(renderer,position,currMood,currentRoom,barreM,barreJ,barreD,WindowW,WindowH,etatPause);
                                SDL_Delay(500);
                                deplaceDroite(&barreD,&barreM,&barreJ,&currentRoom,drain);
                            }
                            break;
                        case SDLK_SPACE:
                            etatPause = (etatPause+1)%2;
                            break;
                    }
                    break;
                case SDL_QUIT:
                    program_on = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    curX=event.motion.x;
                    curY = event.motion.y;
                    actionUser=SDL_TRUE;
                    ticks =0;
                    //DETERMINATION BOUTON APPUYE
                    if((curY)>=posYicone && curY<=posYicone+0.2*WindowH){
                        if(curX >= posXicone && curX <= posXicone + posXicone/3){
                            manger(&barreD,&barreM,&barreJ,currentRoom,drain);
                            currMood = 1;
                        }
                        else if(curX >= (posXicone + posXicone/3) && curX <=(posXicone + posXicone/3)+posXicone/3){
                            jouer(&barreD,&barreM,&barreJ,currentRoom,drain);
                            currMood = 2;
                        }
                        else if(curX >= 0.2 && ((posXicone + posXicone/3)+posXicone/3)+posXicone/3){
                            dormir(&barreD,&barreM,&barreJ,currentRoom,drain);
                            currMood = 3;
                        }
                    }
                default:
                    break;
            }
        }

        while(etatPause){
                pause(etat,renderer,WindowW,WindowH);
                SDL_RenderPresent(renderer);
                SDL_WaitEvent(&event);
                    switch(event.type){
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                            {
                                case SDLK_SPACE:
                                etatPause = (etatPause+1)%2;
                                break;
                            }
                            break;
                        case SDL_QUIT:
                            program_on = 0;
                            etatPause = 0;
                            break;
                    }
                
            }

        //BOUCLE DE DETERMINATION DE LA PROCHAINE ACTION (MARKOV)

        /*if(ticks>1){
            ticks = 0;
            outil = rand()%10;
            nextState = 0;
            if(!actionUser){
                while(outil>probaCumul[nextState][etat]){
                    nextState++;
                }
                switch (nextState)
                {
                    case 0:
                        dormir(&barreD,&barreM,&barreJ,drain);
                        currMood = 3;
                        currentRoom = 0;
                        break;
                    case 1:
                        manger(&barreM,&barreM,&barreJ,drain);
                        currMood = 1;
                        currentRoom = 1;
                        break;
                    case 2:
                        jouer(&barreD,&barreM,&barreJ,drain);
                        currMood = 2;
                        currentRoom = 2;
                        break;
                    default:
                        break;
            }
        }
        } */
        //printf("hello");
        //FIN MARKOV

        tempM = FLOAT_TO_INT(barreM*10);
        tempD = FLOAT_TO_INT(barreD*10);
        tempJ = FLOAT_TO_INT(barreJ*10);
        printf("temp M %d temp D %d temps J %d \n ",tempM,tempD,tempJ);


        //printf("etat des barres manger : %f dormir :%f jouer :%f\n position : %d\n ", barreM, barreD, barreJ, currentRoom);
        Qmax = Qtable[tempM][tempD][tempJ][currentRoom][0];
        
        ActionMax = 0;
        for(a = 1; a < 5 ; a++){
            printf("voici le Qtable :%f\n ",Qtable[tempM][tempD][tempJ][currentRoom][a]);

            if (Qtable[tempM][tempD][tempJ][currentRoom][a] > Qmax){
                Qmax = Qtable[tempM][tempD][tempJ][currentRoom][a];
                
                ActionMax = a;
            } 
        }

        printf("\n action a effectuer numero : %d\n ",ActionMax);

        //printf("%d",ActionMax);
        switch (ActionMax)
                {
                    case 1:
                        dormir(&barreD,&barreM,&barreJ,currentRoom,drain);
                        currMood = 3;
                        break;
                    case 0:
                        manger(&barreD,&barreM,&barreJ,currentRoom,drain);
                        currMood = 1;
                        break;
                    case 2:
                        jouer(&barreD,&barreM,&barreJ,currentRoom,drain);
                        currMood = 2;
                        break;
                    case 3:
                        deplaceGauche(&barreD,&barreM,&barreJ,&currentRoom,drain);
                        break;
                    case 4:
                        deplaceDroite(&barreD,&barreM,&barreJ,&currentRoom,drain);
                        break;
                    default:
                        break;
            }


        if(barreM<=0.0){
            barreM = 0.0;
        }
        if(barreD<=0.0){
            barreD = 0.0;
        }
        if(barreJ<=0.0){
            barreJ = 0.0;
        }
        //printf("etat des barres manger : %f dormir :%f jouer :%f\n position : %d\n ", barreM, barreD, barreJ, currentRoom);

        if(barreM<=0.0||barreD<=0.0||barreJ<=0.0){
            program_on = 0;
            animeMort(renderer,WindowW,WindowH,position);
        }
        
        
        if(program_on){
            afficheTama(renderer,position,currMood,currentRoom,barreM,barreJ,barreD,WindowW,WindowH,etatPause);
        }
        ticks++;
        currMood=0;
        SDL_Delay(delai);
        actionUser = SDL_FALSE;
        
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window_1);
    SDL_Quit();
}