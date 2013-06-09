#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "define.h"
#include "define_algo.h"
#include "define_affichage.h"

#include "structure.h"
#include "jeu.h"
#include "fonctgraph.h"
#include "scores.h"


int main( int argc, char** argv )
{
    argc = argc;
    argv = argv;
    // pour les fonctions utilisant l'alea
    srand(time(NULL));
    Uint32 debut;
    Uint32 passe;

    // variables utiles partout
    int i=0, j=0;

    // différentes surfaces
    SDL_Surface* ecran;
    SDL_Surface* imCarte;
    SDL_Surface* fond;

    t_carte paquet[MAX];

    // contiennent les cartes affichées et zones
    SDL_Rect rectTas[NB_TAS][MAX];
    SDL_Rect rectTri[NB_TRI];
    SDL_Rect rectPioche[2];

    // variables de jeu
    bool gagne;
    bool quitter = false;
    bool enDeplacement;
    bool rejouer;

//    t_tabScores scores;

    // gestion de l'utilisateur
    SDL_Rect posiClic;
    posiClic.x=0;
    posiClic.y=0;

    t_endroit endroitClic;


    /* initialisation de la fenetre */
    ecran = initFenetre();



    TTF_Init();
    TTF_Font* maPolice = TTF_OpenFont("DejaVuSans.ttf",18);
    if(maPolice == NULL)
    {
        fprintf(stderr, "police non chargée : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* création du fond */
    fond = SDL_LoadBMP("fond.bmp");
    if(fond == NULL)
    {
        fprintf(stderr, "fond.bmp non chargée : %s\n", SDL_GetError());
        fond = SDL_CreateRGBSurface(SDL_HWSURFACE,SIZEW,SIZEH,32,0,0,0,0);
        SDL_FillRect(fond,NULL,SDL_MapRGB(ecran->format,118,156,4));
    }
    SDL_Rect posFond;
    posFond.x = 0;
    posFond.y = 0;

    /* chargement de l'image des cartes */
    imCarte = SDL_LoadBMP("cartes.bmp");
    if(imCarte == NULL)
    {
        fprintf(stderr, "cartes.bmp non chargée : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetColorKey(imCarte,SDL_SRCCOLORKEY,SDL_MapRGB(imCarte->format,255,0,255));


    /* structures principales */
    t_pile tri[NB_TRI];
    t_pile tas[NB_TAS];
    t_pioche pioche;
    t_deplacement curseur;
    t_save sauvegarde;
    t_save undo;

    do
    {
        enDeplacement = false;
        gagne = false;
        rejouer = false;
        /* initisalisations */
        initPaquet(paquet);
        initialiserJeu(paquet,tri,tas, &pioche);
        initRect(rectPioche,rectTri);
        initDeplacement(&curseur);
        iniSave(&sauvegarde/*, paquet*/);
        iniSave(&undo/*, paquet*/);

        saveGame(&sauvegarde, tri, tas, pioche);
        saveGame(&undo, tri, tas, pioche);
        affichePaquet(paquet);
        afficherJeu(tri, tas, pioche);

        printf("\n");


        // boucle de jeu
        while(!gagne && !quitter && !rejouer)
        {
            debut = SDL_GetTicks();

            SDL_Event monEvent;
            while(SDL_PollEvent(&monEvent))
            {
                switch(monEvent.type)
                {
                case SDL_QUIT: // si on clique sur la croix, ça ferme la fenêtre
                    quitter = true;
                    rejouer = false;
                    break;
                case SDL_KEYDOWN: // si on appuie sur la touche echap, ça ferme la fenêtre
                    if(monEvent.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quitter = true;
                        rejouer = false;
                    }
                    else if(monEvent.key.keysym.sym == SDLK_r && !enDeplacement)
                    {
                        loadingGame(&sauvegarde, tri, tas, &pioche);
                    }
                    else if(monEvent.key.keysym.sym == SDLK_u && !enDeplacement)
                    {
                        loadingGame(&undo, tri, tas, &pioche);
                    }
                    else if(monEvent.key.keysym.sym == SDLK_c && !enDeplacement){
                        cheat(&pioche,tri,tas);
                    }
                    else if(monEvent.key.keysym.sym == SDLK_n && !enDeplacement)
                    {
                        rejouer = true;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    posiClic.x=monEvent.button.x;
                    posiClic.y=monEvent.button.y;

                    if(monEvent.button.button == SDL_BUTTON_LEFT)
                    {
                        printf("\nsouris gauche enfonce");
                        endroitClic = trouveClic(posiClic, rectPioche, rectTri, rectTas, tas);
                        afficheEndroit(endroitClic);

                        if(!enDeplacement)
                        {
                            switch(endroitClic.zone)
                            {
                            case PIOCHE:
                                if(endroitClic.num_pile == 0)
                                {
                                    saveGame(&undo, tri, tas, pioche);
                                    devoiler(&pioche);
                                }
                                else
                                {
                                    if(!estVideP_droite(pioche))
                                    {
                                        saveGame(&undo, tri, tas, pioche);
                                        initDeplacement(&curseur);
                                        curseur.depart = endroitClic;
                                        deplacement1(&curseur, &pioche, tri, tas);
                                        enDeplacement = true;
                                    }
                                }
                                break;

                            case TRI:
                                if(!estVide(tri[endroitClic.num_pile]))
                                {
                                    saveGame(&undo, tri, tas, pioche);
                                    initDeplacement(&curseur);
                                    curseur.depart = endroitClic;
                                    deplacement1(&curseur, &pioche, tri, tas);
                                    enDeplacement = true;
                                }
                                break;

                            case TAS:
                                if(!estVide(tas[endroitClic.num_pile]))
                                {
                                    saveGame(&undo, tri, tas, pioche);
                                    initDeplacement(&curseur);
                                    curseur.depart = endroitClic;
                                    deplacement1(&curseur, &pioche, tri, tas);
                                    enDeplacement = true;
                                }
                                break;

                            case ZVIDE:
                                break;
                            }
                            afficherJeu(tri,tas,pioche);
                        }
                    }

                    if(monEvent.button.button == SDL_BUTTON_RIGHT)
                    {
                        printf("\nsouris droite enfonce");
                        endroitClic = trouveClic(posiClic, rectPioche, rectTri, rectTas, tas);
                        afficheEndroit(endroitClic);


                        if(!enDeplacement && (endroitClic.zone == PIOCHE || endroitClic.zone == TAS))
                        {
                            if((endroitClic.num_pile == 1 && !estVideP_droite(pioche)) || (!estVide(tas[endroitClic.num_pile])))
                            {
                                saveGame(&undo, tri, tas, pioche);
                                initDeplacement(&curseur);
                                curseur.depart = endroitClic;
                                curseur.arrivee.zone = TRI;
                                for(i=0; i<NB_TRI; i++)
                                {
                                    curseur.arrivee.num_pile = i;
                                    int tmp = tri[i].sommet;
                                    deplacement1(&curseur, &pioche, tri, tas);
                                    deplacement2(&curseur, &pioche, tri, tas);
                                    if(tri[i].sommet == tmp+1)
                                    {
                                        break;
                                    }
                                }
                            }
                            afficherJeu(tri,tas,pioche);
                        }
                    }

                    break;

                case SDL_MOUSEBUTTONUP:
                    posiClic.x=monEvent.button.x;
                    posiClic.y=monEvent.button.y;

                    if(monEvent.button.button == SDL_BUTTON_LEFT)
                    {
                        printf("\nsouris gauche relache");
                        endroitClic = trouveClic(posiClic, rectPioche, rectTri, rectTas, tas);
                        afficheEndroit(endroitClic);

                        if(enDeplacement)
                        {
                            curseur.arrivee = endroitClic;
                            deplacement2(&curseur, &pioche, tri, tas);
                            enDeplacement = false;
                        }

                        afficherJeu(tri,tas,pioche);
                    }

                    break;
                default:
                    break;
                }
            }

            /* effacer (blitter le fond) */
            SDL_BlitSurface(fond,NULL,ecran,&posFond);

            for(i=0; i<NB_TAS; i++)
            {
                for(j=0; j<MAX; j++)
                {
                    rectTas[i][j].h=0;
                    rectTas[i][j].w=0;
                }
            }

            /* affichage */
            for(i=0; i<NB_TAS; i++)
            {
                afficherPileGraph(ecran, tas[i], i, imCarte, rectTas);
            }

            for(i=0; i<NB_TRI; i++)
            {
                afficherTriGraph(ecran, tri[i], rectTri[i], imCarte);
            }

            afficherPiocheGraph(ecran, pioche, imCarte);

            if(enDeplacement)
            {
                int x, y;
                SDL_GetMouseState(&x,&y);
                for(i = curseur.cartAdep.sommet-1; i>=0 ; i--)
                {
                    afficherCarteGraph(ecran,curseur.cartAdep.tab[i],x, y - i*DECALVU + (curseur.cartAdep.sommet)*DECALVU, imCarte);
                }
            }

            if(verifier_victoire(tri))
            {
                gagne=true;
            }

            passe = SDL_GetTicks() - debut;
            if(passe < 30) SDL_Delay(30-passe);
            SDL_Flip(ecran);

        }

        if(gagne)
        {
            anim(tri,ecran,rectTri,imCarte);
            afficherVictoire(ecran,maPolice);
            SDL_Flip(ecran);

            // actions pour demander une nouvelle partie
            rejouer = demanderRejouer(ecran, maPolice);
        }
    }
    while(rejouer && !quitter);

    /* à enlever, sert pour les tests */
    SDL_FreeSurface(fond);
    SDL_FreeSurface(imCarte);

    TTF_CloseFont(maPolice);
    TTF_Quit();

    SDL_Quit();
    printf("programme quitte avec succes !\n");

    return 0;
}
