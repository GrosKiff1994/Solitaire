#include <stdlib.h>
#include <stdio.h>

#include "pile.h"
#include "initialiser.h"
#include "pioche.h"

//renvoie une valeur aléatoire entière comprise entre 0 et MAXN
Element tirage_aleat()
{
    return rand()%MAXN;


}
/*
//initialise un tableau sans deux fois la même valeur (52 elements)
void init_tab_sans_doublon()
{
        int i;
        for(i=0;i<MAXN;i++){tabini[i]=0;} //initialisation de tabini avec que des 0
        int cpt=0;
        Element ind;
        while(cpt<MAXT)
        {
            ind=tirage_aleat();
            if(&tabini[ind]==0)
            {
                tabini[ind]=1;
                cpt++;
            }
        }
        for(i=0;i<MAXT;i++)
        {
            Element tmp=0;
            while(tmp<MAXN)
            {
                if(tabini[tmp]==1)
                {
                    tabfinal[i]=tmp;
                    tmp=MAXN;
                    tabini[tmp]=0;
                }
                else tmp++;
            }
        }
}
*/


void initialiserJeu()
{
//initialisation d'un tableau de 52 elements aléatoire
    int i;
    for(i=0;i<MAXN;i++)
    {
        tablo[i]=i+1;
        printf("%d ",tablo[i]);
    }
    printf("\n\ntablo[18]: %d\n", tablo[18]);
        /*{
            tablo[i]=tirage_aleat();
            printf("%d ",tablo[i]);
        }*/

//tas1
    init(&tas1);
    empiler(&tas1,tablo[0]);

//tas2
    init(&tas2);
    for(i=1;i<3;i++){empiler(&tas2,tablo[i]);}

//tas3
    init(&tas3);
    for(i=3;i<6;i++){empiler(&tas3,tablo[i]);}

//tas4
    init(&tas4);
    for(i=6;i<10;i++){empiler(&tas4,tablo[i]);}

//tas5
    init(&tas5);
    for(i=10;i<15;i++){empiler(&tas5,tablo[i]);}

//tas6
    init(&tas6);
    for(i=15;i<21;i++){empiler(&tas6,tablo[i]);}

//tas7
    init(&tas7);
    for(i=21;i<28;i++){empiler(&tas7,tablo[i]);}


//pioche
    initP(&pioche);


//tri1
    init(&tri1);

//tri2
    init(&tri1);

//tri3
    init(&tri1);

//tri4
    init(&tri1);

}

void afficherJeu()
{
    printf("\npioche: ");afficherP(pioche);

    printf("\ntas1: ");afficher(tas1);
    printf("\ntas2: ");afficher(tas2);
    printf("\ntas3: ");afficher(tas3);
    printf("\ntas4: ");afficher(tas4);
    printf("\ntas5: ");afficher(tas5);
    printf("\ntas6: ");afficher(tas6);
    printf("\ntas7: ");afficher(tas7);

    printf("\ntri1: ");afficher(tri1);
    printf("\ntri2: ");afficher(tri2);
    printf("\ntri3: ");afficher(tri3);
    printf("\ntri4: ");afficher(tri4);
}
