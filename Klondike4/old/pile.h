#include <stdbool.h>
#define MAX 52

typedef int Element;
typedef Element Tableau[MAX];
typedef struct{Tableau tab; int sommet; int nb; int max;} t_pile;

void init(t_pile*);
void empiler(t_pile*,Element);
Element depiler(t_pile*);
bool estVide(t_pile);
bool estPleine(t_pile);
void afficher(t_pile);

t_pile tas1,tas2,tas3,tas4,tas5,tas6,tas7;
t_pile tri1,tri2,tri3,tri4;
