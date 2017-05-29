/*
    UnitTest1: adventurerPlay()
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

    initializeGame(numPlayer, k, seed, &G);

    printf ("\n\nTESTING adventurerPlay():\n");

    memcpy(&copyOfG, &G, sizeof(struct gameState));

    printf("BEFORE call to adventurer\n");
    printf("Cards in Hand:  %d\n",G.handCount[0]);
    printf("Cards in Deck: %d\n",G.deckCount[0]);
    printf("Cards in discard:  %d\n", G.discardCount[0]);
    printf("Coins: %d\n", G.coins, copyOfG.coins+2);

    cardEffect(adventurer, 0, 0, 0, &G, 0, 0);

    printf("AFTER call to adventurer\n");
    printf("Cards in Hand:  %d, Cards Expected: %d\n",
             G.handCount[0], copyOfG.handCount[0]+2);
    printf("Cards in Deck: %d, Cards Expected: %d\n",
            G.deckCount[0], copyOfG.deckCount[0]-2);
    printf("Cards in discard:  %d, Cards Expected: %d\n",
             G.discardCount[0], copyOfG.discardCount[0]-2);
    printf("Coins: %d, Coins expected: %d\n",
            G.coins, copyOfG.coins+2);
    if(G.handCount[0] == copyOfG.handCount[0]+2)
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    if(G.deckCount[0] == copyOfG.deckCount[0]+2)
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");
    
    if(G.discardCount[0] == copyOfG.discardCount[0])
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    if(G.coins == copyOfG.coins+2)
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    return 0;
}