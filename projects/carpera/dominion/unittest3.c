#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int random(int min, int max){
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int main(int argc, char** argv) {

    int i, j;
    srand(time(NULL));

    for(j = 0; j < 5; j++){
        int a[10] = {random(7, 26), random(7, 26), random(7, 26), random(7, 26), random(7, 26), random(7, 26), random(7, 26), random(7, 26), random(7, 26), random(7, 26)};

        int *k = kingdomCards(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);

        for(i = 0; i < 10; i++)
        {
            if(k[i] == a[i])
            {
                printf("kingdomCards(): PASS kingdom card test %d\n", i + 1);
            }
            else
            {
                printf("kingdomCards(): FAIL kingdom card test %d\n", i + 1);
            }
        }
    }

    return 0;
}