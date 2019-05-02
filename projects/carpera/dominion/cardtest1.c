#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(int argc, char** argv){

	printf("*****Adventurer Card Test*****\n");

	int i;
	int numPlayers = 2;
	int currentPlayer = 0;
	int cardOne, cardTwo, treasureOne = 0, treasureTwo = 0;
	struct gameState G, testG, anothertestG;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	int seed = 1000;

	//Initialize game
	initializeGame(numPlayers, k, seed, &G);
	
	//Copy gameState into new state	
	memcpy(&testG, &G, sizeof(struct gameState));
	memcpy(&anothertestG, &G, sizeof(struct gameState));

	//Put card into player's hand for new state
	testG.hand[currentPlayer][testG.handCount[currentPlayer]] = adventurer;
	//Increment handCount of new state
	testG.handCount[currentPlayer]++;

	anothertestG.deck[currentPlayer][anothertestG.deckCount[currentPlayer]] = smithy;
	anothertestG.deckCount[currentPlayer]++;
	anothertestG.hand[currentPlayer][anothertestG.handCount[currentPlayer]] = adventurer;
	//Increment handCount of new state
	anothertestG.handCount[currentPlayer]++;

	//Call cardEffect on new state
	cardEffect(adventurer, 0, 0, 0, &testG, testG.hand[currentPlayer][testG.handCount[currentPlayer] - 1], 0);
	cardEffect(adventurer, 0, 0, 0, &anothertestG, anothertestG.hand[currentPlayer][anothertestG.handCount[currentPlayer] - 1], 0);

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

	if((treasureTwo - treasureOne) > 2)
	{
		printf("Failed on treasure card test. Extra cards drawn: %d\n", (treasureTwo - treasureOne) - 2);
	}
	else if((treasureTwo - treasureOne) == 2)
	{
		printf("Passed on treasure card test.\n");
	}

	if((G.deckCount[currentPlayer] - testG.deckCount[currentPlayer]) == ((testG.discardCount[currentPlayer] - G.discardCount[currentPlayer]) + (treasureTwo - treasureOne)))
	{
		printf("Passed on discard test.\n");
	}
	else
	{
		printf("Failed on discard test.\n Deck Count 1: %d\nDeck Count 2: %d\nDiscard Count 1: %d\nDiscard Count 2: %d\nTreasure: %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer], testG.discardCount[currentPlayer], G.discardCount[currentPlayer], (treasureTwo - treasureOne));
	}

	if(anothertestG.discardCount[currentPlayer] > testG.discardCount[currentPlayer])
	{
		printf("Passed on second discard test.\n");
	}
	else
	{
		printf("Failed on second discard test.\n");
	}
	

	return 0;

}
