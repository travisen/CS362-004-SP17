/*
    UnitTest1: shuffle()
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
    int nameCards[MAX_HAND][MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    struct gameState copyOfG;
    int count; 
    int totalCards = 10;

    printf ("\n\nTESTING shuffle():\n");

    initializeGame(numPlayer, k, seed, &G);
    int identicalCards = 0;
    // duplicate game state for comparison
    memcpy(&copyOfG, &G, sizeof(struct gameState));
    printf("deckCount[0]: %d identicalCards: %d\n",
      G.deckCount[0], identicalCards);
    
    shuffle(0, &copyOfG);
    
    for(i = 0; i < G.deckCount[0]; ++i){
      if(G.deck[0][i]==copyOfG.deck[0][i])
        printf("Cards at position %d are identical\n", i);
        printf("original: %d copy: %d\n", G.deck[0][i], copyOfG.deck[0][i]);
         ++identicalCards;
    }
    
    printf("deckCount[0]: %d identicalCards: %d\n",
      G.deckCount[0], identicalCards);
    if(G.deckCount[0] == identicalCards)
      printf("TEST FAILED. DECKS ARE INDENTICAL");
    else
      printf("\nTEST PASSED. DECKS ARE NOT IDENTICAL");
        
    return 0;

    return 0;
}