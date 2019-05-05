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
    int currentPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int seed = 1000;

    //Initialize game
    initializeGame(numPlayers, k, seed, &G);

    //Copy gameState into new state
    memcpy(&testG, &G, sizeof(struct gameState));

    //Put card into player's hand for new state
    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = copper;
    //Increment handCount of new state
    testG.handCount[currentPlayer]++;

    updateCoins(currentPlayer, &testG, 0);

    if(testG.coins == (G.coins + 1))
    {
        printf("updateCoins(): PASS copper test\n");
    }
    else
    {
        printf("updateCoins(): FAIL copper test\n");
    }

    //Put card into player's hand for new state
    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = silver;
    //Increment handCount of new state
    testG.handCount[currentPlayer]++;

    updateCoins(currentPlayer, &testG, 0);

    if(testG.coins == (G.coins + 3))
    {
        printf("updateCoins(): PASS silver test\n");
    }
    else
    {
        printf("updateCoins(): FAIL silver test\n");
    }

    //Put card into player's hand for new state
    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = gold;
    //Increment handCount of new state
    testG.handCount[currentPlayer]++;

    updateCoins(currentPlayer, &testG, 0);

    if(testG.coins == (G.coins + 6))
    {
        printf("updateCoins(): PASS gold test\n");
    }
    else
    {
        printf("updateCoins(): FAIL gold test\n");
    }

    updateCoins(currentPlayer, &testG, 4);

    if(testG.coins == (G.coins + 10))
    {
        printf("updateCoins(): PASS bonus test\n");
    }
    else
    {
        printf("updateCoins(): FAIL bonus test\n");
    }

    return 0;
}