#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"

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
    int i, j, m, n;
    int treasureHandBefore, treasureHandAfter;
    int treasureDeckBefore, treasureDeckAfter;
    int randDeckCount;
    int cardNum;
    struct gameState testG;
    int cardTwo;
    int newDeckCount;
    int bonusTreasure = 0;
    int treasureType;
    int othercards = 0;

    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int seed = 1000;

    srand(time(NULL));

    printf("-------------------------Testing Card %s ----------------------\n", TESTCARD);

    for(n = 0; n < 100; n++)
    {
        //Reset coin counters
        treasureHandBefore = 0;
        treasureHandAfter = 0;
        treasureDeckBefore = 0;
        treasureDeckAfter = 0;
        othercards = 0;

        //--------------------------SET UP DECK AND HAND----------------

        //Initialize game
        initializeGame(numPlayers, k, seed, &G);

        //Set deck count to random number between 1 and 10
        randDeckCount = random(1, 10);
        newDeckCount = G.deckCount[currentPlayer] + randDeckCount;

        for(m = 0; m < G.deckCount[currentPlayer]; m++)
        {
            printf("Deck @ %d: (%d)\n", m, G.deck[currentPlayer][m]);
        }

        for(m = G.deckCount[currentPlayer]; m < newDeckCount; m++)
        {
            //Generate random number between 0 and 16
            cardNum = random(0, 16);


            //Set cards in player's deck
            if(cardNum == 10)
            {
                G.deck[currentPlayer][m] = curse;
                G.deckCount[currentPlayer]++;
                G.supplyCount[curse]--;
            }
            else if(cardNum == 11)
            {
                G.deck[currentPlayer][m] = estate;
                G.deckCount[currentPlayer]++;
                G.supplyCount[estate]--;

            }
            else if(cardNum == 12)
            {
                G.deck[currentPlayer][m] = duchy;
                G.deckCount[currentPlayer]++;
                G.supplyCount[duchy]--;

            }
            else if(cardNum == 13)
            {
                G.deck[currentPlayer][m] = province;
                G.deckCount[currentPlayer]++;
                G.supplyCount[province]--;

            }
            else if(cardNum == 14)
            {
                G.deck[currentPlayer][m] = copper;
                G.deckCount[currentPlayer]++;
                G.supplyCount[copper]--;

            }
            else if(cardNum == 15)
            {
                G.deck[currentPlayer][m] = silver;
                G.deckCount[currentPlayer]++;
                G.supplyCount[silver]--;


            }
            else if(cardNum == 16)
            {
                G.deck[currentPlayer][m] = gold;
                G.deckCount[currentPlayer]++;
                G.supplyCount[gold]--;


            }
            else
            {
                G.deck[currentPlayer][m] = k[cardNum];
                G.deckCount[currentPlayer]++;
                G.supplyCount[k[cardNum]]--;

            }

            printf("Deck @ %d: (%d)\n", m, G.deck[currentPlayer][m]);

        }

        for(m = 0; m < G.deckCount[currentPlayer]; m++)
        {
            //If card is treasure card
            if(G.deck[currentPlayer][m] == copper || G.deck[currentPlayer][m] == silver || G.deck[currentPlayer][m] == gold)
            {
                //Add to count
                treasureDeckBefore++;
            }
        }

        printf("\n");

        for(j = 0; j < G.handCount[currentPlayer]; j++)
        {
            printf("Hand @ %d: (%d)\n", j, G.hand[currentPlayer][j]);
        }

        bonusTreasure = random(0, 5);

        for(j = 0; j < bonusTreasure; j++)
        {
            treasureType = random(1, 3);

            if(treasureType == 1)
            {
                G.hand[currentPlayer][G.handCount[currentPlayer]] = copper;
                G.supplyCount[copper]--;
            }
            else if(treasureType == 2)
            {
                G.hand[currentPlayer][G.handCount[currentPlayer]] = silver;
                G.supplyCount[gold]--;

            }
            else if(treasureType == 3)
            {
                G.hand[currentPlayer][G.handCount[currentPlayer]] = gold;
                G.supplyCount[gold]--;

            }
            printf("Hand @ %d: (%d)\n", G.handCount[currentPlayer], G.hand[currentPlayer][j]);
            G.handCount[currentPlayer]++;
        }

        //Put card into player's hand for new state
        G.hand[currentPlayer][G.handCount[currentPlayer]] = adventurer;
        G.supplyCount[adventurer]--;
        //Increment handCount of new state
        G.handCount[currentPlayer]++;

        //For each card in player's hand
        for(m = 0; m < G.handCount[currentPlayer] - 1; m++)
        {
            //If card is treasure card
            if(G.hand[currentPlayer][m] == copper || G.hand[currentPlayer][m] == silver || G.hand[currentPlayer][m] == gold)
            {
                //Add to count
                treasureHandBefore++;
            }
        }

        //Copy gameState into new state
        memcpy(&testG, &G, sizeof(struct gameState));

        //Call cardEffect on new state
        cardEffect(adventurer, 0, 0, 0, &testG, testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1], 0);

        //--------------------------TEST 1: Two more treasure cards should be in current player's hand----------------
        printf("TEST 1: ");

        //Loop through hand of new state to find number of treasure cards
        for(i = 0; i < testG.handCount[currentPlayer]; i++)
        {
            cardTwo = testG.hand[currentPlayer][i];

            if(cardTwo == gold || cardTwo == silver || cardTwo == copper)
            {
                treasureHandAfter++;
            }
        }

        assertTrue(treasureHandBefore + 2 == treasureHandAfter);


        //--------------------------TEST 2: Two treasure cards should be removed from current player's deck----------------
        printf("TEST 2: ");

        //Loop through hand of new state to find number of treasure cards
        for(i = 0; i < testG.deckCount[currentPlayer]; i++)
        {
            cardTwo = testG.deck[currentPlayer][i];

            if(cardTwo == gold || cardTwo == silver || cardTwo == copper)
            {
                treasureDeckAfter++;
            }
        }

        assertTrue(treasureDeckBefore - 2 == treasureDeckAfter);

        //--------------------------TEST 3: Appropriate amount of cards are discarded if revealed from deck----------------
        printf("TEST 3: ");

        for(i = 5; i < G.deckCount[currentPlayer]; i++)
        {
            if(G.deck[currentPlayer][i] != copper && G.deck[currentPlayer][i] != silver && G.deck[currentPlayer][i] != gold)
            {
                othercards++;
            }
        }

        assertTrue(testG.discardCount[currentPlayer] == othercards);
        printf("\n\n");
    }

    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}