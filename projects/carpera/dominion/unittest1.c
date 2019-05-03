#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main(int argc, char** argv) {

    printf("*****getCost Unit Test*****\n");

    int numPlayers = 2;
    struct gameState G;
    int cost;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int seed = 1000;

    //Initialize game
    initializeGame(numPlayers, k, seed, &G);

    cost = getCost(curse);

    if(cost == 0)
    {
        printf("Passed on curse cost test\n");
    }
    else
    {
        printf("Failed on curse cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(estate);

    if(cost == 2)
    {
        printf("Passed on estate cost test\n");
    }
    else
    {
        printf("Failed on estate cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(duchy);

    if(cost == 5)
    {
        printf("Passed on duchy cost test\n");
    }
    else
    {
        printf("Failed on duchy cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(province);

    if(cost == 8)
    {
        printf("Passed on province cost test\n");
    }
    else
    {
        printf("Failed on province cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(copper);

    if(cost == 0)
    {
        printf("Passed on copper cost test\n");
    }
    else
    {
        printf("Failed on copper cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(silver);

    if(cost == 3)
    {
        printf("Passed on silver cost test\n");
    }
    else
    {
        printf("Failed on silver cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(gold);

    if(cost == 6)
    {
        printf("Passed on gold cost test\n");
    }
    else
    {
        printf("Failed on gold cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(adventurer);

    if(cost == 6)
    {
        printf("Passed on adventurer cost test\n");
    }
    else
    {
        printf("Failed on adventurer cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(council_room);

    if(cost == 5)
    {
        printf("Passed on council room cost test\n");
    }
    else
    {
        printf("Failed on council room cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(feast);

    if(cost == 4)
    {
        printf("Passed on feast cost test\n");
    }
    else
    {
        printf("Failed on feast cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(gardens);

    if(cost == 4)
    {
        printf("Passed on gardens cost test\n");
    }
    else
    {
        printf("Failed on gardens cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(mine);

    if(cost == 5)
    {
        printf("Passed on mine cost test\n");
    }
    else
    {
        printf("Failed on mine cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(remodel);

    if(cost == 4)
    {
        printf("Passed on remodel cost test\n");
    }
    else
    {
        printf("Failed on remodel cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(smithy);

    if(cost == 4)
    {
        printf("Passed on smithy cost test\n");
    }
    else
    {
        printf("Failed on smithy cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(village);

    if(cost == 3)
    {
        printf("Passed on village cost test\n");
    }
    else
    {
        printf("Failed on village cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(baron);

    if(cost == 4)
    {
        printf("Passed on baron cost test\n");
    }
    else
    {
        printf("Failed on baron cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(great_hall);

    if(cost == 3)
    {
        printf("Passed on great hall cost test\n");
    }
    else
    {
        printf("Failed on great hall cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(minion);

    if(cost == 5)
    {
        printf("Passed on minion cost test\n");
    }
    else
    {
        printf("Failed on minion cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(steward);

    if(cost == 3)
    {
        printf("Passed on steward cost test\n");
    }
    else
    {
        printf("Failed on steward cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(tribute);

    if(cost == 5)
    {
        printf("Passed on tribute cost test\n");
    }
    else
    {
        printf("Failed on tribute cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(ambassador);

    if(cost == 3)
    {
        printf("Passed on ambassador cost test\n");
    }
    else
    {
        printf("Failed on ambassador cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(cutpurse);

    if(cost == 4)
    {
        printf("Passed on cutpurse cost test\n");
    }
    else
    {
        printf("Failed on cutpurse cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(embargo);

    if(cost == 2)
    {
        printf("Passed on embargo cost test\n");
    }
    else
    {
        printf("Failed on embargo cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(outpost);

    if(cost == 5)
    {
        printf("Passed on outpost cost test\n");
    }
    else
    {
        printf("Failed on outpost cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(salvager);

    if(cost == 4)
    {
        printf("Passed on salvager cost test\n");
    }
    else
    {
        printf("Failed on salvager cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(sea_hag);

    if(cost == 4)
    {
        printf("Passed on sea hag cost test\n");
    }
    else
    {
        printf("Failed on sea hag cost test\n");
        printf("Returned cost: %d", cost);
    }

    cost = getCost(treasure_map);

    if(cost == 4)
    {
        printf("Passed on treasure map cost test\n");
    }
    else
    {
        printf("Failed on treasure map cost test\n");
        printf("Returned cost: %d", cost);
    }

    return 0;
}
