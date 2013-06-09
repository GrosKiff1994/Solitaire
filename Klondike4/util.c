#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include <time.h>

int alea(int min,int max){
    return min+rand()%(max-min+1);
}
