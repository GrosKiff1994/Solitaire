#ifndef DEF_FONCTGRAPH
#define DEF_FONCTGRAPH

#include "util.h"

#include "define.h"
#include "define_algo.h"
#include "define_affichage.h"

SDL_Surface* initFenetre();
SDL_Surface* initSurfaceRGB(int w, int h, int r, int g, int b);
void initRect(SDL_Rect rectPioche[2], SDL_Rect rectTri[NB_TRI]);
bool contientClic(SDL_Rect rectCarte, SDL_Rect posiClic);
void afficherPileGraph(SDL_Surface* ecran, t_pile maPile, int indice, SDL_Surface* imCarte, SDL_Rect rectTas[NB_TAS][MAX]);
void afficherTriGraph(SDL_Surface* ecran, t_pile maPile, SDL_Rect rect, SDL_Surface* imCarte);
void afficherPiocheGraph(SDL_Surface* ecran, t_pioche maPioche, SDL_Surface* imCarte);
void afficherCarteGraph(SDL_Surface* ecran, t_carte maCarte, int x, int y, SDL_Surface* imCarte);
int carteClicPile(t_pile V_Pile[], int indicePile, SDL_Rect posiClic, SDL_Rect rectTas[NB_TAS][MAX]);
t_endroit trouveClic(SDL_Rect posiClic, SDL_Rect rectPioche[2], SDL_Rect rectTri[NB_TRI], SDL_Rect rectTas[NB_TAS][MAX], t_pile tas[NB_TAS]);
void afficherVictoire(SDL_Surface* dst, TTF_Font* police);
bool demanderRejouer(SDL_Surface* dst, TTF_Font* police);
void cheat(t_pioche* pioche, t_pile tri[NB_TRI], t_pile tas[NB_TAS]);
void anim(t_pile tri[NB_TRI], SDL_Surface* ecran, SDL_Rect rectTri[NB_TRI], SDL_Surface* imCarte);

#endif
