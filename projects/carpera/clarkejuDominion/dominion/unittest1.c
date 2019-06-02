#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char** argv) {

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
        printf("getCost(): PASS on curse cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on curse cost test\n");
    }

    cost = getCost(estate);

    if(cost == 2)
    {
        printf("getCost(): PASS on estate cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on estate cost test\n");
    }

    cost = getCost(duchy);

    if(cost == 5)
    {
        printf("getCost(): PASS on duchy cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on duchy cost test\n");
         
    }

    cost = getCost(province);

    if(cost == 8)
    {
        printf("getCost(): PASS on province cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on province cost test\n");
         
    }

    cost = getCost(copper);

    if(cost == 0)
    {
        printf("getCost(): PASS on copper cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on copper cost test\n");
         
    }

    cost = getCost(silver);

    if(cost == 3)
    {
        printf("getCost(): PASS on silver cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on silver cost test\n");
         
    }

    cost = getCost(gold);

    if(cost == 6)
    {
        printf("getCost(): PASS on gold cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on gold cost test\n");
         
    }

    cost = getCost(adventurer);

    if(cost == 6)
    {
        printf("getCost(): PASS on adventurer cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on adventurer cost test\n");
         
    }

    cost = getCost(council_room);

    if(cost == 5)
    {
        printf("getCost(): PASS on council room cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on council room cost test\n");
         
    }

    cost = getCost(feast);

    if(cost == 4)
    {
        printf("getCost(): PASS on feast cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on feast cost test\n");
         
    }

    cost = getCost(gardens);

    if(cost == 4)
    {
        printf("getCost(): PASS on gardens cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on gardens cost test\n");
         
    }

    cost = getCost(mine);

    if(cost == 5)
    {
        printf("getCost(): PASS on mine cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on mine cost test\n");
         
    }

    cost = getCost(remodel);

    if(cost == 4)
    {
        printf("getCost(): PASS on remodel cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on remodel cost test\n");
         
    }

    cost = getCost(smithy);

    if(cost == 4)
    {
        printf("getCost(): PASS on smithy cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on smithy cost test\n");
         
    }

    cost = getCost(village);

    if(cost == 3)
    {
        printf("getCost(): PASS on village cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on village cost test\n");
         
    }

    cost = getCost(baron);

    if(cost == 4)
    {
        printf("getCost(): PASS on baron cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on baron cost test\n");
         
    }

    cost = getCost(great_hall);

    if(cost == 3)
    {
        printf("getCost(): PASS on great hall cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on great hall cost test\n");
         
    }

    cost = getCost(minion);

    if(cost == 5)
    {
        printf("getCost(): PASS on minion cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on minion cost test\n");
         
    }

    cost = getCost(steward);

    if(cost == 3)
    {
        printf("getCost(): PASS on steward cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on steward cost test\n");
         
    }

    cost = getCost(tribute);

    if(cost == 5)
    {
        printf("getCost(): PASS on tribute cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on tribute cost test\n");
         
    }

    cost = getCost(ambassador);

    if(cost == 3)
    {
        printf("getCost(): PASS on ambassador cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on ambassador cost test\n");
         
    }

    cost = getCost(cutpurse);

    if(cost == 4)
    {
        printf("getCost(): PASS on cutpurse cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on cutpurse cost test\n");
         
    }

    cost = getCost(embargo);

    if(cost == 2)
    {
        printf("getCost(): PASS on embargo cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on embargo cost test\n");
         
    }

    cost = getCost(outpost);

    if(cost == 5)
    {
        printf("getCost(): PASS on outpost cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on outpost cost test\n");
         
    }

    cost = getCost(salvager);

    if(cost == 4)
    {
        printf("getCost(): PASS on salvager cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on salvager cost test\n");
         
    }

    cost = getCost(sea_hag);

    if(cost == 4)
    {
        printf("getCost(): PASS on sea hag cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on sea hag cost test\n");
         
    }

    cost = getCost(treasure_map);

    if(cost == 4)
    {
        printf("getCost(): PASS on treasure map cost test\n");
    }
    else
    {
        printf("getCost(): FAIL on treasure map cost test\n");
         
    }

    return 0;
}
