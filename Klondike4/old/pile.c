#include "pile.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


void init(t_pile* tpile)
{
    tpile->nb=0;
    tpile->sommet=0;
    tpile->max=MAX;
}

void empiler(t_pile* tpile, Element el)
{
        {
        tpile->tab[tpile->sommet]=el;
        tpile->nb++;
        tpile->sommet++;
        }
}

Element depiler(t_pile* tpile)
{
    Element sorti = tpile->tab[tpile->sommet];
    tpile->nb--;
    tpile->sommet--;
    return sorti;
}

bool estVide(t_pile tpile)
{
    return tpile.nb==0;
}

bool estPleine(t_pile tpile)
{
    return tpile.sommet==tpile.max-1;
}

void afficher(t_pile tpile)
{
    int i;
    for(i=0;i<tpile.sommet;i++){printf("%d ",tpile.tab[i]);}
}
