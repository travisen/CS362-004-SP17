/******
Name: Michael Ennis
Date: 5/14/2017
CS-362-400-SP17
******/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "string.h"
#include "stdio.h"

void randomTestAdventurer()
{
    printf("\n");
    printf("Adventurer Card Test \n");

    /*Create a random deck picking 9 cards to go along with the Adventurer Card */

    int x[26] = {curse, estate, duchy, province, copper, silver, gold, smithy, council_room, feast, gardens, mine, remodel, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};

    int k[10];
    int tempk[10];
    tempk[0] = adventurer;

    int y = 0; //Inner loop to check for same cards.
    int cardCount = 1;
    int cardExsists = 0;

    while (cardCount < 10)
    {
        cardExsists = 0;
        int randCard = rand()% 26;
        tempk[cardCount] =  x[randCard];
        for(y = 0; y< cardCount; y++)
        {
            if(tempk[cardCount] == tempk[y])
                cardExsists = 1;
        }
        if(cardExsists == 0)
            cardCount++;
    }

    y = 0;

    for (y = 0; y < 9; y++)
    {
        k[y] = tempk[y];
    }

    /* get a random number of players */
    int playerAmount[3] = {2, 3, 4};
    int playerSeed = rand() % 3;
    int numPlayers = playerAmount[playerSeed];

    /* According to rngs.c -1 will create a random seed based off of time */
    int randomSeed = -1;
    struct gameState* testGameState = newGame();
    initializeGame(numPlayers, k, randomSeed, testGameState);
    int currentPlayer = whoseTurn(testGameState);
    int copperHave = 0;         /* Current amount of copper cards */
    int silverHave = 0;         /* Current amount of silver cards */
    int goldHave =0;            /* Current amount of gold cards */
    int sumShouldHave = 0;                              /*Holds # of treasure cards expected */
    int cardsShouldHave = 0;
    int temphand[MAX_HAND];

    int j = 0;

    for(j = 0; j < testGameState->handCount[currentPlayer]; j++)
    {
        if(testGameState->hand[currentPlayer][j] == copper)
            copperHave++;
        else if(testGameState->hand[currentPlayer][j] == silver)
            silverHave++;
        else if(testGameState->hand[currentPlayer][j] == gold)
            goldHave++;
    }

    printf("Before card played you have: \n");
    printf("Copper: ");
    printf("%d  \n", copperHave);
    printf("Silver: ");
    printf("%d  \n", silverHave);
    printf("Gold: ");
    printf("%d  \n", goldHave);

    sumShouldHave = copperHave + silverHave + goldHave +2;
    cardsShouldHave = testGameState->handCount[currentPlayer]+2;

    /*Play adventurer Card */
    adventurer_Card(0, currentPlayer, 0, temphand, testGameState);

    int copperHave2 = 0;     /* Current amount of copper cards */
    int silverHave2 = 0;     /* Current amount of silver cards */
    int goldHave2 =0;        /* Current amount of gold cards */
    int sumHave = 0;
    int cardsHave = 0;

    for(j = 0; j < testGameState->handCount[currentPlayer]; j++)
    {
        if(testGameState->hand[currentPlayer][j] == copper)
            copperHave2++;
        else if(testGameState->hand[currentPlayer][j] == silver)
            silverHave2++;
        else if(testGameState->hand[currentPlayer][j] == gold)
            goldHave2++;
    }

    sumHave = copperHave2 + silverHave2 + goldHave2;
    cardsHave = testGameState->handCount[currentPlayer];

    printf("After card played you have: \n");
    printf("Copper: ");
    printf("%d  \n", copperHave2);
    printf("Silver: ");
    printf("%d  \n", silverHave2);
    printf("Gold: ");
    printf("%d  \n", goldHave2);


    if((sumShouldHave == sumHave) && (cardsShouldHave == cardsHave))
    {
        printf("TEST SUCCESSFULLY COMPLETED \n");
    }
    else
    {
        printf("TEST FAILED \n");
        if(sumShouldHave != sumHave)
            printf("Incorrect number of treasure cards \n");
        else if(cardsShouldHave != cardsHave)
            printf("Incorrect number of cards \n");
    }
}
int main()
{
    SelectStream(0);
    PutSeed(4);
    int i = 0;

    for (i = 0; i < 1000; i++)
    {
        randomTestAdventurer();
    }

return 0;
}

