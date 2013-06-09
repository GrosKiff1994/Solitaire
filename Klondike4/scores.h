#define NBSCORESMAX 5
#define OFFSETV 30

/* une place dans les scores */
typedef struct t_place {
    char nom[20];
    int h;
    int m;
    int s;
} t_place;

/* la structure qui contient les scores */
typedef struct t_tabScores {
    int nbscores;
    t_place tab[NBSCORESMAX];
} t_tabScores;

void afficherScores(SDL_Surface* dst, t_tabScores scores, TTF_Font* police);
