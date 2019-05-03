#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(int argc, char** argv) {

    printf("*****kingdomCards Unit Test*****\n");

    int i;
    srand(time(NULL));

    int a[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int *k = kingdomCards(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);

    for(i = 0; i < 10; i++)
    {
        if(k[i] == a[i])
        {
            printf("Passed kingdom card test %d\n", i + 1);
        }
        else
        {
            printf("Failed kingdom card test %d\n", i + 1);
            printf("%d does not match %d\n", k[i], a[i]);
        }
    }

    int b[10] = {salvager, outpost, estate, council_room, feast, remodel, baron, great_hall, steward, ambassador};

    int *m = kingdomCards(b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9]);

    for(i = 0; i < 10; i++)
    {
        if(m[i] == b[i])
        {
            printf("Passed kingdom card test %d\n", i + 11);
        }
        else
        {
            printf("Failed kingdom card test %d\n", i + 11);
            printf("%d does not match %d\n", m[i], b[i]);
        }
    }


    return 0;
}