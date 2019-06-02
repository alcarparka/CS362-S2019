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

int main(int argc, char** argv) {

    int cardNum;
    int numPlayers = 2;
    int i, j, m, n;
    int currentPlayer = 0;
    struct gameState G, testG;
    int countBefore = 0;
    int countAfter = 0;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int seed = 1000;

    //Initialize game
    initializeGame(numPlayers, k, seed, &G);

    printf("-------------------------Testing Card %s ----------------------\n", TESTCARD);


    for(n = 0; n < 100; n++)
    {
        countBefore = 0;
        countAfter = 0;

        G.handCount[1] = random(5, 15);

        for(m = 0; m < G.handCount[1]; m++)
        {
            cardNum = random(0, 16);


            //Set cards in player's deck
            if(cardNum == 10)
            {
                G.hand[1][m] = curse;
                G.supplyCount[curse]--;
            }
            else if(cardNum == 11)
            {
                G.hand[1][m] = estate;
                G.supplyCount[estate]--;

            }
            else if(cardNum == 12)
            {
                G.hand[1][m] = duchy;
                G.supplyCount[duchy]--;

            }
            else if(cardNum == 13)
            {
                G.hand[1][m] = province;
                G.supplyCount[province]--;

            }
            else if(cardNum == 14)
            {
                G.hand[1][m] = copper;
                G.supplyCount[copper]--;

            }
            else if(cardNum == 15)
            {
                G.hand[1][m] = silver;
                G.supplyCount[silver]--;

            }
            else if(cardNum == 16)
            {
                G.hand[1][m] = gold;
                G.supplyCount[gold]--;

            }
            else
            {
                G.hand[1][m] = k[cardNum];
                G.supplyCount[k[cardNum]]--;

            }

            printf("Hand @ %d: (%d)\n", m, G.hand[1][m]);
        }

        //Put card into player's hand for new state
        G.hand[currentPlayer][G.handCount[currentPlayer]] = cutpurse;
        //Increment handCount of new state
        G.handCount[currentPlayer]++;
        
        // ----------- TEST 1: Each other player should have one less Copper if Copper was in hand before or reveal no Copper if no Copper was in hand before--------------

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
                
                if(countBefore > 0)
                {
                    printf("\nCOPPER IN HAND: %d\n", countBefore);

                    assertTrue(countAfter == countBefore - 1);
                    //Copper card played + cutpurse card played = 2
                    assertTrue(testG.playedCardCount == G.playedCardCount + 2);

                }
                else if(countBefore == 0)
                {
                    printf("\nNO COPPER IN HAND\n");
                    assertTrue(countAfter == countBefore);
                    //No copper discarded + cutpurse played = 1
                    assertTrue(testG.playedCardCount == G.playedCardCount + 1);
                }
            }
        }

        printf("\n\n");

    }

    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}