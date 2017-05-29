/*
    UnitTest1: smithyPlay() Test
    Used testUpdateCoins.c which was provided by instructor as
    a template for writing this unit test..
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

    int player1 = 0;
    int player2 = 1;

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("\n\nTESTING playSmithy():\n");
    //int playSmithy(int currentPlayer, struct gameState *state, int handPos)

    initializeGame(numPlayer, k, seed, &G);

    memcpy(&copyOfG, &G, sizeof(struct gameState));

    printf("Inital hand size: %d\n",
             copyOfG.handCount[player1]);

    playSmithy(&G, 0);

    //Drawn cards are put in hand and taken from deck
    printf("Expected hand size: %d  New Hand Size: %d\n",
        copyOfG.handCount[player1]+3, G.handCount[player1]);
    if(copyOfG.handCount[player1]+3 == G.handCount[player1])
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    //Player 2's hand should not change
    printf("Expected hand size: %d  New Hand Size: %d\n",
        copyOfG.handCount[player2], G.handCount[player2]);
    if(copyOfG.handCount[player2] == G.handCount[player2])
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");


    //printf("whoseTurn test passed!\n");

    return 0;
}