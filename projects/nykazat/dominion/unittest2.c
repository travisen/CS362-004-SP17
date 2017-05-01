/*
    UnitTest2: whoseTurn()

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
#define NOISY_TEST 1

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

    printf ("TESTING whoseTurn():\n");

    int currState = 0;

    for (int turn = 0; turn < 20; turn++)
    {
        G.whoseTurn = turn;
        currState = whoseTurn(&G);

        if (currState == turn)
            printf("whoseTurn() with %d test: PASS\n", turn);
        else
            printf("whoseTurn() with %d test: FAILED\n", turn);
    }
    

    printf("whoseTurn test passed!\n");

    return 0;
}