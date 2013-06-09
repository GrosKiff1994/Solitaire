#include <stdbool.h>
#include "define_algo.h"


//énumérations des différentes valeurs possibles des cartes selon famille et valeur
typedef enum t_valeur {AS,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,NEUF,DIX,VALET,DAME,ROI}t_valeur;
typedef enum t_famille {TREFLE,CARREAU,COEUR,PIQUE,SPEC}t_famille;
typedef enum t_spec {JOKER1, JOKER2, DOS, VIDE}t_spec;



//défini une carte
typedef struct T_carte
{
    enum t_valeur valeur;
    enum t_famille famille;
    int vu;
}T_carte;

//défini une pile
typedef struct T_pile
{
    struct T_carte vecteur[TAILLEPILE];
    int sommet;             // première case de libre au dessus de la pile
    int taillePile;
}T_pile;



// différents prototypes de cartepile.c
void initTab(bool monTab[NBCOUL][NBVAL]);
void initPile(struct T_pile* maPile);
int vide(struct T_pile maPile);
int pleine(struct T_pile maPile);
struct T_carte carteAlea(bool tabUti[NBCOUL][NBVAL], bool vu);
struct T_carte carteAlea2();

void empiler(struct T_pile* maPile, struct T_carte maCarte);
struct T_carte depiler(struct T_pile* maPile);

void afficherCarte(struct T_carte maCarte);
void afficherPile(struct T_pile maPile);
