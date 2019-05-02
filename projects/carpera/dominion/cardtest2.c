#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(int argc, char** argv) {

    printf("*****Smithy Card Test*****\n");

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
    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = smithy;
    //Increment handCount of new state
    testG.handCount[currentPlayer]++;

    //Call cardEffect on new state
    cardEffect(smithy, 0, 0, 0, &testG, testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1], 0);

    if((testG.handCount[currentPlayer] - G.handCount[currentPlayer]) == 3)
    {
        printf("Passed on cards drawn test\n");
    }
    else
    {
        printf("Failed on cards drawn test\n");

        if((testG.handCount[currentPlayer] - G.handCount[currentPlayer]) < 3) {
            printf("Not enough cards drawn\n");
            printf("Cards drawn: %d\n", (testG.handCount[currentPlayer] - G.handCount[currentPlayer]));
        }
        else if((testG.handCount[currentPlayer] - G.handCount[currentPlayer]) > 3){
            printf("Too many cards drawn\n");
            printf("Cards drawn: %d\n", (testG.handCount[currentPlayer] - G.handCount[currentPlayer]));
        }
    }

    if(testG.playedCardCount > G.playedCardCount)
    {
        printf("Passed on played card count test\n");
    }
    else
    {
        printf("Failed on played card count test\n");
    }



    return 0;
    
}
