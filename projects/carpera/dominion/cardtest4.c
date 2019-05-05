#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define TESTCARD "cutpurse"

void assertTrue(int true)
{
    if(true == 1)
    {
        printf("\nPASSED\n\n");
    }
    else
    {
        printf("\nFAILED\n\n");
    }
}

int main(int argc, char** argv) {

    int numPlayers = 2;
    int i, j;
    int currentPlayer = 0;
    struct gameState G, testG, anothertestG;
    int countBefore = 0;
    int countAfter = 0;
    int flag = 0;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int seed = 1000;

    //Initialize game
    initializeGame(numPlayers, k, seed, &G);

    //Put card into player's hand for new state
    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = cutpurse;
    //Increment handCount of new state
    testG.handCount[currentPlayer]++;

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1: +2 coins --------------
    printf("TEST 1: +2 coins\n");

    //Copy gameState into new state
    memcpy(&testG, &G, sizeof(struct gameState));
    //Call cardEffect on new state
    cardEffect(cutpurse, 0, 0, 0, &testG, testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1], 0);

    //Check number of coins in each state
    printf("coins = %d, expected = %d\n", testG.coins, G.coins + 2);
    //Assert
    assertTrue(testG.coins == G.coins + 2);

    // ----------- TEST 2: Each other player should have one less Copper if Copper was in hand before --------------
    printf("TEST 2: Each other player should have one less Copper if Copper was in hand before\n");

    //Add copper to hand of other player of original state
    G.hand[1][G.handCount[1]] = copper;
    //Increment handCount
    G.handCount[1]++;

    //Copy gameState into new state
    memcpy(&testG, &G, sizeof(struct gameState));
    //Call cardEffect on new state
    cardEffect(cutpurse, 0, 0, 0, &testG, testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1], 0);

    //For each player
    for (i = 0; i < numPlayers; i++)
    {
        //If player is not current player
        if (i != currentPlayer)
        {
            //For each card in hand of that player before
            for (j = 0; j < G.handCount[i]; j++)
            {
                //If card is copper
                if (G.hand[i][j] == copper)
                {
                    //Add to count
                    countBefore++;
                }
                //If last card in hand is reached and count is still 0
                if (j == G.handCount[i] && countBefore == 0)
                {
                    break;
                }
            }
            //For each card in hand of that player after
            for (j = 0; j < testG.handCount[i]; j++)
            {
                //If card is copper
                if (testG.hand[i][j] == copper)
                {
                    //Add to count
                    countAfter++;
                }
                //If last card in hand is reached and count is still 0
                if (j == testG.handCount[i] && countAfter == 0)
                {
                    break;
                }
            }

            printf("treasure = %d, expected = %d\n", countAfter, countBefore - 1);
            assertTrue(countAfter == countBefore - 1);
        }
    }

    // ----------- TEST 3: Each other player should discard a Copper if Copper was in hand before --------------
    printf("TEST 3: Each other player should discard a Copper if Copper was in hand before\n");

    //Copper card played + cutpurse card played = 2
    printf("played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 2);
    assertTrue(testG.playedCardCount == G.playedCardCount + 2);

    // ----------- TEST 4: Each other player should reveal no Copper if Copper was not in hand before --------------
    printf("TEST 4: Each other player should reveal no Copper if Copper was not in hand before\n");

    memcpy(&anothertestG, &testG, sizeof(struct gameState));
    //Call cardEffect on new state
    cardEffect(cutpurse, 0, 0, 0, &anothertestG, anothertestG.hand[currentPlayer][anothertestG.handCount[currentPlayer] - 1], 0);

    countAfter = 0;
    countBefore = 0;

    //For each player
    for (i = 0; i < numPlayers; i++)
    {
        //If player is not current player
        if (i != currentPlayer)
        {
            //For each card in hand of that player before
            for (j = 0; j < testG.handCount[i]; j++)
            {
                //If card is copper
                if (testG.hand[i][j] == copper)
                {
                    //Add to count
                    countBefore++;
                }
                //If last card in hand is reached and count is still 0
                if (j == testG.handCount[i] && countBefore == 0)
                {
                    break;
                }
            }
            //For each card in hand of that player after
            for (j = 0; j < anothertestG.handCount[i]; j++)
            {
                //If card is copper
                if (anothertestG.hand[i][j] == copper)
                {
                    //Add to count
                    countAfter++;
                }
                //If last card in hand is reached and count is still 0
                if (j == anothertestG.handCount[i] && countAfter == 0)
                {
                    break;
                }
            }
             printf("treasure = %d, expected = %d\n", countAfter, countBefore);
            assertTrue(countAfter == countBefore);

        }

    }

    // ----------- TEST 5: Each other player should not discard a Copper if Copper was not in hand before --------------
    printf("TEST 5: Each other player should not discard a Copper if Copper was not in hand before\n");

    //No copper discarded + cutpurse played = 1
    printf("played card count = %d, expected = %d\n", anothertestG.playedCardCount, testG.playedCardCount + 1);
    assertTrue(anothertestG.playedCardCount == testG.playedCardCount + 1);

    //--------------------------TEST 6: State change should occur for other players----------------
    printf("TEST 6: State change should occur for other players\n");

    flag = 0;

    for (i = 0; i < numPlayers; i++) {
        if (i != currentPlayer) {
            if (testG.handCount[i] != G.handCount[i] - 1) {
                printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i] - 1);
                flag = 1;
            } else {
                printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i] - 1);
            }
            for (j = 0; j < testG.handCount[i]; j++) {
                if (testG.hand[i][j] != G.hand[i][j]) {
                    printf("card = %d, expected = %d\n", testG.hand[i][j], G.hand[i][j]);
                    flag = 1;
                } else {
                    printf("card = %d, expected = %d\n", testG.hand[i][j], G.hand[i][j]);
                }
            }
            if (testG.deckCount[i] != G.deckCount[i]) {
                printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
                flag = 1;
            } else {
                printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
            }
            for (j = 0; j < testG.deckCount[i]; j++) {
                if (testG.deck[i][j] != G.deck[i][j]) {
                    printf("card = %d, expected = %d\n", testG.deck[i][j], G.deck[i][j]);
                    flag = 1;
                } else {
                    printf("card = %d, expected = %d\n", testG.deck[i][j], G.deck[i][j]);
                }
            }
            if (testG.discardCount[i] != G.discardCount[i]) {
                printf("discard count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);
                flag = 1;
            } else {
                printf("discard count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);
            }
            for (j = 0; j < testG.discardCount[i]; j++) {
                if (testG.discard[i][j] != G.discard[i][j]) {
                    printf("card = %d, expected = %d\n", testG.discard[i][j], G.discard[i][j]);
                    flag = 1;
                } else {
                    printf("card = %d, expected = %d\n", testG.discard[i][j], G.discard[i][j]);

                }
            }
        }
    }

    assertTrue(flag == 0);

    //--------------------------TEST 7: No state change should occur to the victory card piles and kingdom card piles----------------
    printf("TEST 7: No state change should occur to the victory card piles and kingdom card piles\n");

    flag = 0;

    for (i = 0; i < treasure_map + 1; i++) {
        if (testG.supplyCount[i] != G.supplyCount[i]) {
            printf("supply count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
            flag = 1;
        } else {
            printf("supply count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
        }
    }

    assertTrue(flag == 0);

    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}
