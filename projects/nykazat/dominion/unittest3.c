/*
    UnitTest1: drawCard()
    Used testUpdateCoins.c which was provided by instructor as
    a template for writing this unit test.

    Game should end if three supply piles are at 0 or
    if province cards are empty
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
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("\n\nTESTING drawCard():\n");
    /* Setup game state for testing */

    initializeGame(numPlayer, k, seed, &G);

    memcpy(&copyOfG, &G, sizeof(struct gameState));

    drawCard(player1, &G);

    //Drawn cards are put in hand and taken from deck
    printf("Expected hand size: %d  New Hand Size: %d\n",
             copyOfG.handCount[player1]+1, G.handCount[player1]);
    if(copyOfG.handCount[player1]+1 == G.handCount[player1])
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    printf("Expected Deck Size: %d  New Deck Size: %d\n",
            copyOfG.deckCount[player1]-1, G.deckCount[player1]);
    if(copyOfG.handCount[player1]+1 == G.handCount[player1])
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    drawCard(player1, &G);

    printf("Expected hand size: %d  New Hand Size: %d\n",
             copyOfG.handCount[player1]+2, G.handCount[player1]);
    if(copyOfG.handCount[player1]+2 == G.handCount[player1])
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    printf("Expected Deck Size: %d  New Deck Size: %d\n",
            copyOfG.deckCount[player1]-2, G.deckCount[player1]);
    if(copyOfG.deckCount[player1]-2 == G.deckCount[player1])
        printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
    else
        printf("FAILED VALUES DO NOT MATCH.\n");

    return 0;
}