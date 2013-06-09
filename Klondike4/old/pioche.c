#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "pioche.h"

//fonction devoiler permet de montrer la 1ere carte du paquet, elle passe alors a la fin
void devoiler(T_Pioche* p_pioche)
{
    p_pioche->contenu[p_pioche->dernier+1] = p_pioche->contenu[p_pioche->debut];
    int i;
    for(i=1;i<p_pioche->dernier+2;i++)
    {
        p_pioche->contenu[i-1] = p_pioche->contenu[i];
    }
}
