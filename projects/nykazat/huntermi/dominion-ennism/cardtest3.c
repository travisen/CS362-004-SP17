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
Card Tested: Great Hall
Card Type: Action - Victory
Card Cost: $3
Card Action: +1 Card then +1 Action
*/

int main()
{
    printf("\n");
    printf("Great Hall Card Test \n");

    /*Set up game and initialize*/
    int k[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    int numPlayers = 2;
    int randomSeed = 1000;
    struct gameState* testGameState = newGame();
    initializeGame(numPlayers, k, randomSeed, testGameState);


    /*Get the current player*/
    int currentPlayer = whoseTurn(testGameState);

    /*Number of cards player should have after Great Hall card is played*/
    int cardsNeeded = testGameState->handCount[currentPlayer];

    /*Number of action player should have after Great Hall card is played*/
    int actionNeeded = testGameState->numActions +1;

    /*Play the GreatHall Card*/
    greatHall_Card(0, currentPlayer,testGameState);

    /*Check how many cards & actions the current player has */
    int cardsHave = testGameState->handCount[currentPlayer];
    int actionHave = testGameState->numActions;


    if((cardsNeeded == cardsHave) && (actionNeeded == actionHave))
    {
        printf("TEST SUCCESSFULLY COMPLETED \n");
    }
    else
    {
        printf("TEST FAILED \n");

        if(cardsNeeded != cardsHave)
        {
            printf("Incorrect number of cards \n");
        }
        else if(actionNeeded != actionHave)
        {
            printf("Incorrect number of actions \n");
            printf("%d \n", actionNeeded);
            printf("%d \n", actionHave);
        }
    }
    return 0;
}
