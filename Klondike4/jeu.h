#ifndef DEF_JEU
#define DEF_JEU

#include "define.h"
#include "structure.h"

typedef enum{ZVIDE, PIOCHE, TRI, TAS}t_zone;
typedef struct{t_zone zone; int num_pile; int num_carte;}t_endroit;
typedef struct{t_pile cartAdep; t_endroit depart; t_endroit arrivee;}t_deplacement;

void initialiserJeu(t_carte tab[MAX], t_pile tri[NB_TRI], t_pile tas[NB_TAS], t_pioche*);
void afficherJeu(t_pile tri[NB_TRI], t_pile tas[NB_TAS],t_pioche pioche);
bool verifier_victoire(t_pile tri[NB_TRI]);
bool estOppose(t_carte c1, t_carte c2);
void afficheEndroit(t_endroit e);

void initDeplacement(t_deplacement* dep);
void afficheDeplacement(t_deplacement d);
bool deplacement_possible(t_deplacement dep, /*t_pioche pioche,*/ t_pile tri[NB_TRI], t_pile tas[NB_TAS]);
void deplacement1(t_deplacement* dep, t_pioche* pioche, t_pile tri[NB_TRI], t_pile tas[NB_TAS]);
void deplacement2(t_deplacement* dep, t_pioche* pioche, t_pile tri[NB_TRI], t_pile tas[NB_TAS]);

#endif
