#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void manger(float * barreD, float * barreM,float * barreJ,float drain){
    printf("Tama mange.\n");
    *barreD-=drain;
    *barreJ-=drain;
    *barreM+=2*drain;
}

void dormir(float * barreD, float * barreM,float * barreJ,float drain){
    printf("Tama dort.\n");
    *barreM-=drain;
    *barreJ-=drain;
    *barreD+=2*drain;
}

void jouer(float * barreD, float * barreM,float * barreJ,float drain){
    printf("Tama joue.\n");
    *barreM-=drain;
    *barreD-=drain;
    *barreJ+=2*drain;
}

int main(){
    float barreD = 0.5,barreM=0.5,barreJ=0.5;
    srand( time( NULL ) );

    float probaEtat[3][3] ={{0.1, 0.4, 0.5},
                            {0.4, 0.2, 0.4},
                            {0.5, 0.4, 0.1}};

    int program_on = 1;
    int etat = 1;
    float drain = 0.1;
    int nextState=0;
    int probaCumul[3][3];
    int i,j,outil;

    for (i = 0;i<3;i++){
        for (j = 0; j<3;j++){
            probaCumul[i][j]=probaEtat[i][j]*10;
            if(i>0){
                probaCumul[i][j]+=probaCumul[i-1][j];
            }
        }
    }

    while(program_on){
        outil = rand()%10;
        nextState = 0;
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

        if(barreM>=1||barreD>=1||barreJ>=1||barreM<=0||barreD<=0||barreJ<=0){
            program_on = 0;
        }
        printf("Sommeil : %f, faim : %f, joie : %f\n",barreD,barreM,barreJ);
    }
    
    printf("%f",barreM);
    
}
