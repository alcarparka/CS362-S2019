#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(int argc, char** argv) {

    printf("*****Steward Card Test*****\n");

    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState G, testG_1, testG_2, testG_3;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int seed = 1000;

    //Initialize game
    initializeGame(numPlayers, k, seed, &G);

    //Copy gameState into new state
    memcpy(&testG_1, &G, sizeof(struct gameState));
    memcpy(&testG_2, &G, sizeof(struct gameState));
    memcpy(&testG_3, &G, sizeof(struct gameState));

    //Put card into player's hand for new state
    testG_1.hand[currentPlayer][testG_1.handCount[currentPlayer]] = steward;
    //Increment handCount of new state
    testG_1.handCount[currentPlayer]++;
    //Put card into player's hand for new state
    testG_2.hand[currentPlayer][testG_2.handCount[currentPlayer]] = steward;
    //Increment handCount of new state
    testG_2.handCount[currentPlayer]++;
    //Put card into player's hand for new state
    testG_3.hand[currentPlayer][testG_3.handCount[currentPlayer]] = steward;
    //Increment handCount of new state
    testG_3.handCount[currentPlayer]++;

    //Call cardEffect on new state
    cardEffect(steward, 1, 0, 0, &testG_1, testG_1.hand[currentPlayer][testG_1.handCount[currentPlayer] - 1], 0);
    cardEffect(steward, 2, 0, 0, &testG_2, testG_2.hand[currentPlayer][testG_2.handCount[currentPlayer] - 1], 0);
    cardEffect(steward, 3, 0, 0, &testG_3, testG_3.hand[currentPlayer][testG_3.handCount[currentPlayer] - 1], 0);

    if((testG_1.handCount[currentPlayer] - G.handCount[currentPlayer]) == 2)
    {
        if(testG_1.deckCount[currentPlayer] == (G.deckCount[currentPlayer] - 2))
        {
            printf("Passed on number of cards drawn test\n");
        }
        else
        {
            printf("Failed on number of cards drawn test\n");
            printf("Cards not taken from deck\n");
        }
    }
    else
    {
        if((testG_1.handCount[currentPlayer] - G.handCount[currentPlayer]) > 2)
        {
            printf("Failed on number of cards drawn test\n");
            printf("Too many cards drawn\n");
        }
        else if((testG_1.handCount[currentPlayer] - G.handCount[currentPlayer]) < 2)
        {
            printf("Failed on number of cards drawn test\n");
            printf("Too few cards drawn\n");
        }
    }

    if(testG_2.coins == (G.coins + 2))
    {
        printf("Passed on coins gained test\n");
    }
    else
    {
        if(testG_2.coins > (G.coins + 2))
        {
            printf("Failed on coins gained test\n");
            printf("Too many coins gained\n");
        }
        else if(testG_2.coins < (G.coins + 2))
        {
            printf("Failed on coins gained test\n");
            printf("Too few coins gained\n");
        }
    }

    if(testG_3.handCount[currentPlayer] == (G.handCount[currentPlayer] - 2))
    {
        printf("Passed on trash count test\n");
    }
    else if(testG_3.handCount[currentPlayer] > (G.handCount[currentPlayer] - 2))
    {
        printf("Failed on trash count test\n");
        printf("Too many cards in hand\n");
    }
    else if(testG_3.handCount[currentPlayer] < (G.handCount[currentPlayer] - 2))
    {
        printf("Failed on trash count test\n");
        printf("Too few cards in hand\n");
    }




    return 0;
}
    
