/**
fichier à ne plus utiliser, a servi pour les débuts du projet
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "cartepile.h"


void initTab(bool monTab[NBCOUL][NBVAL]){
    int i=0,j=0;
    for(i=0;i<NBCOUL;i++){
        for(j=0;j<NBVAL;j++){
            monTab[i][j] = false;
        }
    }
}

int alea(int valMin,int valMax)
{
    return rand()%(valMax - valMin+1)+valMin;
}

/*
    Tirer et créer une carte aléatoirement
*/
struct T_carte carteAlea(bool tabUti[NBCOUL][NBVAL], bool vu)
{
    struct T_carte maCarte;
    do{
        maCarte.valeur = alea(AS,ROI);
        maCarte.famille = alea(TREFLE,PIQUE);
    }while(tabUti[maCarte.famille][maCarte.valeur]);
    tabUti[maCarte.famille][maCarte.valeur] = true;

    maCarte.vu = vu;
    return maCarte;
};

struct T_carte carteAlea2(){
    struct T_carte maCarte;
    maCarte.valeur = alea(AS,ROI);
    maCarte.famille = alea(TREFLE,PIQUE);
    maCarte.vu = 1;
    return maCarte;
};


/*
    Initialiser une pile
*/
void initPile(struct T_pile* maPile)
{
    maPile->sommet = 0;
}

/*
    Tester si une pile est vide
*/
int vide(struct T_pile maPile)
{
    return maPile.sommet == 0;
}

/*
    Tester si une pile est pleine
*/
int pleine(struct T_pile maPile)
{
    return maPile.sommet == TAILLEPILE+1;
}

/*
    empiler une carte passée en paramètre à une pile donnée
*/
void empiler(struct T_pile* maPile, struct T_carte maCarte)
{
    if(pleine(*maPile))
    {
        printf("pile pleine !");
    }
    else
    {
        maPile->vecteur[maPile->sommet] = maCarte;
        maPile->sommet++;
    }
}

/*
    dépiler une carte d'une pile et la retourner, si la pile est vide, retourne la carte vide {-1;-1;0}
*/
struct T_carte depiler(struct T_pile* maPile)
{
    struct T_carte maCarte;
    maPile->sommet--;
    maCarte = maPile->vecteur[maPile->sommet];
    return maCarte;
}


/*
    Afficher une carte passée en paramètres : valeur, famille, vu
*/
void afficherCarte(struct T_carte maCarte)
{
    // valeur
    printf("valeur : ");
    switch(maCarte.valeur)
    {
    case AS:
        printf("AS");
        break;
    case VALET:
        printf("VALET");
        break;
    case DAME:
        printf("DAME");
        break;
    case ROI:
        printf("ROI");
        break;
    default:
        printf("%d",maCarte.valeur+1);
        break;
    }

    printf("\t");

    // nom de la famille
    printf("famille : ");
    switch(maCarte.famille)
    {
    case TREFLE:
        printf("TREFLE");
        break;
    case CARREAU:
        printf("CARREAU");
        break;
    case COEUR:
        printf("COEUR");
        break;
    case PIQUE:
        printf("PIQUE");
        break;
    default:
        break;
    }
    printf("\t");

    // état de visibilité
    printf("visible : ");
    if(maCarte.vu == 1)
    {
        printf("VU");
    }
    else
    {
        printf("PASVU");
    }
    printf("\n");
}

void afficherPile(struct T_pile maPile)
{
    int i;
    for(i=0;i<maPile.sommet;i++)
    {
        printf("carte num %d\t",i);
        afficherCarte(maPile.vecteur[i]);
    }
}
