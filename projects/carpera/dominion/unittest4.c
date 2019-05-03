#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(int argc, char** argv) {

    printf("*****isGameOver Unit Test*****\n");

    int numPlayers = 2;
    struct gameState G;
    int result = 0;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int seed = 1000;

    //Initialize game
    initializeGame(numPlayers, k, seed, &G);

    G.supplyCount[province] = 0;

    result = isGameOver(&G);

    if(result == 1)
    {
        printf("Passed empty Province stack test\n");
    }
    else
    {
        printf("Failed empty Province stack test\n");
        printf("Returned: %d", result);
    }

    G.supplyCount[estate] = 0;
    G.supplyCount[duchy] = 0;

    result = isGameOver(&G);

    if(result == 1)
    {
        printf("Passed empty supply piles test\n");
    }
    else
    {
        printf("Failed empty supply piles test\n");
        printf("Returned: %d", result);
    }

    G.supplyCount[estate] = 2;
    G.supplyCount[duchy] = 3;
    G.supplyCount[province] = 4;

    result = isGameOver(&G);

    if(result == 0)
    {
        printf("Passed not empty supply piles test\n");
    }
    else
    {
        printf("Failed not empty supply piles test\n");
        printf("Returned: %d", result);
    }

    G.supplyCount[estate] = 1;
    G.supplyCount[duchy] = 0;
    G.supplyCount[province] = 1;

    result = isGameOver(&G);

    if(result == 0)
    {
        printf("Passed almost empty supply piles test\n");
    }
    else
    {
        printf("Failed almost empty supply piles test\n");
        printf("Returned: %d", result);
    }


    return 0;
}