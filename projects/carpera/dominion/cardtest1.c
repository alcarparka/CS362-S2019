#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

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

int main(int argc, char** argv){

	int i, j;
	int flag;

	int numPlayers = 2;
	int currentPlayer = 0;
	int cardOne, cardTwo, treasureOne = 0, treasureTwo = 0;
	struct gameState G, testG, anothertestG;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	int seed = 1000;

	//Initialize game
	initializeGame(numPlayers, k, seed, &G);

	//Put card into player's hand for new state
	testG.hand[currentPlayer][testG.handCount[currentPlayer]] = adventurer;
	//Increment handCount of new state
	testG.handCount[currentPlayer]++;

	printf("-------------------------Testing Card %s ----------------------\n", TESTCARD);

	//Copy gameState into new state	
	memcpy(&testG, &G, sizeof(struct gameState));
	memcpy(&anothertestG, &G, sizeof(struct gameState));

	anothertestG.deck[currentPlayer][anothertestG.deckCount[currentPlayer]] = smithy;
	anothertestG.deckCount[currentPlayer]++;

	//Call cardEffect on new state
	cardEffect(adventurer, 0, 0, 0, &testG, testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1], 0);
	cardEffect(adventurer, 0, 0, 0, &anothertestG, anothertestG.hand[currentPlayer][anothertestG.handCount[currentPlayer] - 1], 0);

	//--------------------------TEST 1: Two more treasure cards should be in current player's hand----------------
	printf("TEST 1: Two more treasure cards should be in current player's hand\n");

	//Loop through hand to find number of treasure cards
	for(i = 0; i < G.handCount[currentPlayer]; i++)
	{
		cardOne = G.hand[currentPlayer][i];
		
		if(cardOne == gold || cardOne == silver || cardOne == copper)
		{
			treasureOne++;
		}
	}
	
	//Loop through hand of new state to find number of treasure cards
	for(i = 0; i < testG.handCount[currentPlayer]; i++)
	{
		cardTwo = testG.hand[currentPlayer][i];
		
		if(cardTwo == gold || cardTwo == silver || cardTwo == copper)
		{
			treasureTwo++;
		}
	}

	printf("treasure cards = %d, expected = %d\n", treasureTwo, treasureOne + 2);
	assertTrue(treasureOne + 2 == treasureTwo);


	//--------------------------TEST 2: Two treasure cards should be removed from current player's deck----------------
	printf("TEST 2: Two treasure cards should be removed from current player's deck\n");

	treasureOne = 0; treasureTwo = 0;

	//Loop through hand to find number of treasure cards
	for(i = 0; i < G.deckCount[currentPlayer]; i++)
	{
		cardOne = G.deck[currentPlayer][i];

		if(cardOne == gold || cardOne == silver || cardOne == copper)
		{
			treasureOne++;
		}
	}

	//Loop through hand of new state to find number of treasure cards
	for(i = 0; i < testG.deckCount[currentPlayer]; i++)
	{
		cardTwo = testG.deck[currentPlayer][i];

		if(cardTwo == gold || cardTwo == silver || cardTwo == copper)
		{
			treasureTwo++;
		}
	}

	printf("treasure cards = %d, expected = %d\n", treasureTwo, treasureOne - 2);
	assertTrue(treasureOne - 2 == treasureTwo);

	//--------------------------TEST 3: No cards discarded when no other revealed cards----------------
	printf("TEST 3: No cards discarded when no other revealed cards\n");

	printf("discard count = %d, expected = %d\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
	assertTrue(G.discardCount[currentPlayer] == testG.discardCount[currentPlayer]);

	//--------------------------TEST 4: One card discarded when one other revealed card----------------
	printf("TEST 4: One card discarded when one other revealed card\n");

	printf("discard count = %d, expected = %d\n", anothertestG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 1);
	assertTrue(anothertestG.discardCount[currentPlayer] - G.discardCount[currentPlayer] == 1);

	//--------------------------TEST 5: No state change should occur for other players----------------
	printf("TEST 5: No state change should occur for other players\n");

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

	//--------------------------TEST 6: No state change should occur to the victory card piles and kingdom card piles----------------
	printf("TEST 6: No state change should occur to the victory card piles and kingdom card piles\n");

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
