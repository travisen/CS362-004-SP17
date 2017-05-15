/*
    smithyPlay: smithyPlay()
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

    printf ("\n\nTESTING smithyPlay():\n");

    for (i = 1; i < runs; i++)
    {

        int seed = rand() % 10000+1;
        int choice1 = rand()%2;
        int choice2 = rand()%2;
        int choice3 = rand()%2;
        int handPos = rand()%2;
        G.deckCount[0] = rand() % MAX_DECK;
        G.discardCount[0] = rand() % MAX_DECK;
        G.handCount[0] = rand() % MAX_HAND;
        //printf("%d\n", G.handCount[0]);
        //initializeGame(numPlayers, kcards, seed, &G);
        memcpy(&copyOfG, &G, sizeof(struct gameState));
        //printf("%d\n", G.handCount[0]);
        printf("TESTING smithyPlay() WITH SEED: %d\n", seed);


        cardEffect(smithyPlay, choice1, choice2, choice3, &G, handPos, 0);

        //Drawn cards are put in hand and taken from deck
        printf("Expected hand size: %d  New Hand Size: %d\n",
            copyOfG.handCount[0] + 2, G.handCount[0]);
        if(copyOfG.handCount[0] + 2 == G.handCount[0])
            printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
        else
            printf("FAILED VALUES DO NOT MATCH.\n");

        //Player 2's hand should not change
        printf("Expected hand size: %d  New Hand Size: %d\n",
            copyOfG.handCount[1], G.handCount[1]);
        if(copyOfG.handCount[1] == G.handCount[1])
            printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
        else
            printf("FAILED VALUES DO NOT MATCH.\n");


        printf("FINISHED TESTING %d \n\n", i);

    }

  return 0;
}