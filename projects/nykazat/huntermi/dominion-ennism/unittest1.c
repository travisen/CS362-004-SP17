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
Unit Test Function:
int numHandCards(struct gameState *state)

Will check the function after init then add 2 cards and subtract 2 cards checking
the function after each call against a manually calculated integer.

*/

int main()
{
    printf("\n");
    printf("numHandCards Unit Test: \n");

    /*Set up game and initialize*/
    int k[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    int numPlayers = 2;
    int randomSeed = 1000;
    struct gameState* testGameState = newGame();
    initializeGame(numPlayers, k, randomSeed, testGameState);

    /*Get the current player*/
    int currentPlayer = whoseTurn(testGameState);
    int numberCardsCompare = 5;
    int numberCardsHave = numHandCards(testGameState);

    /*Compare to check and see if same after init */
    if(numberCardsCompare != numberCardsHave)
    {
        printf("TEST FAILED 1 \n");
        return 0;
    }

    /*Add a card and compare */
    numberCardsCompare += 1;
    drawCard(currentPlayer, testGameState);
    numberCardsHave = numHandCards(testGameState);

    if(numberCardsCompare != numberCardsHave)
    {
        printf("TEST FAILED 2 \n");
        return 0;
    }

    /*Add a card and compare again */
    numberCardsCompare += 1;
    drawCard(currentPlayer, testGameState);
    numberCardsHave = numHandCards(testGameState);

    if(numberCardsCompare != numberCardsHave)
    {
        printf("TEST FAILED 3 \n");
        return 0;
    }

    /* Discard a card and compare */
    numberCardsCompare -=1;
    discardCard(0, currentPlayer, testGameState, 0);
    numberCardsHave = numHandCards(testGameState);

    if(numberCardsCompare != numberCardsHave)
    {
        printf("TEST FAILED 4 \n");
        return 0;
    }

    /* Discard a card and compare again*/
    numberCardsCompare -=1;
    discardCard(0, currentPlayer, testGameState, 0);
    numberCardsHave = numHandCards(testGameState);

    if(numberCardsCompare != numberCardsHave)
    {
        printf("TEST FAILED 5 \n");
        return 0;
    }

    printf("TEST SUCCESSFULLY COMPLETED \n");
    return 0;
}
