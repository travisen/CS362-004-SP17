/*
    UnitTest1: getCost()
    Used testUpdateCoins.c which was provided by instructor as
    a template for writing this unit test.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0


int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING getCost():\n");

    if (getCost(curse) == 0)
        printf("TEST FOR %s PASSED\n", "curse");
    else
        printf("TEST FOR %s FAILED\n", "curse");

    if (getCost(estate) == 2)
        printf("TEST FOR %s PASSED\n", "estate");
    else
        printf("TEST FOR %s FAILED\n", "estate");

    if (getCost(duchy) == 5)
        printf("TEST FOR %s PASSED\n", "duchy");
    else
        printf("TEST FOR %s FAILED\n", "duchy");

    if (getCost(adventurer) == 6)
        printf("TEST FOR %s PASSED\n", "adventurer");
    else
        printf("TEST FOR %s FAILED\n", "adventurer");

    if (getCost(smithy) == 4)
        printf("TEST FOR %s PASSED\n", "smithy");
    else
        printf("TEST FOR %s FAILED\n", "smithy");

    if (getCost(baron) == 4)
        printf("TEST FOR %s PASSED\n", "baron");
    else
        printf("TEST FOR %s FAILED\n", "baron");

    if (getCost(treasure_map) == 4)
        printf("TEST FOR %s PASSED\n", "treasure_map");
    else
        printf("TEST FOR %s FAILED\n", "treasure_map");

    if (getCost(salvager) == 4)
        printf("TEST FOR %s PASSED\n", "salvager");
    else
        printf("TEST FOR %s FAILED\n", "salvager");


    //printf("whoseTurn test passed!\n");

    return 0;
}