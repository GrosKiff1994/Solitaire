#ifndef DEF_DEFINE_AFFICHAGE
#define DEF_DEFINE_AFFICHAGE

#include <SDL/SDL.h>

// 125*182


/* define d'affichage */
#define SIZEW 1000
#define SIZEH 650
#define TAILLEIMCARTEW 1391
#define TAILLEIMCARTEH 776
#define TAILLECARTEW TAILLEIMCARTEW/NB_VAL
#define TAILLECARTEH TAILLEIMCARTEH/(NB_FAM+1)

/* position des éléments */
#define MARGE 110
#define OFFSETJEU 275
#define ESPACE (int)((double)(SIZEW - 2*MARGE)/(double)(NB_TAS - 1))
#define DECALVU 25
#define DECALPASVU  10
#define OFFSETTRI   (SIZEW - 3*ESPACE - MARGE)
#define OFFSETPIOH  MARGE
#define OFFSETZVERT 100
#define OFFSETWINV 400
#define OFFSETREJV 600

#endif
