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
Card Tested: Steward
Card Type: Action
Card Cost: $3
Card Action: Choose one +2 cards, or +$2 or trash 2 cards from your hand.
*/

int main()
{
    printf("\n");
    printf("Steward Card Test \n");

    int choice1Test = 0;
    int choice2Test = 0;
    int choice3Test = 0;

    /*Set up game 1 and initialize choice 1
    This section will test choice 1 = 1; */

    int k[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    int numPlayers = 2;
    int randomSeed = 1000;
    struct gameState* testGameState = newGame();
    initializeGame(numPlayers, k, randomSeed, testGameState);
    int currentPlayer = whoseTurn(testGameState);

    /* Test choice 1 = 1, choice 2 = 0, choice 3 = 0 Should +2 Cards) */
    int shouldHaveCards = testGameState->handCount[currentPlayer] +1;

    steward_Card(0, currentPlayer, 1, 0, 0, testGameState);

    int haveCards = testGameState->handCount[currentPlayer];

    if(shouldHaveCards == haveCards)
        choice1Test = 1;
    else
        choice1Test = 0;

    /*Set up game 2 and initialize choice 1 = 2
    This section will test choice 1 = 2; */

    int l[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    struct gameState* testGameState2 = newGame();
    initializeGame(numPlayers, l, randomSeed, testGameState2);
    currentPlayer = whoseTurn(testGameState2);

    /*Test choice 1 = 2, choice 2 = 0, choice 3 = 0 Should +2 Coins*/
    int shouldHaveCoins = testGameState2->coins +2;

    steward_Card(0, currentPlayer, 2, 0, 0, testGameState2);

    int haveCoins = testGameState2->coins;

    if(shouldHaveCoins == haveCoins)
        choice2Test = 1;
    else
        choice2Test = 0;

    /*Set up game 3 and initialize choice 2 & 3
    This section will test choice 1 = 0; */

    int m[10] = {adventurer, smithy, village, great_hall, mine, remodel, sea_hag, tribute, minion, steward};
    struct gameState* testGameState3 = newGame();
    initializeGame(numPlayers, m, randomSeed, testGameState3);
    currentPlayer = whoseTurn(testGameState3);

    /* Test choice 1 = 0, choice 2 = 1, choice 3 = 2 Should -2 Cards) */
    int shouldHaveCards2 = testGameState3->handCount[currentPlayer] -2;

    steward_Card(0, currentPlayer, 0, 1, 2, testGameState3);

    int haveCards2 = testGameState3->handCount[currentPlayer];

    if(shouldHaveCards2 = haveCards2)
        choice3Test = 1;
    else
        choice3Test = 0;


    if((choice1Test == 1) && (choice2Test == 1) && (choice3Test ==1))
    {
        printf("TEST SUCCESSFULLY COMPLETED \n");
    }
    else
    {
        printf("TEST FAILED \n");
        if (choice1Test == 0)
            printf("Error in Choice 1 \n");

        if(choice2Test == 0)
            printf("Error in Choice 2 \n");

        if(choice3Test == 0)
            printf("Error in Choice 3 \n");
    }
    return 0;
}
