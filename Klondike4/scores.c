#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "scores.h"

/* Affiche les scores sur une surface, dst : surface modifiée */
void afficherScores(SDL_Surface* dst, t_tabScores scores, TTF_Font* police){
    int i;
    SDL_Rect posi;
    SDL_Rect posiScores;
    SDL_Color coul;
    coul.r = 255;
    coul.g = 255;
    coul.b = 255;

    /* création de la surface qui contient les scores */
    SDL_Surface* surf_scores = SDL_CreateRGBSurface(SDL_HWSURFACE,300,200,32,0,0,0,0);
    SDL_FillRect(surf_scores,NULL,SDL_MapRGB(dst->format,100,200,100));

    SDL_Surface* surftmp;

    /* centrage de la surf des scores */
    posiScores.x = dst->w/2-surf_scores->w/2;
    posiScores.y = dst->h/2-surf_scores->h/2;

    char strtmp[20];

    for(i=0;i<scores.nbscores;i++){
        posi.y = OFFSETV + TTF_FontLineSkip(police)*i;

        /* nom de la place */
        posi.x = 30;
        sprintf(strtmp,"n%d : %s",i+1, scores.tab[i].nom);
        surftmp = TTF_RenderText_Blended(police, strtmp, coul);
        SDL_BlitSurface(surftmp,NULL,surf_scores,&posi);
        SDL_FreeSurface(surftmp);

        /* chaine qui contient le temps d'une place mis en forme : hh:mm:ss */
        posi.x = 180;
        sprintf(strtmp,"%02d:%02d:%02d",scores.tab[i].h,scores.tab[i].m,scores.tab[i].s);
        surftmp = TTF_RenderText_Blended(police, strtmp, coul);
        SDL_BlitSurface(surftmp,NULL,surf_scores,&posi);
        SDL_FreeSurface(surftmp);
    }

    /* Application des scores sur la surface voulue */
    SDL_BlitSurface(surf_scores,NULL,dst,&posiScores);
    SDL_FreeSurface(surf_scores);
}
