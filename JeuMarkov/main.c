#include "sceneSDL.h"
#include <time.h>

void manger(float * barreD, float * barreM,float * barreJ,float drain){
    printf("Tama mange.\n");
    *barreD-=drain;
    *barreJ-=drain;
    *barreM+=2*drain;
    if(*barreM>=1.0){
        *barreM=1.0;
    }
}

void dormir(float * barreD, float * barreM,float * barreJ,float drain){
    printf("Tama dort.\n");
    *barreM-=drain;
    *barreJ-=drain;
    *barreD+=2*drain;
    if(*barreD>=1.0){
        *barreD=1.0;
    }
}

void jouer(float * barreD, float * barreM,float * barreJ,float drain){
    printf("Tama joue.\n");
    *barreM-=drain;
    *barreD-=drain;
    *barreJ+=2*drain;
    if(*barreJ>=1.0){
        *barreJ=1.0;
    }
}

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

    SDL_GetCurrentDisplayMode(0, &current);
    int curX,curY;
    int currMood = 0;
    int WindowW = current.h/2;
    int WindowH = 1.3*current.h/2;

    window_1 = SDL_CreateWindow("Tama!Go!CHI!",current.w/2-current.h/4,0,WindowW,WindowH,SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );
    //fin init

    SDL_bool actionUser = SDL_TRUE;
    float barreD = 0.5,barreM=0.5,barreJ=0.5;
    srand( time( NULL ) );

    float probaEtat[3][3] ={{0.1, 0.4, 0.5},
                            {0.4, 0.2, 0.4},
                            {0.5, 0.4, 0.1}};
    SDL_Event event;

    int currentRoom = 0;
    int program_on = 1;
    int etat = 1;
    float drain = 0.05;
    int nextState=0;
    int probaCumul[3][3];
    int i,j,outil;
    int delai = 1000;
    for (i = 0;i<3;i++){
        for (j = 0; j<3;j++){
            probaCumul[i][j]=probaEtat[i][j]*10;
            if(i>0){
                probaCumul[i][j]+=probaCumul[i-1][j];
            }
        }
    }
    eclosion(renderer,WindowW,WindowH);
    while(program_on){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            currentRoom = (currentRoom-1+3)%3;
                            break;
                        case SDLK_RIGHT:
                            currentRoom = (currentRoom+1+3)%3;
                    }
                    break;
                case SDL_QUIT:
                    program_on = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    curX=event.motion.x;
                    curY = event.motion.y;
                    actionUser=SDL_TRUE;
                    delai = 1000;

                    if((curY)>=WindowH*0.75 && curY<=WindowH*0.95+50){
                        if(curX >= 50 && curX <=WindowH*0.2+50){
                            manger(&barreD,&barreM,&barreJ,drain);
                            //printf("Vous avez fait manger Tama.\n");
                        }
                        else if(curX >= 200 && curX <=WindowH*0.2+200){
                            jouer(&barreD,&barreM,&barreJ,drain);
                            //printf("Vous avez fait jouer Tama.\n");
                        }
                        else if(curX >= 350 && curX <=WindowH*0.2+350){
                            dormir(&barreD,&barreM,&barreJ,drain);
                            //printf("Vous avez fait dormir Tama.\n");
                        }
                    }

                default:
                    break;
            }
        }
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
                    break;
                case 1:
                    manger(&barreM,&barreM,&barreJ,drain);
                    break;
                case 2:
                    jouer(&barreD,&barreM,&barreJ,drain);
                    break;
                default:
                    break;
            }
            delai = 2000;
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
        initSDL(currentRoom,currMood,barreM,barreJ,barreD,renderer,WindowW,WindowH);
        if(barreM>=1.0||barreD>=1.0||barreJ>=1.0||barreM<=0.0||barreD<=0.0||barreJ<=0.0){
            program_on = 0;
        }
        SDL_Delay(delai);
        actionUser = SDL_FALSE;
        //printf("Sommeil : %f, faim : %f, joie : %f | Programme on :%d\n",barreD,barreM,barreJ,program_on);
    }
}