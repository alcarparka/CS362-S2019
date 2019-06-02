#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "steward"

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

int random(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int randomcard;

    int i, j, m, n, z;
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

    printf("-------------------------Testing Card %s ----------------------\n", TESTCARD);

    for (z = 0; z < 100; z++) {
        //Randomize choice1
        choice1 = random(1, 3);

        printf("Choice: %d\n", choice1);

        if (choice1 == 1) {
            // ----------- TEST 1: choice1 = 1 = +2 cards --------------

            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));
            cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

            newCards = 2;
            xtraCoins = 0;
            assertTrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded);
            assertTrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards);
            assertTrue(testG.coins == G.coins + xtraCoins);
        } else if (choice1 == 2) {
            // ----------- TEST 2: choice1 = 2 = +2 coins --------------

            // copy the game state to a test case
            memcpy(&testG, &G, sizeof(struct gameState));
            choice1 = 2;
            cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

            newCards = 0;
            xtraCoins = 2;
            assertTrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded);
            assertTrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards);
            assertTrue(testG.coins == G.coins + xtraCoins);
        } else if (choice1 == 3) {
            // ----------- TEST 3: choice1 = 3 = trash two cards --------------

            // cycle through each eligible combination of 2 cards to trash
            for (i = 1; i < G.handCount[currentPlayer]; i++) {
                for (j = i + 1; j < G.handCount[currentPlayer]; j++) {
                    //Randomize cards in hand
                    for (n = 0; n < 5; n++) {
                        randomcard = random(0, 9);

                        G.hand[currentPlayer][n] = k[randomcard];
                    }

                    // copy the game state to a test case
                    memcpy(&testG, &G, sizeof(struct gameState));
                    choice2 = j;
                    choice3 = i;
                    remove1 = testG.hand[currentPlayer][i];
                    remove2 = testG.hand[currentPlayer][j];
                    cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

                    // tests that the removed cards are no longer in the player's hand
                    for (m = 0; m < testG.handCount[currentPlayer]; m++) {
                        assertTrue(testG.hand[currentPlayer][m] != remove1);
                        assertTrue(testG.hand[currentPlayer][m] != remove2);
                    }

                    // tests for the appropriate number of remaining cards
                    newCards = 0;
                    xtraCoins = 0;
                    discarded = 3;
                    if (i == 1 && j == 2) {
                        assertTrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded);
                        assertTrue(testG.deckCount[currentPlayer] ==
                                   G.deckCount[currentPlayer] - newCards + shuffledCards);
                    }


                }

            }
        }

        printf("\n");

    }
    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}