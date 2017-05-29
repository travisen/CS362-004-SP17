/*
    UnitTest1: villagePlay()
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
    struct gameState copyOfG;
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

    printf ("\n\nTESTING villagePlay():\n");

    
    initializeGame(numPlayer, k, seed, &G);

    memcpy(&copyOfG, &G, sizeof(struct gameState));

    printf("Inital hand size: %d\n",
        copyOfG.handCount[0]);
    printf("Inital Actions: %d\n",
        copyOfG.numActions);

    playVillage(&G, 0);

    //Test that hand size is the same
    printf("Expected hand size: %d  New Hand Size: %d\n",
        copyOfG.handCount[0], G.handCount[0]);
    if(copyOfG.handCount[0] == G.handCount[0])
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    //Test that actions increased by 2
    printf("Expected actions: %d  New # actions: %d\n",
        copyOfG.numActions+2, G.numActions);
    if(copyOfG.numActions+2 == G.numActions)
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    return 0;
}