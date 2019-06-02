#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "steward"


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

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int flag = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    //Put card into player's hand for new state
    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = steward;
    //Increment handCount of new state
    testG.handCount[currentPlayer]++;

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1: choice1 = 1 = +2 cards --------------
    printf("TEST 1: choice1 = 1 = +2 cards\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

    newCards = 2;
    xtraCoins = 0;
    printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer],
           G.handCount[currentPlayer] + newCards - discarded);
    assertTrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer],
           G.deckCount[currentPlayer] - newCards + shuffledCards);
    assertTrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards);
    printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
    assertTrue(testG.coins == G.coins + xtraCoins);

    // ----------- TEST 2: choice1 = 2 = +2 coins --------------
    printf("TEST 2: choice1 = 2 = +2 coins\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 2;
    cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

    newCards = 0;
    xtraCoins = 2;
    printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer],
           G.handCount[currentPlayer] + newCards - discarded);
    assertTrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer],
           G.deckCount[currentPlayer] - newCards + shuffledCards);
    assertTrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards);
    printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
    assertTrue(testG.coins == G.coins + xtraCoins);

    // ----------- TEST 3: choice1 = 3 = trash two cards --------------

    printf("TEST 3: choice1 = 3 = trash two cards\n");
    choice1 = 3;

    // cycle through each eligible combination of 2 cards to trash
    for (i = 1; i < G.handCount[currentPlayer]; i++) {
        for (j = i + 1; j < G.handCount[currentPlayer]; j++) {

            G.hand[currentPlayer][0] = steward;
            G.hand[currentPlayer][1] = copper;
            G.hand[currentPlayer][2] = duchy;
            G.hand[currentPlayer][3] = estate;
            G.hand[currentPlayer][4] = feast;

            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));

            printf("starting cards: ");
            for (m = 0; m < testG.handCount[currentPlayer]; m++) {
                printf("(%d)", testG.hand[currentPlayer][m]);
            }
            printf("; ");

            choice2 = j;
            choice3 = i;
            remove1 = testG.hand[currentPlayer][i];
            remove2 = testG.hand[currentPlayer][j];
            cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

            printf("removed: (%d)(%d); ", remove1, remove2);
            printf("ending cards: ");

            // tests that the removed cards are no longer in the player's hand
            for (m = 0; m < testG.handCount[currentPlayer]; m++) {
                printf("(%d)", testG.hand[currentPlayer][m]);
                assert(testG.hand[currentPlayer][m] != remove1);
                assert(testG.hand[currentPlayer][m] != remove2);
            }
            printf(", expected: ");
            for (m = 1; m < G.handCount[currentPlayer]; m++) {
                if (G.hand[currentPlayer][m] != G.hand[currentPlayer][i] && G.hand[currentPlayer][m] != G.hand[currentPlayer][j]) {
                    printf("(%d)", G.hand[currentPlayer][m]);
                }
            }
            printf("\n");

            // tests for the appropriate number of remaining cards
            newCards = 0;
            xtraCoins = 0;
            discarded = 3;
            if (i == 1 && j == 2) {
                printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer],
                       G.handCount[currentPlayer] + newCards - discarded);
                assertTrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded);
                printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer],
                       G.deckCount[currentPlayer] - newCards + shuffledCards);
                assertTrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards);
            }


        }

    }

    //--------------------------TEST 4: No state change should occur for other players----------------
    printf("TEST 4: No state change should occur for other players\n");

    flag = 0;

    for (i = 0; i < numPlayers; i++) {
        if (i != currentPlayer) {
            if (testG.handCount[i] != G.handCount[i]) {
                printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
                flag = 1;
            } else {
                printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
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

    //--------------------------TEST 5: No state change should occur to the victory card piles and kingdom card piles----------------
    printf("TEST 5: No state change should occur to the victory card piles and kingdom card piles\n");

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