/*
    randomtestadventurer: adventurerPlay()
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
    int j = 0;
    int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};

    printf ("\n\nTESTING adventurerPlay():\n");

    for (j = 1; j <= runs; j++)
    {

        int seed = rand()%10000+1;
        G.deckCount[0] = rand() % MAX_DECK;
        G.discardCount[0] = rand() % MAX_DECK;
        G.handCount[0] = rand() % MAX_HAND;
        int choice1 = rand()%2;
        int choice2 = rand()%2;
        int choice3 = rand()%2;
        int handPos = rand()%2;
        int coinsInDeck = 0;
        int cardsDug = 0;
        initializeGame(numPlayers, kcards, seed, &G);
        memcpy(&copyOfG, &G, sizeof(struct gameState));

        printf("TESTING ADVENTURERPLAY() WITH SEED: %d\n", seed);

        for (i = 0; i < copyOfG.deckCount[0]; i++)
        {
            if (copyOfG.deck[0][i] == 4 || copyOfG.deck[0][i] == 5 || copyOfG.deck[0][i] ==  6)
            {
                coinsInDeck = coinsInDeck + 1;
            }
            if (coinsInDeck >= 2) // once 2 coppers are found
            {
                coinsInDeck = i + 1;
                cardsDug = coinsInDeck;
                break;
            }
        }

        cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, 0);
        updateCoins(0, &G, 0);
        updateCoins(0, &copyOfG, 0);

        printf("Test %d\n", j);
        if(G.handCount[0] == copyOfG.handCount[0] + 2)
            printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
        else
            printf("FAILED VALUES DO NOT MATCH.\n");
        
        printf("Cards in Hand:  %d, Cards Expected: %d\n",
                 G.handCount[0], copyOfG.handCount[0] + 2);

        if(G.deckCount[0] == copyOfG.deckCount[0] - cardsDug)
            printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
        else
            printf("FAILED VALUES DO NOT MATCH.\n");

        printf("Cards in Deck: %d, cards Expected: %d\n",
                G.deckCount[0], copyOfG.deckCount[0] - cardsDug);

        if(G.discardCount[0] == copyOfG.discardCount[0] + cardsDug - 2)
            printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
        else
            printf("FAILED VALUES DO NOT MATCH.\n");
        printf("Cards in discard:  %d, Cards Expected: %d\n",
                 G.discardCount[0], copyOfG.discardCount[0] + cardsDug - 2);

        if(G.coins == copyOfG.coins + 2)
            printf("PASSED. VALUES SHOULD BE IDENTICAL\n");
        else
            printf("FAILED VALUES DO NOT MATCH.\n");
        printf("Coins: %d, Coins expected: %d\n",
                G.coins, copyOfG.coins + 2);

        printf("FINISHED TESTING %d \n\n", j);

    }

  return 0;
}