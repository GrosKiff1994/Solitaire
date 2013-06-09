#include <stdlib.h>
#include <stdio.h>

#include "define.h"

#include "util.h"
#include "structure.h"


//type pile --> les 7 tas + les 4 tris
void init(t_pile* tpile)
{
    tpile->nb=0;
    tpile->sommet=0;
}

void empiler(t_pile* tpile, Element el)
{
    tpile->tab[tpile->sommet]=el;
    tpile->nb++;
    tpile->sommet++;
}

Element depiler(t_pile* tpile)
{
    tpile->nb--;
    tpile->sommet--;
    Element sorti = tpile->tab[tpile->sommet];

    return sorti;
}


bool estVide(t_pile tpile)
{
    return tpile.nb==0;
}

bool estPleine(t_pile tpile)
{
    return tpile.nb==MAX;
}


void afficher(t_pile tpile)
{
    int i;
    for(i=0; i<tpile.sommet; i++)
    {
        afficherCarte(tpile.tab[i]);
    }
}

//type pioche --> pioche
void initPioche(t_pioche* p_pioche)
{
    p_pioche->debut = -1;
    p_pioche->dernier = -1;
}

//fonction devoiler permet de montrer la 1ere carte du paquet, elle passe alors a la fin
void devoiler(t_pioche* p_pioche)
{
    int i;
    // si le tas de pioche est vide : boucler
    if(estVideP_gauche(*p_pioche))
    {
        for(i=0; i<=p_pioche->dernier; i++)
        {
            p_pioche->contenu[i].vu=false;
        }
    }
    else
    {
        p_pioche->contenu[p_pioche->dernier+1] = p_pioche->contenu[p_pioche->debut];
        for(i=0; i<=p_pioche->dernier; i++)
        {
            p_pioche->contenu[i] = p_pioche->contenu[i+1];
        }
        p_pioche->contenu[p_pioche->dernier].vu = true;
    }

}

//enlève un élement de la pioche qui se trouve être le dernier élement: dernier element devoilé
Element enlever(t_pioche* p_pioche)
{
    p_pioche->dernier--;
    return p_pioche->contenu[p_pioche->dernier+1];
}


void afficherP(t_pioche p)
{
    int i;
    for(i=p.debut; i<=p.dernier; i++)
    {
        afficherCarte(p.contenu[i]);
    }
}


bool estVideP(t_pioche p)
{
    return (p.dernier == -1);
}

// retourne vrai si la pioche de gauche est vide ce qui permet alors de reinitP()
bool estVideP_gauche(t_pioche p)
{
    return (estVideP(p) || p.contenu[p.debut].vu);
}

bool estVideP_droite(t_pioche p)
{
    return (estVideP(p) || !p.contenu[p.dernier].vu);
}

//permet de "reinitialiser la pioche: toutes les cartes dévoilées redeviennent non vu
void reinitP(t_pioche p)
{
    int i;
    for(i=p.debut; i<=p.dernier; i++)
    {
        p.contenu[i].vu = false;
    }
}

//type carte --> carte + paquet
void initCarte(t_carte* carte, bool tabutil[NB_FAM][NB_VAL])
{
    carte->vu = false;
    int v,f;
    do
    {
        v = alea(AS,ROI);
        f = alea(TREFLE,PIQUE);
    }
    while(tabutil[f][v]);

    carte->famille=f;
    carte->valeur=v;
    tabutil[f][v] = true;
}

t_carte carteAlea(bool vu)
{
    t_carte maCarte;
    maCarte.valeur = alea(AS,ROI);
    maCarte.famille = alea(TREFLE,PIQUE);
    maCarte.vu = vu;

    return maCarte;
}


void afficherCarte(t_carte carte)
{
    if(!carte.vu)
    {
        printf("X ");
    }
    else
    {
        switch(carte.valeur)
        {
        case AS:
            printf("AS");
            break;
        case DEUX:
            printf("2");
            break;
        case TROIS:
            printf("3");
            break;
        case QUATRE:
            printf("4");
            break;
        case CINQ:
            printf("5");
            break;
        case SIX:
            printf("6");
            break;
        case SEPT:
            printf("7");
            break;
        case HUIT:
            printf("8");
            break;
        case NEUF:
            printf("9");
            break;
        case DIX:
            printf("10");
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
            break;
        }
        printf(" de ");
        switch(carte.famille)
        {
        case TREFLE:
            printf("TREFLE ");
            break;
        case CARREAU:
            printf("CARREAU ");
            break;
        case COEUR:
            printf("COEUR ");
            break;
        case PIQUE:
            printf("PIQUE ");
            break;
        default:
            break;
        }
    }
}


void initPaquet(t_carte tab[MAX])
{
    bool tabutil[NB_FAM][NB_VAL]= {{false}};
    int i;
    for(i=0; i<MAX; i++)
    {
        initCarte(&tab[i],tabutil);
    }
}


void affichePaquet(t_carte tab[MAX])
{
    int i;
    printf("\nPaquet :\n");
    for(i=0; i<MAX; i++)
    {
        t_carte tmp;
        tmp.vu = true;
        tmp.famille = tab[i].famille;
        tmp.valeur = tab[i].valeur;
        afficherCarte(tmp);
        printf("/ ");
    }
    printf("\n");
}


//Initialisation du tableau de sauvegarde

void iniSave(t_save* p_save/*, t_carte tab[MAX]*/)
{
    int i;

    for (i=0; i<NB_TRI; i++)
    {
        p_save->tailleTri[i]=0;
    }
    for (i=0; i<NB_TAS; i++)
    {
        p_save->tailleTas[i]=0;
    }
    for (i=0; i<2; i++)
    {
        p_save->taillePioche[i]=0;
    }
}


//Les données sont réparties sur les lignes
// 0-3 : Les piles concernant les tris
// 4-10 : Les piles concernant les tas
// 11 : La pile de la pioche
void saveGame(t_save* p_save, t_pile tri[NB_TRI], t_pile tas[NB_TAS], t_pioche pioche)
{
    int i,j;

    for (i=0; i<NB_TRI; i++)
    {
        for (j=0; j<tri[i].sommet; j++)
        {
            p_save->table[i][j]=tri[i].tab[j];
        }
        p_save->tailleTri[i]=tri[i].sommet;
    }

    for (i=0; i<NB_TAS; i++)
    {
        for (j=0; j<tas[i].sommet; j++)
        {
            p_save->table[NB_TRI+i][j]=tas[i].tab[j];
        }
        p_save->tailleTas[i]=tas[i].sommet;
    }


    for (i=0; i<(MAX - 28); i++)
    {
        p_save->table[NB_TRI+NB_TAS][i]=pioche.contenu[i];
    }
    p_save->taillePioche[0]=pioche.debut;
    p_save->taillePioche[1]=pioche.dernier;

}



//Chargement d'un tableau de sauvegarde
void loadingGame(t_save* p_save, t_pile tri[NB_TRI], t_pile tas[NB_TAS], t_pioche* p_pioche)
{

    int i,j;

    for(i=0;i<NB_TRI;i++)
    {
        init(&tri[i]);
        for(j=0;j<p_save->tailleTri[i];j++)
        {
            empiler(&tri[i],(p_save->table[i][j]));
        }
    }

    for(i=0;i<NB_TAS;i++)
    {
        init(&tas[i]);
        for(j=0;j<p_save->tailleTas[i];j++)
        {
            empiler(&tas[i],p_save->table[NB_TRI+i][j]);
        }
        tas[i].tab[tas[i].sommet-1].vu=true;
    }


    initPioche(p_pioche);
    for(i=0; i<(MAX - 28); i++)
    {
        p_pioche->contenu[i]=(p_save->table[NB_TRI+NB_TAS][i]);
    }
    p_pioche->debut=p_save->taillePioche[0];
    p_pioche->dernier=p_save->taillePioche[1];
}
