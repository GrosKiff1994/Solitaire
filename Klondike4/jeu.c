#include <stdlib.h>
#include <stdio.h>

#include "jeu.h"

void initialiserJeu(t_carte tab[MAX], t_pile tri[NB_TRI], t_pile tas[NB_TAS], t_pioche* p_pioche)
{
    //initialisation des 7 tas
    int j=0;
    int t = 0;
    int i;

    for(i=0; i<NB_TAS; i++)
    {
        init(&tas[i]);
        for(j=0; j<=i; j++)
        {

            empiler(&tas[i],tab[t]);
            t++;
        }
        tas[i].tab[tas[i].sommet-1].vu=true;
    }

    //initialisation des 4 tris
    for(i=0; i<NB_TRI; i++)
    {
        init(&tri[i]);
    }

    //initialisation de la pioche
    initPioche(p_pioche);
    for(i=0; i<(MAX-28); i++)
    {
        p_pioche->contenu[i]=tab[i+28];
    }
    p_pioche->debut=0;
    p_pioche->dernier=(MAX-28)-1;
}

void afficherJeu(t_pile tri[NB_TRI], t_pile tas[NB_TAS],t_pioche pioche)
{
    int i;
    //affichage de la pioche
    printf("\npioche: ");
    afficherP(pioche);

    //affichage des 7 tas
    for(i=0; i<7; i++)
    {
        printf("\ntas%d: ",i);
        afficher(tas[i]);
    }

    //affichage des 4 tris
    for(i=0; i<4; i++)
    {
        printf("\ntri%d: ",i);
        afficher(tri[i]);
    }

    printf("\n");
}

//verifier_victoire renvoie vrai si la valeur du sommet des 4 tris est ROI
bool verifier_victoire(t_pile tri[NB_TRI])
{
    bool victoire = true;
    int i = 0;
    while(i<NB_TRI && victoire == true)
    {
        if(tri[i].tab[tri[i].sommet-1].valeur != ROI)
        {
            victoire = false;
        }
        i++;
    }
    return victoire;
}

// renvoie vrai si les deux cartes n'ont pas la même couleur (noir ou rouge)
bool estOppose(t_carte c1, t_carte c2)
{
    if(c1.famille == COEUR || c1.famille == CARREAU)
    {
        return c2.famille == TREFLE || c2.famille == PIQUE;
    }
    else return c2.famille == CARREAU || c2.famille == COEUR;
}

void afficheEndroit(t_endroit e)
{
    printf("endroit : ");
    switch(e.zone)
    {
    case PIOCHE:
        printf("pioche, pile %d", e.num_pile);
        break;
    case TRI:
        printf("tri, pile %d", e.num_pile);
        break;
    case TAS:
        printf("tas, pile %d, carte %d", e.num_pile, e.num_carte);
        break;
    case ZVIDE:
        printf("vide");
    }
}

/* affiche un déplacement en console */
void afficheDeplacement(t_deplacement d)
{
    printf("\nDeplacement : ");
    afficheEndroit(d.depart);
    printf(" vers ");
    afficheEndroit(d.arrivee);
    printf(" de : ");
    afficher(d.cartAdep);
}

/* initialise un déplacement */
void initDeplacement(t_deplacement* dep)
{
    dep->depart.zone = ZVIDE;
    dep->depart.num_pile = -1;
    dep->depart.num_carte = -1;
    dep->arrivee.zone = ZVIDE;
    dep->arrivee.num_pile = -1;
    dep->arrivee.num_carte = -1;
    init(&dep->cartAdep);
}

/*
TRI
    -> vide -> AS
    -> sinon -> même famille && valeur-1
TAS
    -> vide -> ROI
    -> sinon -> oppose && valeur+1
*/
bool deplacement_possible(t_deplacement dep, /*t_pioche pioche,*/t_pile tri[NB_TRI], t_pile tas[NB_TAS])
{
    t_carte hautadep = dep.cartAdep.tab[dep.cartAdep.sommet-1];
    switch(dep.arrivee.zone)
    {
    case TRI:
        if(estVide(tri[dep.arrivee.num_pile]))
        {
            return dep.cartAdep.tab[0].valeur == AS;
        }
        else
        {
            return (dep.cartAdep.nb == 1) && (dep.cartAdep.tab[0].famille == tri[dep.arrivee.num_pile].tab[0].famille) && (dep.cartAdep.tab[0].valeur == tri[dep.arrivee.num_pile].tab[tri[dep.arrivee.num_pile].sommet-1].valeur+1);
        }
        break;
    case TAS:
        if(estVide(tas[dep.arrivee.num_pile]))
        {
            return hautadep.valeur == ROI;
        }
        else
        {
            t_carte desti = tas[dep.arrivee.num_pile].tab[tas[dep.arrivee.num_pile].sommet-1];
            return estOppose(hautadep, desti) && (hautadep.valeur == desti.valeur-1);
        }
            break;
    default:
        return false;
        break;
    }
}

//de Depart vers cartAdep (tout ce qui est en deplacement)
void deplacement1(t_deplacement* dep, t_pioche* pioche, t_pile tri[NB_TRI], t_pile tas[NB_TAS])
{
    switch(dep->depart.zone)
    {
    case PIOCHE:
        empiler(&dep->cartAdep, enlever(pioche));
        break;
    case TAS:
        do
        {
            empiler(&dep->cartAdep, depiler(&tas[dep->depart.num_pile]));
        }
        while(tas[dep->depart.num_pile].nb > dep->depart.num_carte);
        break;
    case TRI:
        empiler(&dep->cartAdep, depiler(&tri[dep->depart.num_pile]));
        break;
    default:
        break;
    }

}
//de cartAdep vers Arrivee
void deplacement2(t_deplacement* dep, t_pioche* pioche, t_pile tri[NB_TRI], t_pile tas[NB_TAS])
{
    if(deplacement_possible(*dep, /* *pioche,*/ tri, tas))
    {
        switch(dep->arrivee.zone)
        {
        case TRI:
            empiler(&tri[dep->arrivee.num_pile], depiler(&dep->cartAdep));
            break;
        case TAS:
            do
            {
                empiler(&tas[dep->arrivee.num_pile], depiler(&dep->cartAdep));
            }
            while(!estVide(dep->cartAdep));
            break;
        default:
            break;
        }

        if(dep->depart.zone == TAS && !estVide(tas[dep->depart.num_pile]))
        {
                        tas[dep->depart.num_pile].tab[tas[dep->depart.num_pile].sommet-1].vu = true;
        }
    }
    else
    {
        switch(dep->depart.zone)
        {
        case PIOCHE:
            pioche->dernier++;
            pioche->contenu[pioche->dernier] = depiler(&dep->cartAdep);
            break;
        case TAS:
            do
            {
                empiler(&tas[dep->depart.num_pile], depiler(&dep->cartAdep));
            }
            while(!estVide(dep->cartAdep));
            break;
        case TRI:
            empiler(&tri[dep->depart.num_pile], depiler(&dep->cartAdep));
            break;
        default:
            break;
        }
    }
}


