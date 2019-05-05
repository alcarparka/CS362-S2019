#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define TESTCARD "smithy"

void assertTrue(int true)
{
    if(true == 1)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED\n");
    }
}

int main(int argc, char** argv) {

    int i, j;
    int flag = 0;

    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int seed = 1000;

    //Initialize game
    initializeGame(numPlayers, k, seed, &G);

    //Put card into player's hand for new state
    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = smithy;
    //Increment handCount of new state
    testG.handCount[currentPlayer]++;

    printf("-------------------------Testing Card %s ----------------------\n", TESTCARD);

    //--------------------------TEST 1: current player should receive exactly 3 cards----------------
    printf("TEST 1: current player should receive exactly 3 cards\n");
    //Copy gameState into new state
    memcpy(&testG, &G, sizeof(struct gameState));
    //Call cardEffect on new state
    cardEffect(smithy, 0, 0, 0, &testG, testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1], 0);

    //3 cards added - 1 sent to played pile
    printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], (G.handCount[currentPlayer] + 2));
    assertTrue(testG.handCount[currentPlayer] - G.handCount[currentPlayer] == 2);

    //--------------------------TEST 2: 3 cards should come from current player's pile----------------
    printf("TEST 2: 3 cards should come from current player's pile\n");

    if(testG.deckCount[currentPlayer] != G.deckCount[currentPlayer] - 3)
    {
        printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - 3);
        flag = 1;
    }
    else
    {
        printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - 3);
    }

    assertTrue(flag == 0);

    //--------------------------TEST 3: No state change should occur for other players----------------
    printf("TEST 3: No state change should occur for other players\n");

    flag = 0;

    for(i = 0; i < numPlayers; i++)
    {
        if(i != currentPlayer)
        {
            if(testG.handCount[i] != G.handCount[i])
            {
                printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
                flag = 1;
            }
            else
            {
                printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
            }
            for(j = 0; j < testG.handCount[i]; j++)
            {
                if(testG.hand[i][j] != G.hand[i][j])
                {
                    printf("card = %d, expected = %d\n", testG.hand[i][j], G.hand[i][j]);
                    flag = 1;
                }
                else
                {
                    printf("card = %d, expected = %d\n", testG.hand[i][j], G.hand[i][j]);
                }
            }
            if(testG.deckCount[i] != G.deckCount[i])
            {
                printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
                flag = 1;
            }
            else
            {
                printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
            }
            for(j = 0; j < testG.deckCount[i]; j++)
            {
                if(testG.deck[i][j] != G.deck[i][j])
                {
                    printf("card = %d, expected = %d\n", testG.deck[i][j], G.deck[i][j]);
                    flag = 1;
                }
                else
                {
                    printf("card = %d, expected = %d\n", testG.deck[i][j], G.deck[i][j]);
                }
            }
            if(testG.discardCount[i] != G.discardCount[i])
            {
                printf("discard count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);
                flag = 1;
            }
            else
            {
                printf("discard count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);
            }
            for(j = 0; j < testG.discardCount[i]; j++)
            {
                if(testG.discard[i][j] != G.discard[i][j])
                {
                    printf("card = %d, expected = %d\n", testG.discard[i][j], G.discard[i][j]);
                    flag = 1;
                }
                else
                {
                    printf("card = %d, expected = %d\n", testG.discard[i][j], G.discard[i][j]);

                }
            }
        }
    }

    assertTrue(flag == 0);

    //--------------------------TEST 4: No state change should occur to the victory card piles and kingdom card piles----------------
    printf("TEST 4: No state change should occur to the victory card piles and kingdom card piles\n");

    flag = 0;

    for(i = 0; i < treasure_map + 1; i++)
    {
        if(testG.supplyCount[i] != G.supplyCount[i])
        {
            printf("supply count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
            flag = 1;
        }
        else
        {
            printf("supply count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
        }
    }

    assertTrue(flag == 0);

    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
    
}
