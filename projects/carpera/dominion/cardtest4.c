#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(int argc, char** argv) {

    printf("*****Cutpurse Card Test*****\n");

    int numPlayers = 2;
    int i, j;
    int currentPlayer = 0;
    struct gameState G, testG;
    int countBefore = 0;
    int countAfter = 0;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int seed = 1000;

    //Initialize game
    initializeGame(numPlayers, k, seed, &G);

    //Copy gameState into new state
    memcpy(&testG, &G, sizeof(struct gameState));

    //Put card into player's hand for new state
    testG.hand[currentPlayer][testG.handCount[currentPlayer]] = cutpurse;
    testG.handCount[currentPlayer]++;

    //Call cardEffect on new state
    cardEffect(cutpurse, 0, 0, 0, &testG, testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1], 0);

    if((testG.coins - G.coins) == 2)
    {
        printf("Passed on update coins test\n");
    }
    else
    {
        if((testG.coins - G.coins) > 2)
        {
            printf("Failed on update coins test\n");
            printf("Too many coins gained\n");
        }
        else if((testG.coins - G.coins) < 2)
        {
            printf("Failed on update coins test\n");
            printf("Too few coins gained\n");
        }
    }

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
                if(j == testG.handCount[i] && countAfter == 0)
                {
                    break;
                }
            }

            //If copper was in hand before
            if(countBefore != 0)
            {
                //If copper has been discarded
                if(countAfter == (countBefore - 1))
                {
                    printf("Passed on discard copper test 1\n");
                }
                    //If copper was not discarded
                else if(countAfter > (countBefore - 1))
                {
                    printf("Failed on discard copper test 1\n");
                    printf("Copper not discarded\n");
                }
                    //If too much copper was discarded
                else if(countAfter < (countBefore - 1))
                {
                    printf("Failed on discard copper test 1\n");
                    printf("Too much copper discarded\n");
                }
            }
                //If copper was not in hand before
            else
            {
                //If copper before is equal to copper after
                if(countBefore == countAfter)
                {
                    printf("Passed on discard copper test 1\n");
                    printf("No copper to be discarded\n");
                }
                    //If copper before is not equal to copper after
                else
                {
                    printf("Failed on discard copper test 1\n");
                    printf("No copper to be discarded\n");
                }
            }

        }

    }


    if(testG.playedCardCount == (G.playedCardCount + 1))
    {
        printf("Passed on discard card test\n");
    }
    else if(testG.playedCardCount > (G.playedCardCount + 1))
    {
        printf("Failed on discard card test\n");
        printf("Too many cards discarded\n");
    }
    else if(testG.playedCardCount < (G.playedCardCount + 1))
    {
        printf("Failed on discard card test\n");
        printf("Too few cards discarded\n");
    }

    countBefore = 0;
    countAfter = 0;

    //Manipulate original to have copper in hand
    G.hand[1][G.handCount[1]] = copper;
    G.handCount[1]++;
    G.hand[currentPlayer][G.handCount[currentPlayer]] = cutpurse;
    G.handCount[currentPlayer]++;

    //For each card in hand of other player
    for (j = 0; j < G.handCount[1]; j++)
    {
        //If card is copper
        if (G.hand[1][j] == copper)
        {
            //Add to count
            countBefore++;
        }
    }

    //Call cardEffect on original struct
    cardEffect(cutpurse, 0, 0, 0, &G, G.hand[currentPlayer][G.handCount[currentPlayer] - 1], 0);


    //For each card in hand of other player
    for (j = 0; j < G.handCount[1]; j++)
    {
        //If card is copper
        if (G.hand[1][j] == copper)
        {
            //Add to count
            countAfter++;
        }
    }

    //If copper was in hand before
    if(countBefore != 0)
    {
        //If copper has been discarded
        if(countAfter == (countBefore - 1))
        {
            printf("Passed on discard copper test 2\n");
        }
            //If copper was not discarded
        else if(countAfter > (countBefore - 1))
        {
            printf("Failed on discard copper test 2\n");
            printf("Copper not discarded\n");
        }
            //If too much copper was discarded
        else if(countAfter < (countBefore - 1))
        {
            printf("Failed on discard copper test 2\n");
            printf("Too much copper discarded\n");
        }
    }
        //If copper was not in hand before
    else
    {
        //If copper before is equal to copper after
        if(countBefore == countAfter)
        {
            printf("Passed on discard copper test 2\n");
            printf("No copper to be discarded\n");
        }
            //If copper before is not equal to copper after
        else
        {
            printf("Failed on discard copper test 2\n");
            printf("No copper to be discarded\n");
        }
    }

    return 0;
}
