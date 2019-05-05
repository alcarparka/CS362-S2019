#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(int argc, char** argv) {

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
        printf("isGameOver(): PASS empty Province stack test\n");
    }
    else
    {
        printf("isGameOver(): FAIL empty Province stack test\n");
    }

    G.supplyCount[estate] = 0;
    G.supplyCount[duchy] = 0;

    result = isGameOver(&G);

    if(result == 1)
    {
        printf("isGameOver(): PASS empty supply piles test\n");
    }
    else
    {
        printf("isGameOver(): FAIL empty supply piles test\n");
    }

    G.supplyCount[estate] = 2;
    G.supplyCount[duchy] = 3;
    G.supplyCount[province] = 4;

    result = isGameOver(&G);

    if(result == 0)
    {
        printf("isGameOver(): PASS not empty supply piles test\n");
    }
    else
    {
        printf("isGameOver(): FAIL not empty supply piles test\n");
    }

    G.supplyCount[estate] = 1;
    G.supplyCount[duchy] = 0;
    G.supplyCount[province] = 1;

    result = isGameOver(&G);

    if(result == 0)
    {
        printf("isGameOver(): PASS almost empty supply piles test\n");
    }
    else
    {
        printf("isGameOver(): FAIL almost empty supply piles test\n");
    }


    return 0;
}