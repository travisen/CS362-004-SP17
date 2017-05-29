#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "string.h"
#include "stdio.h"

/*
    Name: Michael Ennis
    Date: 30April2017
    Assignment 3
*/

/*
Card Tested: Smithy
Card Type : Action Card
Card Cost : $4
Card Action: + 3 Cards

*/

int main()
{
    printf("\n");
    printf("Smithy Card Test \n");

    /*Set up game and initialize*/
    int k[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    int numPlayers = 2;
    int randomSeed = 1000;
    struct gameState* testGameState = newGame();
    initializeGame(numPlayers, k, randomSeed, testGameState);

    /*Get the current player*/
    int currentPlayer = whoseTurn(testGameState);

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
    return 0;
}
