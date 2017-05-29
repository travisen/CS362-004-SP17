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


void randomTestSmithy()
{

    printf("\n");
    printf("Smithy Card Test \n");

    /*Create a random deck picking 9 cards to go along with the Smithy Card */

    int x[26] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};

    int k[10];
    int tempk[10];
    tempk[0] = smithy;

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

    /*Set a random player to turn*/
    int currentPlayer = rand() % numPlayers;
    testGameState->whoseTurn = currentPlayer;

    /*Number of cards player should have after Smithy card is played*/
    int cardsNeeded = testGameState->handCount[currentPlayer] +2;

    /*Play the Smithy Card*/
    smithy_Card(0, currentPlayer, testGameState);

    /*Check how many cards the current player has */
    int cardsHave = testGameState->handCount[currentPlayer];

    if(cardsHave == cardsNeeded)
    {
        printf("TEST SUCCESSFULLY COMPLETED \n");
    }
    else
    {
        printf("TEST FAILED \n");
        printf("Current player only has ");
        printf("%d", cardsHave);
        printf(" and should have 7. \n");
    }
}
int main()
{
    printf("\n");
    printf("Smithy Card Test \n");
    int i = 0;

    for (i = 0; i < 1000; i++)
    {
        randomTestSmithy();
    }

return 0;
};
