/*
    villagePlay: villagePlay()
    Used both testUpdateCoins.c which was provided by instructor as
    a template for writing this unit test and the testDrawCard.c file.
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
    srand(time(NULL));
    int numPlayers = 2;
    int runs = 1000;
    struct gameState G, copyOfG;
    int i = 0;
    int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};

    printf ("\n\nTESTING villagePlay():\n");

    for (i = 1; i < runs; i++)
    {

        int seed = rand()%10000+1;
        G.deckCount[0] = rand() % MAX_DECK;
        G.discardCount[0] = rand() % MAX_DECK;
        G.handCount[0] = rand() % MAX_HAND;
        int choice1 = rand()%2;
        int choice2 = rand()%2;
        int choice3 = rand()%2;
        int handPos = rand()%2;
        //initializeGame(numPlayers, kcards, seed, &G);
        memcpy(&copyOfG, &G, sizeof(struct gameState));

        printf("TESTING villagePlay() WITH SEED: %d\n", seed);


        cardEffect(village, choice1, choice2, choice3, &G, handPos, 0);

        printf("Test %d\n", i);

        if(G.handCount[0] == copyOfG.handCount[0] + 1)
            printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
        else
            printf("FAILED VALUES DO NOT MATCH.\n");
        
        printf("Cards in Hand:  %d, Cards Expected: %d\n",
                 G.handCount[0], copyOfG.handCount[0] + 1);

        if(G.deckCount[0] == copyOfG.deckCount[0] - 1)
            printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
        else
            printf("FAILED VALUES DO NOT MATCH.\n");

        printf("Cards in Deck: %d, cards Expected: %d\n",
                G.deckCount[0], copyOfG.deckCount[0] - 1);

        if(G.numActions == copyOfG.numActions + 2)
            printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
        else
            printf("FAILED VALUES DO NOT MATCH.\n");
        printf("Number of Actions:  %d, Number Expected: %d\n",
              G.numActions, copyOfG.numActions + 2);

        printf("FINISHED TESTING %d \n\n", i);

    }

  return 0;
}