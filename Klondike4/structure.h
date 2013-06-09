#ifndef DEF_STRUCTURE
#define DEF_STRUCTURE

#include "define.h"
#include "define_algo.h"

#include <stdbool.h>


/*----carte------*/
typedef enum {TREFLE,CARREAU,COEUR,PIQUE,SPEC}t_famille;
typedef enum {JOKER1,JOKER2,DOS,VIDE}t_spec;
typedef enum {AS,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,NEUF,DIX,VALET,DAME,ROI}t_valeur;
typedef struct {t_valeur valeur; t_famille famille; bool vu;}t_carte;

void initPaquet(t_carte tab[MAX]);
void initCarte(t_carte*, bool tabutil[NB_FAM][NB_VAL]);
t_carte carteAlea(bool vu);
void affichePaquet(t_carte tab[MAX]);
void afficherCarte(t_carte);


/*----pile------*/

typedef t_carte Element;
typedef struct{Element tab[MAX]; int sommet; int nb;} t_pile;

void init(t_pile*);
void empiler(t_pile*,Element);
Element depiler(t_pile*);
bool estVide(t_pile);
bool estPleine(t_pile);
void afficher(t_pile);

/*----pioche------*/

typedef struct{Element contenu[MAX]; int debut; int dernier; } t_pioche;

void initPioche(t_pioche* p_pioche);
void devoiler(t_pioche*);
Element enlever(t_pioche*);
void afficherP(t_pioche);
bool estVideP(t_pioche);
bool estVideP_gauche(t_pioche p);
bool estVideP_droite(t_pioche p);

/*-----Save-----*/

typedef struct{t_carte table[NB_TRI+NB_TAS+1][MAX]; int tailleTri[NB_TRI]; int tailleTas[NB_TAS]; int taillePioche[2];} t_save;

void iniSave(t_save* p_save/*, t_carte tab[MAX]*/);
void saveGame(t_save* p_save, t_pile tri[NB_TRI], t_pile tas[NB_TAS], t_pioche pioche);
void loadingGame(t_save* p_save, t_pile tri[NB_TRI], t_pile tas[NB_TAS], t_pioche* p_pioche);

#endif
