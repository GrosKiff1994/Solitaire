#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "define.h"
#include "define_algo.h"
#include "define_affichage.h"

#include "jeu.h"
#include "fonctgraph.h"

SDL_Surface* initFenetre(){
    SDL_Surface* fen;

    // initials=isation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Solitaire",NULL);

    Uint32          colorkey;
    SDL_Surface     *image;
    image = SDL_LoadBMP("icon.bmp");
    if(image){
        colorkey = SDL_MapRGB(image->format, 0, 255, 255);
        SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);
        SDL_WM_SetIcon(image,NULL);
    }
    else{
        fprintf(stderr, "problème d'icone : %s\n", SDL_GetError());
    }

    // création de la fenêtre
    fen = SDL_SetVideoMode(SIZEW,SIZEH,32,SDL_HWSURFACE);
    if(fen == NULL)
    {
        fprintf(stderr, "Unable to create window SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return fen;
}

SDL_Surface* initSurfaceRGB(int w, int h, int r, int g, int b){
    SDL_Surface* surf = SDL_CreateRGBSurface(SDL_HWSURFACE,w,h,32,0,0,0,0);
    SDL_FillRect(surf,NULL,SDL_MapRGB(SDL_GetVideoSurface()->format,r,g,b));
    return surf;
}

void initRect(SDL_Rect rectPioche[2], SDL_Rect rectTri[NB_TRI]){
    rectPioche[0].y = OFFSETZVERT - TAILLECARTEH/2;
    rectPioche[0].x = OFFSETPIOH - TAILLECARTEW/2;
    rectPioche[0].w = TAILLECARTEW;
    rectPioche[0].h = TAILLECARTEH;


    rectPioche[1].y = OFFSETZVERT - TAILLECARTEH/2;
    rectPioche[1].x = OFFSETPIOH + ESPACE - TAILLECARTEW/2;
    rectPioche[1].w = TAILLECARTEW;
    rectPioche[1].h = TAILLECARTEH;

    int i;
    for(i=0;i<NB_TRI;i++){
        rectTri[i].y = OFFSETZVERT - TAILLECARTEH/2;
        rectTri[i].x = OFFSETTRI + i*ESPACE - TAILLECARTEW/2;
        rectTri[i].w = TAILLECARTEW;
        rectTri[i].h = TAILLECARTEH;
    }
}

// vérifie si une coordonnée est contenue dans une carte
bool contientClic(SDL_Rect rectCarte, SDL_Rect posiClic)
{
    return((posiClic.x >= rectCarte.x) && (posiClic.x <= rectCarte.x + rectCarte.w) && (posiClic.y >= rectCarte.y) && (posiClic.y <= rectCarte.y + rectCarte.h));
}

t_endroit trouveClic(SDL_Rect posiClic, SDL_Rect rectPioche[2], SDL_Rect rectTri[NB_TRI], SDL_Rect rectTas[NB_TAS][MAX], t_pile tas[NB_TAS]){
    int i=0;
    t_endroit endroitClic = {ZVIDE, -1, -1};

    if(contientClic(rectPioche[0], posiClic)){
        endroitClic.zone = PIOCHE;
        endroitClic.num_pile = 0;
        return endroitClic;
    }

    if(contientClic(rectPioche[1], posiClic)){
        endroitClic.zone = PIOCHE;
        endroitClic.num_pile = 1;
        return endroitClic;
    }

    for(i=0;i<NB_TRI;i++){
        if(contientClic(rectTri[i], posiClic)){
            endroitClic.zone = TRI;
            endroitClic.num_pile = i;
            return endroitClic;
        }
    }


    for(i=0;i<NB_TAS;i++){
        if(estVide(tas[i])){
            if(contientClic(rectTas[i][0], posiClic)){
                endroitClic.zone = TAS;
                endroitClic.num_pile = i;
                return endroitClic;
            }
        }
        else
        {
            int c = carteClicPile(&tas[i], i, posiClic, rectTas);
            if(c > -1)
            {
                endroitClic.zone = TAS;
                endroitClic.num_pile = i;
                endroitClic.num_carte = c;
                return endroitClic;
            }
        }
    }

    return endroitClic;
}





/* retourne l'indice de la carte cliquée dans une pile ou bien -1 */
int carteClicPile(t_pile* pile, int indicePile, SDL_Rect posiClic, SDL_Rect rectTas[NB_TAS][MAX]){
    int i;
    for(i=0;i<pile->sommet;i++){
        if(contientClic(rectTas[indicePile][i],posiClic)){
            if(pile->tab[i].vu && (i==(pile->sommet -1) || !contientClic(rectTas[indicePile][i+1],posiClic))){
                return i;
            }
        }
    }
    return -1;
}

// afficher une t_pile avec SDL
void afficherPileGraph(SDL_Surface* ecran, t_pile maPile, int indice, SDL_Surface* imCarte, SDL_Rect rectTas[NB_TAS][MAX]){
    int i=0;
    int posiY = OFFSETJEU;
    int posiX;
    SDL_Rect tmp;
    if(estVide(maPile)){
        posiX = MARGE+(indice)*ESPACE;
        t_carte cartevide;
        cartevide.famille=SPEC;
        cartevide.valeur=VIDE;
        cartevide.vu=true;
        afficherCarteGraph(ecran, cartevide,posiX, posiY,imCarte);
        tmp.w = TAILLECARTEW;
        tmp.h = TAILLECARTEH;
        tmp.x = posiX-TAILLECARTEW/2;
        tmp.y = posiY-TAILLECARTEH/2;
        rectTas[indice][0]=tmp;
    }
    else{
        for(i=0;i<maPile.sommet;i++){
            posiX=MARGE+(indice)*ESPACE;
            afficherCarteGraph(ecran, maPile.tab[i], posiX, posiY, imCarte);
            tmp.w = TAILLECARTEW;
            tmp.h = TAILLECARTEH;
            tmp.x = posiX-TAILLECARTEW/2;
            tmp.y = posiY-TAILLECARTEH/2;
            rectTas[indice][i]=tmp;


            if(maPile.tab[i].vu == 0)
            {
                posiY += DECALPASVU;
            }
            else
            {
                posiY += DECALVU;
            }
        }
    }
    //printf("\n");
}

// afficher une zone de tri avec SDL
void afficherTriGraph(SDL_Surface* ecran, t_pile maPile, SDL_Rect rect, SDL_Surface* imCarte){
    int posiY = rect.y + TAILLECARTEH/2;
    int posiX = rect.x + TAILLECARTEW/2;
    if(estVide(maPile)){
        t_carte cartevide;
        cartevide.famille=SPEC;
        cartevide.valeur=VIDE;
        cartevide.vu=true;
        afficherCarteGraph(ecran, cartevide, posiX, posiY, imCarte);
    }
    else{
        afficherCarteGraph(ecran, maPile.tab[maPile.sommet-1], posiX, posiY, imCarte);
    }
}


// afficher graphiquement la pioche
void afficherPiocheGraph(SDL_Surface* ecran, t_pioche maPioche, SDL_Surface* imCarte){
    int posiY = OFFSETZVERT;
    int posiX = OFFSETPIOH;

    //SDL_Rect tmp;
    if(!estVideP_gauche(maPioche)){
        afficherCarteGraph(ecran, maPioche.contenu[maPioche.debut],posiX, posiY,imCarte);
    }
    else{
        t_carte cartevide;
        cartevide.famille=SPEC;
        cartevide.valeur=VIDE;
        cartevide.vu=true;
        afficherCarteGraph(ecran, cartevide, posiX, posiY, imCarte);
    }

    posiX = OFFSETPIOH + ESPACE;

    if(estVideP_droite(maPioche)){
        t_carte cartevide;
        cartevide.famille=SPEC;
        cartevide.valeur=VIDE;
        cartevide.vu=true;
        afficherCarteGraph(ecran, cartevide,posiX, posiY,imCarte);
    }
    else{
        afficherCarteGraph(ecran, maPioche.contenu[maPioche.dernier], posiX, posiY, imCarte);
    }
}

// afficher une carte avec SDL
void afficherCarteGraph(SDL_Surface* ecran, t_carte maCarte, int x, int y, SDL_Surface* imCarte){

    SDL_Rect posiCarte;
    posiCarte.x = x - TAILLECARTEW/2;
    posiCarte.y = y - TAILLECARTEH/2;

    SDL_Rect imTmp;

    if(maCarte.vu == true)
    {
            /* découpage de l'image */
            imTmp.x = maCarte.valeur*TAILLECARTEW;
            imTmp.y = maCarte.famille*TAILLECARTEH+1;

    }
    else
    {
            imTmp.x = DOS*TAILLECARTEW;
            imTmp.y = SPEC*TAILLECARTEH+1;
    }

    imTmp.w = TAILLECARTEW;
    imTmp.h = TAILLECARTEH;
    SDL_BlitSurface(imCarte, &imTmp, ecran, &posiCarte);
}

void afficherVictoire(SDL_Surface* dst, TTF_Font* police){
    SDL_Color coul;
    coul.r = 0;
    coul.g = 0;
    coul.b = 0;
    SDL_Surface* messageWIN = TTF_RenderText_Blended(police,"Vous avez gagné !",coul);
    SDL_Rect posi;
    posi.x = dst->w/2 - messageWIN->w/2;
    posi.y = OFFSETWINV;
    SDL_BlitSurface(messageWIN,NULL,dst,&posi);
    SDL_FreeSurface(messageWIN);
}

bool demanderRejouer(SDL_Surface* dst, TTF_Font* police){
    SDL_Color coul;
    coul.r = 0;
    coul.g = 0;
    coul.b = 0;
    SDL_Surface* messageRejouer = TTF_RenderText_Blended(police,"Voulez vous rejouer ? Entrée : oui, Echap : non",coul);
    SDL_Rect posi;
    posi.x = dst->w/2 - messageRejouer->w/2;
    posi.y = OFFSETREJV;
    SDL_BlitSurface(messageRejouer,NULL,dst,&posi);
    SDL_FreeSurface(messageRejouer);
    SDL_Flip(dst);
    SDL_Event monEvent;
    while(true){
        SDL_WaitEvent(&monEvent);
        if(monEvent.type == SDL_KEYDOWN){
            if(monEvent.key.keysym.sym == SDLK_ESCAPE) return false;
            else if(monEvent.key.keysym.sym == SDLK_RETURN) return true;
        }
    }
}

void cheat(t_pioche* pioche, t_pile tri[NB_TRI], t_pile tas[NB_TAS]){
    initPioche(pioche);
    int i,j;
    for(i=0;i<NB_TRI;i++){
        init(&tri[i]);
    }

    for(i=0;i<NB_TAS;i++){
        init(&tas[i]);
    }

    for(i=AS;i<=ROI;i++){
        for(j=TREFLE;j<=PIQUE;j++){
            t_carte tmp;
            tmp.famille = j;
            tmp.valeur = i;
            tmp.vu = true;
            empiler(&tri[j],tmp);
        }
    }
}

void anim(t_pile tri[NB_TRI], SDL_Surface* ecran, SDL_Rect rectTri[NB_TRI], SDL_Surface* imCarte) {
    SDL_Rect decal;
    SDL_Rect posi;
    int frein;

    int i, j;

    for(i=AS;i<=ROI;i++){
        for(j=TREFLE;j<=PIQUE;j++){
            t_carte dep = depiler(&tri[j]);
            posi.x = rectTri[j].x;
            posi.y = rectTri[j].y;
            int dir = alea(0,1);
            decal.x = (dir?-1:1)*alea(5,7);
            decal.y = -alea(0,15);

            int total = 10;

            bool done = false;
            while (!done)
            {
                SDL_Event event;
                while(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT) done = true;
                }
                total++;
                frein = total/10;
                decal.y += frein;
                posi.x += decal.x;
                posi.y += decal.y;
                printf("posi.x =%d, posi.y = %d, decal.x = %d, decal.y = %d\n",posi.x,posi.y, decal.x, decal.y);

                if(posi.y + TAILLECARTEH > SIZEH){
                    decal.y = - decal.y;
                    posi.y = SIZEH - TAILLECARTEH;
                }

                if(posi.x <= - TAILLECARTEW || posi.x >= SIZEW){
                    done = true;
                }

                afficherCarteGraph(ecran,dep,posi.x+TAILLECARTEW/2,posi.y+TAILLECARTEH/2,imCarte);
                SDL_Flip(ecran);
                SDL_Delay(30);
            }
        }
    }
}
